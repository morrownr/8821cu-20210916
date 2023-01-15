#!/bin/bash
#
OPTIONS_FILE="8821cu.conf"
SCRIPT_NAME="edit-options.sh"
#
# Purpose: Make it easier to edit the driver options file.
#
# To make this file executable:
#
# $ chmod +x edit-options.sh
#
# To execute this file:
#
# $ sudo ./edit-options.sh
#
if [[ $EUID -ne 0 ]]
then
	echo "You must run this script with superuser (root) privileges."
	echo "Try: \"sudo ./${SCRIPT_NAME}\""
	exit 1
fi

# Check if ${EDITOR} is an executable or try to default to nano or finally complain if it's not installed.
if ! [ -x "${EDITOR}" ]
then
        EDITOR="$(which nano 2>/dev/null)"
        if ! [ -x "${EDITOR}" ]
        then
                echo "No text editor found (default: nano)."
                echo "Please install one and set the EDITOR variable to point to it."
                echo "When you have an editor, please run \"sudo ./${SCRIPT_NAME}\""
                exit 1
        fi
fi

${EDITOR} /etc/modprobe.d/${OPTIONS_FILE}

read -p "Do you want to apply the new options by rebooting now? [y/N] " -n 1 -r
echo    # move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    reboot
fi

exit 0
