/*
 * main.c
 */

#include "include/revolution.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    char buf[256];
    char isCfdisk;
    char disk[256];
    char fs[256];
    char part[256];
    char buf2[256];

    printf("\t\t***Welcome to Revolution!***\n\n##############################\n");
    printf("\nThe 'revolutionary' installer for Soviet Linux\n\n##############################\n");

    printf("Select a tool to partition the drive: \n1) fdisk\n2) cfdisk\n");

    do {
        scanf("%s", buf);

        if (strcmp(buf, "1") == 0) {
            isCfdisk = 0;
            break;
        }
        else if (strcmp(buf, "2") == 0) {
            isCfdisk = 1;
            break;
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
        make_fs(fs, part);
        copy_sys_files();
    }

    printf("Finished!");

    return 0;
}
