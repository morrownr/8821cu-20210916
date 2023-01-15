#!/bin/sh

# SMEM needs to be set here if dkms build is not initiated by install-driver.sh
SMEM=$(LANG=C free | awk '/Mem:/ { print $2 }')

# SPROC needs to be set here if dkms build is not initiated by install-driver.sh
SPROC=$(nproc)

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

exit 0
