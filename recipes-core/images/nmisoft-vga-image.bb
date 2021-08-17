SUMMARY = "A small image with a VGA driver"

LICENSE = "MIT"

IMAGE_INSTALL = "packagegroup-core-boot ${CORE_IMAGE_EXTRA_INSTALL}"

IMAGE_LINGUAS = " "

inherit core-image

IMAGE_FEATURES_append = " ssh-server-openssh"
IMAGE_INSTALL_append = " nmisoftvga-mod"
