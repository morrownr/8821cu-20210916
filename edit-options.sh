#!/bin/bash

# Purpose: Make it easier to edit the driver options file.
#
# Flexible editor support.
#
# To make this file executable:
#
# $ chmod +x edit-options.sh
#
# To execute this file:
#
# $ sudo ./edit-options.sh
#
# Copyright(c) 2023 Nick Morrow
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of version 2 of the GNU General Public License as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

SCRIPT_NAME="edit-options.sh"
SCRIPT_VERSION="20230120"
OPTIONS_FILE="8821cu.conf"
DEFAULT_EDITOR=`cat default-editor`

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
        echo "Please install ${DEFAULT_EDITOR} or edit the file 'default-editor' to specify your editor."
        echo "Once complete, please run \"sudo ./${SCRIPT_NAME}\""
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
