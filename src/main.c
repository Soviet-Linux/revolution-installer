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
    char* disk;
    char* fs;
    char* part;

    printf("\t\t***Welcome to Revolution!***\n\n##############################\n");
    printf("\nThe 'revolutionary' installer for Soviet Linux\n\n##############################\n");

    printf("Select a tool to partition the drive: \n1) fdisk\n2) cfdisk\n");

    do {
        scanf("%[^\n]", buf);

        if (strcmp(buf, "1") == 0) {
            isCfdisk = 1;
            break;
        }
        else if (strcmp(buf, "2") == 0) {
            isCfdisk = 0;
            break;
        }

        printf("Please enter 1 or 2\n");
    } while(1);

    printf("Enter a disk to edit: ");
    scanf("%[^\n]", buf);

    disk = (char*) malloc(sizeof(char) * strlen(buf));
    strcpy(disk, buf);


    printf("Select a file system to make: (only ext4 is supported for now) ");
    scanf("%[^\n]", buf);

    fs = (char*) malloc(sizeof(char) * strlen(buf));
    strcpy(disk, buf);

    printf("Select a partition to create a file system on: ");
    scanf("%[^\n]", buf);

    part = (char*) malloc(sizeof(char) * strlen(buf));
    strcpy(disk, part);


    printf("The system will be installed on %s using file system %s. Continue? [y/n] ", part, fs);
    scanf("%[^\n]", buf);

    if (strcmp(buf, "y") == 0) {

        partition_disk(isCfdisk, disk);
        make_fs(fs, part);
        copy_sys_files();
    }

    printf("Finished!");

    return 0;
}
