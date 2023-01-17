#!/bin/bash
#
OPTIONS_FILE="8821cu.conf"
SCRIPT_NAME="edit-options.sh"
DEFAULT_EDITOR="nano"
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

# Try to find the user's default text editor through ${VISUAL}, ${EDITOR} or nano
if command -v "${VISUAL}" >/dev/null 2>&1
then
        TEXT_EDITOR="${VISUAL}"
elif command -v "${EDITOR}" >/dev/null 2>&1
then
        TEXT_EDITOR="${EDITOR}"
elif command -v "${DEFAULT_EDITOR}" >/dev/null 2>&1
then
        TEXT_EDITOR="${DEFAULT_EDITOR}"
else
        echo "No text editor found (default: ${DEFAULT_EDITOR})."
        echo "Please install one and set the VISUAL or EDITOR variables to point to it."
        echo "When you have an editor, please run \"sudo ./${SCRIPT_NAME}\""
        exit 1
fi

${TEXT_EDITOR} /etc/modprobe.d/${OPTIONS_FILE}

read -p "Do you want to apply the new options by rebooting now? [y/N] " -n 1 -r
echo    # move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    reboot
fi

exit 0
