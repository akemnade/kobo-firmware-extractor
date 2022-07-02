// SPDX-License-Identifier: MIT

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char **argv)
{
   const uint8_t magic[8] = {
      0xff, 0xf5, 0xaf, 0xff, 0x78, 0x56, 0x34, 0x12
   };
   uint8_t head[16];
   int fd;
   int destfd;
   off_t offset;
   uint8_t *buf;
   size_t length;

   if (argc != 4) {
       fprintf(stderr, "Usage: %s device-or-image offset-in-sectors outputfile\n", argv[0]);
       fprintf(stderr, "\nextracts firmware from a kobo hidden partition\n");
       return 1;
   }

   fd = open(argv[1], O_RDONLY);
   if (fd < 0) {
       fprintf(stderr, "cannot open %s\n", argv[1]);
       return 1;
   }
   
   offset = strtoul(argv[2], NULL, 0); 
   offset *= 512;
   if (lseek(fd, offset - sizeof(magic) - 8, SEEK_SET) < 0) {
       perror("seek failed");
       return 1;
   }
   
   if ((sizeof(head) != read(fd, head, sizeof(head))) ||
       (memcmp(head, magic, sizeof(magic)))) {
       fprintf(stderr, "did not find valid header\n");
       return 1;
   } 
   
   length = head[11];
   length <<= 8;
   length |= head[10];
   length <<= 8;
   length |= head[9];
   length <<= 8;
   length |= head[8];

   buf = malloc(length);
   if (length != read(fd, buf, length)) {
       fprintf(stderr, "failed to read data\n");
       return 1;
   }

   destfd = open(argv[3], O_WRONLY | O_CREAT, 0666);
   if (destfd < 0) {
       fprintf(stderr, "failed to open %s\n", argv[3]);
       return 1;
   }

   if (length != write(destfd, buf, length)) {
       fprintf(stderr, "failed to write data\n");
       return 1;
   }

   return 0;
}
