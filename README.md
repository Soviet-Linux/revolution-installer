# revolution-installer
The installer of the Soviet-Linux operating system.

## Functionality
The installer will follow this steps to install the system:

1. Display available keyboards layout and prompt the user for a valid keyboard
layout
2. Prompt the user for a hostname
3. Display available locales and prompt the user for a valid one
4. Display available time zones and prompt the user for a valid one
5. Prompt the user for a root password
6. Prompt the user for a username and password. Allow also the user to set
user groups
7. Display available devices and prompt the user for a device where to install
GRUB
8. Prompt the user for a choice of cfdisk or fdisk, if user chooses cfdisk
display the devices available and prompt the user for one
9. Display and prompt the user for a device and a file system
10. Review the installation settings
11. Install the system:
12. Format and install filesystem
13. Mount the drives
14. Copy the system
15. Set the hostname
16. Set the locale
17. Set the timezone
18. Set the timezone
19. Set root password
20. Create the username and set groups
21. Create /etc/fstab
22. Install GRUB
23. Reboot

## Development & Contributing
Read the [development docs](https://github.com/Soviet-Linux/delevopment-docs) for more info.
To contribute create a branch and choose an installer step to implement. To
keep the code organized please create a new file under the `src` folder and use
one function, with the same name as the file, as the entry point. Once you have
completed your implementation make a pull request and await for it to be merged.

## Usage
First compile the program using make in the root directory of the program
`# make`, then run it `./bin/revolution`.

To install in the system move the executable into `/bin` or `/usr/bin` if `/bin`
is a symlink.

## TODO
- Add user creation
- Set root password
- Set keyboard layout
- Set hostname
- Set locale and timezone
- Install GRUB
- Recompile kernel
