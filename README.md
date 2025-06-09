Notice: An updated standards compliant (mac80211), in-kernel driver for
rtl8821/11cu chipset based adapters and modules is available and as of
kernel 6.12 is of good quality. If your distro uses kernel 6.12 or
later, there is no need to install this driver. The in-kernel driver is
part of the rtw88 series of drivers. The in-kernel driver is Linux
Standards compliant (mac80211) and is a much better driver than this
one. This driver will no longer get API related updates beyond kernel
6.14 (unless provided by a user). If you use a kernel prior to 6.14, it
is possible to use the new standards compliant driver by going to the
following repo:

https://github.com/lwfinger/rtw88

If you decide to use the in-kernel driver, remember to first remove the
driver in this repo. You can run the following to remove the driver in
this repo:

$ sudo sh remove-driver.sh

It has been my pleasure to maintain this driver for the last several
years. Thanks to all of those who helped.

Remember: Ask not what your operating system can do for you, but
what you can do for your operating system.

Regards,

@morrownr

## 8821cu ( 8821cu.ko ) :rocket:

## Linux Driver for USB WiFi Adapters that are based on the RTL8811CU, RTL8821CU, RTL8821CUH and RTL8731AU Chipsets

- v5.12.0.4 (Realtek) (20210916) plus updates from the Linux community

Note: Please read the file "supported-device-IDs" for information about
how to confirm that this is the correct driver for your adapter.

### Supported Features

- IEEE 802.11 b/g/n/ac WiFi compliant
- 802.1x, WEP, WPA TKIP and WPA2 AES/Mixed mode for PSK and TLS (Radius)
- WPA3-SAE (Personal) (see FAQ)
- WPA3-Enterprise (Suite-B 192-bit)
- WAPI 1.0 station mode
- WPS - PIN and PBC Methods
- IEEE 802.11b/g/n/ac Client mode
  * Supports wireless security for WEP, WPA TKIP and WPA2 AES PSK
  * Supports site survey scan and manual connect
  * Supports WPA/WPA2 TLS client
