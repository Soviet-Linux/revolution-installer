/*
 * main.c
 */
/*
 * This file is part of revolution-installer.
 * revolution-installer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * revolution-installer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with revolution-installer. If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright 2022 AntaresMKII
 */
/*
 * The main function should walk the user though the setup process following the
 * following steps:
 * 1. Display available keyboards layout and prompt the user for a valid keyboard
 * layout
 * 2. Prompt the user for a hostname
 * 3. Display available locales and prompt the user for a valid one
 * 4. Display available time zones and prompt the user for a valid one
 * 5. Prompt the user for a root password
 * 6. Prompt the user for a username and password. Allow also the user to set
 * user groups
 * 7. Display available devices and prompt the user for a device where to install
 * GRUB
 * 8. Prompt the user for a choice of cfdisk or fdisk, if user chooses cfdisk
 * display the devices available and prompt the user for one
 * 9. Display and prompt the user for a device and a file system
 * 10. Review the installation settings
 * 11. Install the system:
 *      a. Format and install filesystem
 *      b. Mount the drives
 *      c. Copy the system
 *      d. Set the hostname
 *      e. Set the locale
 *      f. Set the timezone
 *      g. Set the timezone
 *      h. Set root password
 *      i. Create the username and set groups
 *      j. Create /etc/fstab
 *      k. Install GRUB
 *      l. Reboot
 */

#include "include/revolution.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define SQ_PATH "/run/initramfs/memory/data/soviet-linux/01-core.sb"

void get_str(int len, char *arr)
{
	char ch;
	register int len_incr = -1;
	
	do {
	    *(arr+len_incr) = ch;
	    len_incr++;
    } while((ch=getchar()) != 13 && len_incr < len);
	
	*(arr + len) = '\0';
}

int main (int argc, char** argv)
{

    p_list part_list;
    part_list.first = NULL;

    printf("=== Disk Partition ===\n");
    if (dpart_loop()) {
        printf("Error partitioning drive\nQuitting...\n");
        exit(EXIT_FAILURE);
    }

    printf("=== File System Creation ===\n");
    if (fs_loop(&part_list)) {
        printf("Error creating file system!\n Quitting...\n");
        exit(EXIT_FAILURE);
    }

    printf("=== Mount Setup ===\n");
    mount_setup(&part_list);

    printf("=== Mounting Root File System ===\n");
    mount_root(&part_list);

    printf("=== Mounting Remaining Devices ===\n");
    mount_dev(&part_list);

    printf("=== Generating Base Directories ===\n");
    gen_base_dir();

    printf("=== Extracting Squashfs Image ===\n");
    copy_sys_files(SQ_PATH, "/mnt/");

    printf("=== Mounting Virtual Kernel File System ===\n");
    if (mount_virtkfs() == -1) {
        printf("Error Mounting virtual kernel file system. ERRNO: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("=== Entering chroot Environment ===\n");
    chroot("/mnt/");

    printf("=== Generating fs tab ===\n");
    if (0 != generate_fstab(&part_list)) {
        printf("Error generating fstab. ERRNO:%s\n", strerror(errno));
    }

    printf("=== Setting up Boot Loader ===\n");
    move_boot_dir();
    create_grub_conf(&part_list);

    printf("=== Rebooting! ===\n");
    system("shutdown -r now");

    return 0;
}
