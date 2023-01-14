#!/bin/sh

# SMEM needs to be set here if dkms build is not initiated by install-driver.sh
if [[ ! -z ${SMEM} ]]
then
    SMEM=$(LANG=C free | awk '/Mem:/ { print $2 }')
fi

# SMEM needs to be set here if dkms build is not initiated by install-driver.sh
if [[ ! -z ${SPROC} ]]
then
    SPROC=$(nproc)
fi

# Avoid Out of Memory condition in low-RAM systems by limiting core usage.
if [ "$SPROC" -gt 1 ]
then
	if [ "$SMEM" -lt 1400000 ]
	then
		SPROC=2
	fi
fi

kernelver=${kernelver:-$(uname -r)}
make "-j$SPROC" "KVER=$kernelver" "KSRC=/lib/modules/$kernelver/build"
