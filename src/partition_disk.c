/*
 * partition_disk.c
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
#include "include/revolution.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

int partition_disk (char* disk)
{
    char* command;
    int pid, status;

    command = (char*) malloc(sizeof(char) * 20);
    if (command == NULL) {
        return -1;
    }

    strcpy(command, "/usr/sbin/cfdisk");

    pid = fork();

    if (pid == 0) {
        execl(command, "revolution-cfdisk", disk);
    }

    waitpid(pid, &status, 0);
    free(command);
    return status;
}

int list_dev()
{
    struct dirent *de;

    DIR *dir = opendir("/dev/");

    if (dir == NULL) {
        printf("Failed to open /dir/\n");
        return 1;
    }

    while ((de = readdir(dir)) != NULL) {
        if (strncmp(de->d_name, "sd", 2) == 0 ||
                strncmp(de->d_name, "nvme0",5) == 0) {
            printf("/dev/%s\n", de->d_name);
        }
    }

    closedir(dir);
    return 0;
}

int dpart_loop()
{
    char disk_path[100];
    int rc = 1;

    do {
        printf("Enter a disk to edit (c to continue, l to list disks): ");
        scanf("%s", disk_path);
        if (strcmp(disk_path, "q") == 0) {
            rc = 0;
        }
        else if (strcmp(disk_path, "l") == 0) {
            list_dev();
        }
        else {
            partition_disk(disk_path);
        }
    } while (rc);

    return rc;
}
