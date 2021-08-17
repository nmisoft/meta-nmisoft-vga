FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_append = " file://0001-Add-user-dts-include.patch \
		   file://nmisoft-vga.dtsi;subdir=git/arch/arm/boot/dts \
		   file://nmisoft-vga-enable-spi1.dtsi;subdir=git/arch/arm/boot/dts \
		   file://disable-mcasp.cfg \
		   file://disable-leds-gpio.cfg \
		   "

KERNEL_CONFIG_FRAGMENTS += "${WORKDIR}/disable-mcasp.cfg"
KERNEL_CONFIG_FRAGMENTS += "${WORKDIR}/disable-leds-gpio.cfg"
