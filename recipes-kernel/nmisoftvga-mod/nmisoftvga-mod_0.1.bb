SUMMARY = "nmisoft VGA kernel module"
DESCRIPTION = "${SUMMARY}"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=18daa804c2bf1c4e9f2beb326a36407a"

inherit module

SRC_URI = "file://Makefile \
           file://nmisoftvga.c \
           file://LICENSE \
          "

S = "${WORKDIR}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

RPROVIDES_${PN} += "kernel-module-nmisoftvga"
