#!/bin/sh
# SPDX-License-Identifier: MIT

busybox mkdir -p /lib/firmware/imx/epdc
if [ ! -f /lib/firmware/imx/epdc/epdc-extracted.fw ]
        then 
		[ -e /dev/mmcblk0 ] || busybox mknod /dev/mmcblk0 b 179 0
                extract-kobohidden /dev/mmcblk0 14336 /lib/firmware/imx/epdc/epdc-extracted.fw
                if [ ! -e /lib/firmware/imx/epdc/epdc.fw ]
                then
                        busybox ln -s /lib/firmware/imx/epdc/epdc-extracted.fw /lib/firmware/imx/epdc/epdc.fw
                fi
        fi
modprobe mxc_epdc_drm
