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
void get_str(int len, char *arr){
char ch;
register int len_incr=0;
while((ch=getchar())!=13&&len_incr<len){
		*(arr+len_incr)=ch;
		len_incr++;
	}
	*(arr+len)='\0';
	}
int main (int argc, char** argv)
{
    char buf[2];
    char isCfdisk;
    char disk[256];
    char fs[256];
    char part[256];
    char buf2[256];

    printf("***Welcome to Revolution!***\n\n##############################\n");
    printf("\nThe 'revolutionary' installer for Soviet Linux\n\n##############################\n");

    printf("Select a tool to partition the drive: \n1) fdisk\n2) cfdisk\n");

    do {
        get_str(1,buf);
        if (strcmp(buf, "1") == 0) {
            char confirm[2];
            printf("Are you sure you want to use fdisk?(Y/N):");
            get_str(1,confirm);
            if(strcmp(confirm,"Y")==0){
            isCfdisk = 0;
            break;
            }
            else{
              printf("\nPlease enter 1 or 2\n");
              strcpy(buf,"");
            }
        }
        else if (strcmp(buf, "2") == 0) {
            char confirm[2];
            printf("Are you sure you want to use cfdisk?(Y/N):");
            get_str(1,confirm);
            if(strcmp(confirm,"Y")==0){
            isCfdisk = 1;
            break;
            }
            else{
              printf("\nPlease enter 1 or 2\n");
              strcpy(buf,"");
            }
        }

        printf("Please enter 1 or 2\n");
        strcpy(buf, "");

    } while(1);



    printf("Enter a disk to edit: ");
    scanf("%s", disk);
    printf("%s\n", disk);

    partition_disk(isCfdisk, disk);

    printf("Select a file system to make: (only ext4 is supported for now) ");
    scanf("%s", fs);

    printf("Select a partition to create a file system on: ");
    scanf("%s", part);

    printf("The system will be installed on %s using file system %s. Continue? [y/n] ", part, fs);
    scanf("%s", buf2);

    if (strcmp(buf2, "y") == 0) {
        printf("[1] Making file system\n");
        make_fs(fs, part);
        printf("[2] Mounting root file system\n");
        mount_setup(part, fs);
        printf("[3] Copying system\n");
        copy_sys_files();
        printf("[4] Generating fstab\n");
        generate_fstab(part, fs);
    }

    printf("Finished!\n");

    return 0;
}