- Power saving modes
- Miracast
- WiFi-Direct
- MU-MIMO
- Mesh
- Wake on WLAN
- Wireshark compatible
- Aircrack-ng compatible
- Packet injection
- hostapd compatible
- AP mode DFS channel support
- Supported interface modes
  * Managed
  * Monitor (see FAQ) (see [Monitor_Mode](https://github.com/morrownr/Monitor_Mode))
  * AP (see [Bridged Wireless Access Point](https://github.com/morrownr/USB-WiFi/blob/main/home/AP_Mode/Bridged_Wireless_Access_Point.md))
  * P2P-client
  * P2P-GO
- Log level control
- LED control
- Power saving control
- VHT control (allows 80 MHz channel width in AP mode)
- AP mode DFS channel control

### A FAQ is available in this repo with the name `FAQ.md`

- Please read the FAQ and this document before posting issues.

### Additional documentation is in the file `8821cu.conf`

### Compatible CPU Architectures

- x86, i386, i686
- x86-64, amd64
- armv6l, armv7l (arm)
- aarch64 (arm64)

Note: Additional CPU architectures may work but I currently only have
the hardware to test the above.

### Compatible Kernels

- Kernels: 5.10 - 5.11 (Realtek)
- Kernels: 5.12 - 6.14 (community support)

Note: Kernels earlier than 5.10 may work but are not tested or
supported.

### Tested Compilers

- gcc 12, 13 and 14

### Tested Linux Distributions

Note: The information in this section depends largely on user reports
which can be provided via PR or message in Issues.

- [Arch Linux](https://www.archlinux.org) (kernels 5.4 and 5.11)

- [Armbian](https://www.armbian.com/) (kernel 5.15) (Rock 4 SE (Rock 4b image with xfce))

- [Debian](https://www.debian.org/) (kernels 5.10, 5.15 and 6.1)

- [Fedora](https://getfedora.org) Fedora 38 (6.2.13-300)

- [Kali Linux](https://www.kali.org/) (kernel 6.3)

- [Manjaro](https://manjaro.org) (kernel 5.15)

- [openSUSE](https://www.opensuse.org/) Tumbleweed (rolling) (kernel 5.15)

- [Raspberry Pi OS](https://www.raspberrypi.org) (2023-05-03)(ARM 32 bit and 64 bit) (kernel 6.1.38)

- [Raspberry Pi Desktop](https://www.raspberrypi.org) (2022-07-01) (x86 32 bit) (kernel 5.10)

- [SkiffOS](https://github.com/skiffos/skiffos/) for Odroid XU4 (ARM 32 bit) (kernel 6.0.7)

- [Ubuntu](https://www.ubuntu.com) 22.04 (kernel 5.15) and 22.10 (kernel 5.19) (kernel 6.2)

- [Void Linux](https://voidlinux.org/) (kernel 5.18)

Note: Red Hat Enterprise Linux (RHEL) and distros based on RHEL are
supported by Red Hat devs due to the way kernel patches are handled in
Red Hat. I support knowledgable RHEL developers if they want to merge
the required support and keep it current. I reserve the right to delete
this support without notice if it causes any problems.

Current RHEL maintainer: none

Note: Android is supported in the driver according to Realtek. I will
support knowledgable Android developers if they want to merge and keep
current the required support (most likely just instructions about how to
compile and maybe a modification or two to the Makefile).

Current Android maintainer: none

Note: OpenWRT is not supported. OpenWRT provides drivers for USB WiFi
adapters. OpenWRT provided drivers include support for the MT7921au
(AXE3000), MT7612u (AC1200), MT7610u (AC600) chipsets. It is a challenge
to use Realtek based adapters that use out-of-kernel drivers with
OpenWRT so it is strongly advised to use the already supported chipsets.

### Compatible Devices

- EDUP EP-AC1651 (nano) (single-state, single-function)
- EDUP EP-AC1635 (single-state, single-function)
- Numerous adapters that are based on the supported chipsets

Note: If you are looking for information about what adapter to buy,
click [here](https://github.com/morrownr/USB-WiFi) and look for Main
Menu item 2 which will show information about and links to recommended
adapters.

Note: If you decide to buy an adapter that is supported by this driver,
I recommend you search for an adapter that is `single-state and
single-function`. Multi-function adapters, wifi and bluetooth, can be
problematic. For advice about single-state and multi-state adapters, 
click [here](https://github.com/morrownr/USB-WiFi) and look for Main
Menu item 1.

### Installation Information

Warning: It is recommended that you follow the installation instructions
in the Installation Steps section. Avoid installation by downloading the
zip file if at all possible. Support can only be provided, on a best
effort basis, if the Installation Steps in the next section are followed.

Warning: Installing multiple out-of-kernel drivers for the same hardware
usually does not end well. The install-driver.sh script has the
capability to detect and remove most conflicting drivers but not all. If
this driver does not work well after installation and you have
previously installed a driver that you did not remove, it is suggested
that you run the following command in an effort to determine if you need
to take action to manually remove conflicting drivers:

```
sudo dkms status
```

Warning: If you decide to do a distro upgrade, which will likely install
a new version of kernel such as 5.15 to 6.1, you need to update this
driver with the newest available code and then run the removal script
before performing the disto upgrade. Use the following commands in the
driver directory:

```
git pull
```

Note: Do not reboot before running the below command so that the driver
stays active until after your distro upgrade is complete.

```
sudo sh remove-driver.sh
```

Note: The following command will reinstall the updated driver after you
are finished with the distro upgrade and reboot.

```
sudo sh install-driver.sh
```

Internet access is required for initial installation. There are
numerous ways to enable temporary internet access depending on your
hardware and situation. [One method is to use tethering from a phone.](https://www.makeuseof.com/tag/how-to-tether-your-smartphone-in-linux).
Another method is to keep a [WiFi adapter that uses an in-kernel driver](https://github.com/morrownr/USB-WiFi/blob/main/home/USB_WiFi_Adapters_that_are_supported_with_Linux_in-kernel_drivers.md) in your toolkit.

You will need to use the terminal interface. The quick way to open a
terminal: Ctrl+Alt+T (hold down on the Ctrl and Alt keys then press the
T key).

An alternative terminal is to use SSH (Secure Shell) from the same or from
another computer, in which case you will be in a suitable terminal after logging
in, but this step requires that an SSH daemon/server has already been
configured. (There are lots of SSH guides available, e.g., for the [Raspberry Pi](https://www.raspberrypi.com/documentation/computers/remote-access.html#setting-up-an-ssh-server) and for [Ubuntu](https://linuxconfig.org/ubuntu-20-04-ssh-server). Do not forget [to secure the SSH server](https://www.howtogeek.com/443156/the-best-ways-to-secure-your-ssh-server/).)

You will need to have sufficient access rights to use `sudo` so that commands
can be executed as the `root` user. (If the command `sudo echo Yes` returns
"Yes", with or without having to enter your password, you do have sufficient
access rights.)

DKMS is used for the installation, if available. DKMS is a system utility
which will automatically recompile and reinstall this driver when a new
kernel is installed. DKMS is provided by and maintained by Dell.

It is recommended that you do not delete the driver directory after
installation as the directory contains information and scripts that you
may need in the future.

Secure Boot: see FAQ.

### Installation Steps

Note: The installation instructions are for the novice user. Experienced
users are welcome to alter the installation to meet their needs. Support
will be provided, on a best effort basis, based on the steps below. Another
way to word this paragraph is that if you do not follow the below steps for
installation, you are your own tech support.

#### Step 1: Open a terminal (e.g. Ctrl+Alt+T)

#### Step 2: Update and upgrade system packages (select the option for the distro you are using)

Note: If your Linux distro does not fall into one of options listed
below, you will need to research how to `update` and `upgrade` your
system packages.

- Option for Debian based distributions such as Ubuntu, Kali, Armbian
and Raspberry Pi OS

```
sudo apt update && sudo apt upgrade
```

- Option for Arch based distributions such as Manjaro

```
sudo pacman -Syu
```

- Option for Fedora based distributions

```
sudo dnf upgrade
```

- Option for openSUSE based distributions

```
sudo zypper update
```

- Option for Void Linux

```
sudo xbps-install -Syu
```

Note: It is recommended that you reboot your system at this point. The
rest of the installation will appreciate having a fully up-to-date
system to work with. The installation can then be continued with Step 3.

```
sudo reboot
```

#### Step 3: Install the required packages (select the option for the distro you are using)

Note: If your Linux distro does not fall into one of options listed
below, you will need to research how to properly setup up the development
environment for your system. General guidance follows.

Development Environment Requirements: (package names may vary by distro)

- Mandatory packages: `gcc` `make` `bc` `kernel-headers` `build-essential` `git`
- Highly recommended packages: `dkms` `rfkill` `iw` `ip`
- Mandatory packages if Secure Boot is active: `openssl` `sign-file` `mokutil`

Note: The below options should take care of the mandatory and highly recommended
requirements. If Secure Boot is active on your system, please also install the
mandatory packages for Secure Boot as shown above.

- Option for Armbian (arm64)

```
sudo apt install -y build-essential
```

- Option for Raspberry Pi OS (arm/arm64)

```
sudo apt install -y raspberrypi-kernel-headers build-essential bc dkms git
```

- Option for Debian, Kali, and Raspberry Pi Desktop (x86)

```
sudo apt install -y linux-headers-$(uname -r) build-essential bc dkms git libelf-dev rfkill iw
```

- Option for Ubuntu (all official flavors) and the numerous Ubuntu based distros

```
sudo apt install -y build-essential dkms git iw
```

- Option for Fedora

Note: Fedora users should also install `openssl` if secure boot is
active.

```
sudo dnf -y install git dkms kernel-devel
```

- Option for openSUSE

```
sudo zypper install -t pattern devel_kernel dkms
```

- Option for Alpine

```
sudo apk add linux-lts-dev make gcc
```

- Option for Void Linux

```
sudo xbps-install linux-headers dkms git make
```

- Options for Arch and Manjaro (if using Manjaro for RasPi4B, see note)

If using pacman

```
sudo pacman -S --noconfirm linux-headers dkms git bc iw
```

Note: The following is needed if using Manjaro for RasPi4B.

```
sudo pacman -S --noconfirm linux-rpi4-headers dkms git bc
```

Note: If you are asked to choose a provider, make sure to choose the one
that corresponds to your version of the linux kernel (for example,
"linux510-headers" for Linux kernel version 5.10). If you install the
incorrect version, you'll have to uninstall it and install the correct
version.

If using other methods, please follow the instructions provided by those
methods.

#### Step 4: Create a directory to hold the downloaded driver

```
mkdir -p ~/src
```

#### Step 5: Move to the newly created directory

```
cd ~/src
```

#### Step 6: Download the driver

```
git clone https://github.com/morrownr/8821cu-20210916.git
```

#### Step 7: Move to the newly created driver directory

```
cd ~/src/8821cu-20210916
```

#### Step 8: Run the installation script (`install-driver.sh`)

Important: The compilation may fail if the major version of gcc that is
in use is not the same as the major version of the gcc that was used to
compile the kernel that is in use:

Example of bad situation:

```
gcc 12.1 (used to compile the kernel)
gcc 10.3 (version of gcc in use)
```

Example of good situation:

```
gcc 12.2 (used to compile the kernel)
gcc 12.1 (version of gcc in use)
```

To determine the values:

```
cat /proc/version
```

```
gcc --version
```

If you find your system in a bad situation, it is recommended that you
install a version of gcc that matches the major version of gcc that was
used to compile your kernel. Here is an example for Ubuntu:

```
sudo apt install gcc-12
```

Note: If your system is a low memory system, it is recommended that you
terminate running apps so as to provide the maximum amount of RAM to the
compilation process.

Note: For automated builds (non-interactive), use `NoPrompt` as an
option.

```
sudo ./install-driver.sh
```

or

```
sudo sh install-driver.sh
```

Note: If you elect to skip the reboot at the end of the installation
script, the driver may not load immediately and the driver options will
not be applied. Rebooting is strongly recommended.

Note: Fedora users that have secure boot turned on may need to run the
following to enroll the key:

```
sudo mokutil --import /var/lib/dkms/mok.pub
```

### Manual Installation Instructions

Note: The installation script, install-driver.sh, automates the
installation process, however, if you want to or need to do a basic
command line installation, use the following:

```
make clean
```

```
make -j$(nproc)
```

If secure boot is off:

```
sudo make install
```

```
sudo reboot
```

If secure boot is on:

Note: Please read to the end of this section before coming back here to
enter commands.

```
sudo make sign-install
```

Note: You will be promted for a password, please remember the password
as it will be used in some of the following steps.

```
sudo reboot
```

The MOK managerment screen will appear during boot:

`Shim UEFI Key Management`

`Press any key...`

Select "Enroll key"

Select "Continue"

Select "Yes"

When promted, enter the password you entered earlier.

Warning: If you enter the wrong password, your computer will not be
bootable. In this case, use the BOOT menu from your BIOS to boot then as
follows:

```
sudo mokutil --reset
```

Restart your computer. Use the BOOT menu from BIOS to boot. In the MOK
managerment screen, select `reset MOK list`, then reboot and retry from
the above step `sudo make sign-install`.

Note: If you use the Manual Installation Instructions, you will need to
repeat the installation process each time a new kernel is installed in
your distro.

-----

### Manual Removal Instructions

To remove the driver if installed by the Manual Installation
Instructions:

```
sudo make uninstall
```

```
sudo reboot
```

Note: If you use the manual installation instructions, or if dkms is not
installed, you will need to repeat the process each time a new kernel is
installed in your distro.

-----

### Driver Options (`edit-options.sh`)

Note: In Linux, driver options are called module parameters.

A file called `88x2bu.conf` will be installed in `/etc/modprobe.d` by
default if you use the installation script, `install-driver.sh`. If you
are following the Manual Installation Instructions, you can use the
`edit-options.sh` script to install and/or edit the file.

Note: The installation script, `install-driver.sh`. will prompt you to
edit the options.

`88x2bu.conf` will be read and applied to the driver on each system boot.

To edit the driver options file, run the `edit-options.sh` script

```
sudo ./edit-options.sh
```

Note: Documentation for Driver Options is included in the file
 `8821cu.conf`.

-----

### Upgrading the Driver

Note: Linux development is continuous therefore work on this driver is
continuous.

Note: Upgrading the driver is advised in the following situations:

- if a new or updated version of the driver needs to be installed
- if a distro version upgrade is going to be installed (i.e. going from
kernel 5.10 to kernel 5.15)

#### Step 1: Move to the driver directory

```
cd ~/src/8821cu-20210916
```

#### Step 2: Remove the currently installed driver

```
sudo ./remove-driver.sh
```

#### Step 3: Pull updated code from this repo

```
git pull
```

#### Step 4: Install the driver

```
sudo ./install-driver.sh
```

-----
### Removal of the Driver (`remove-driver.sh`)

Note: Removing the driver is advised in the following situations:

- if driver installation fails
- if the driver is no longer needed

Note: The following removes everything that has been installed, with the
exception of the packages installed in Step 3 and the driver directory.
The driver directory can be deleted after running this script.

#### Step 1: Open a terminal (e.g. Ctrl+Alt+T)

#### Step 2: Move to the driver directory

```
cd ~/src/8821cu-20210916
```

#### Step 3: Run the removal script

Note: For automated builds (non-interactive), use `NoPrompt` as an
option.

```
sudo ./remove-driver.sh
```

-----

### Recommended WiFi Router/ Access Point Settings

Note: These are general recommendations, some of which may not apply to
your specific situation.

- Security: Set WPA2-AES or WPA2/WPA3 mixed or WPA3. Do not set WPA2
mixed mode or WPA or TKIP.

- Channel width for 2.4 GHz: Set 20 MHz fixed width. Do not use 40 MHz
or 20/40 automatic.

- Channels for 2.4 GHz: Set channel 1 or 6 or 11 depending on the
congestion at your location. Do not set automatic channel selection. As
time passes, if you notice poor performance, recheck congestion and set
channel appropriately. The environment around you can and does change
over time.

- Mode for 2.4 GHz: For best performance, set "N only" if you no longer
use B or G capable devices.

- Network names: Do not set the 2.4 GHz Network and the 5 GHz Network
to the same name. Note: Unfortunately many routers come with both
networks set to the same name. You need to be able to control which
network that is in use so changing the name of one of the networks is
recommended. Since many IoT devices use the 2.4 GHz network, it may be
better to change the name of the 5 GHz network.

- Channels for 5 GHz: Not all devices are capable of using DFS channels
(I'm looking at you Roku.) It may be necessary to set a fixed channel in
the range of 36 to 48 or 149 to 165 in order for all of your devices to
work on 5 GHz. (For US, other countries may vary.)

- Best location for the WiFi router/access point: Near center of
apartment or house, at least a couple of feet away from walls, in an
elevated location. You may have to test to see what the best location is
in your environment.

- Check congestion: There are apps available for smart phones that allow
you to get an idea of the congestion levels on WiFi channels. The apps
generally go by the name of `WiFi Analyzer` or something similar.

After making and saving changes, reboot the router.

-----

### Recommendations regarding USB

- Moving your USB WiFi adapter to a different USB port has been known to
fix a variety of problems.

- If connecting your USB WiFi adapter to a desktop computer, use the USB
ports on the rear of the computer. Why? The ports on the rear are
directly connected to the motherboard which will reduce problems with
interference and disconnection.

- If your USB WiFi adapter is USB 3 capable and you want it to operate
in USB3 mode, plug it into a USB 3 port.

- Avoid USB 3.1 Gen 2 ports if possible as almost all currently
available adapters have been tested with USB 3.1 Gen 1 (aka USB 3) and
not with USB 3.1 Gen 2.

- If you use an extension cable and your adapter is USB 3 capable, the
cable needs to be USB 3 capable (if not, you will be limited to USB 2
speeds).

- Extention cables can be problematic. A way to check if the extension
cable is the problem is to plug the adapter temporarily into a USB port
on the computer.

- Some USB WiFi adapters require considerable electrical current and
push the capabilities of the power available via USB port. One example
is adapters that use the Realtek 8814au chipset. Using a powered
multiport USB extension can be a good idea in cases like this.

-----

Contributors:

```
@Jibun-no-Kage
@alkisg
@M0les
@mendel5
@colincdean
@jeff-hiner
@paralin
@tamojitray
@amisix
@henkv1
@SubZero5
```

Without the above contributors, this driver would not be nearly
as good as it.

-----

To Contribute:

Fork this repository.
Make your edits.
TEST THEM!
Create a pull request.

-----

#### [Go to Main Menu](https://github.com/morrownr/USB-WiFi)

-----
