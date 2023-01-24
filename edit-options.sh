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
DEFAULT_EDITOR="$(<default-editor.txt)"
EDITORS_SEARCH=("${VISUAL}" "${EDITOR}" "${DEFAULT_EDITOR}" "vi")

if [[ $EUID -ne 0 ]]
then
	echo "You must run this script with superuser (root) privileges."
	echo "Try: \"sudo ./${SCRIPT_NAME}\""
	exit 1
fi

# Try to find the user's default text editor through the EDITORS_SEARCH array
for editor in ${EDITORS_SEARCH[@]}
do
        if command -v "${editor}" >/dev/null 2>&1
        then
                TEXT_EDITOR="${editor}"
                break
        fi
done

# Fail if no editor was found
if ! command -v "${TEXT_EDITOR}" >/dev/null 2>&1
then
        echo "No text editor found (default: ${DEFAULT_EDITOR})."
        echo "Please install ${DEFAULT_EDITOR} or edit the file 'default-editor.txt' to specify your editor."
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
