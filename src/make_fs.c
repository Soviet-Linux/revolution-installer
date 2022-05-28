/*
 * make_fs.c
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
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int make_fs (char* fs, char* disk)
{
    char* command = "/usr/sbin/mkfs";
    int pid;
    char* fs_arg = (char*) malloc(strlen(fs) + 3);
    if (fs_arg == NULL) {
        return -1;
    }

    fs_arg[0] = '\0';
    strcat(fs_arg, "-t");
    strcat(fs_arg, fs);

    pid = fork();
    if (pid == 0) {
        execl(command, "revolution-mkfs", fs_arg, disk);
    }

    waitpid(pid, NULL, 0);
    free(fs_arg);
    return 0;
}

int fs_loop(p_list *list)
{
    char part_path[100];
    char file_sys[100];
    char sel;
    int rc = 1;
    part *curr;

    do {
        printf("Enter a partition for file system creation: (c to continue, l to list disks): ");
        scanf("%s", part_path);
        if (strcmp(part_path, "c") == 0) {
            rc = 0;
            break;
        }
        else if (strcmp(part_path, "l") == 0) {
            list_dev();
        }

        printf("Enter a file system to use (c to continue): ");
        scanf("%s", file_sys);
        if (strcmp(file_sys, "c") == 0) {
            rc = 0;
        }
        else if (strcmp(file_sys, "ext4") != 0) {
            printf("This file system is not supported yet.\n");
        }
        else {
            make_fs(file_sys, part_path);

            curr = (part *) malloc(sizeof(part));
            curr->path = (char *) malloc(strlen(part_path));
            curr->fs = (char *) malloc(strlen(file_sys));

            if (curr == NULL || curr->path == NULL || curr->fs == NULL) {
                exit(EXIT_FAILURE);
            }

            strcpy(curr->path, part_path);
            strcpy(curr->fs, file_sys);

            if (list->first == NULL) {
                list->first = curr;
            }

            curr = curr->next;
        }

    } while (rc);

    return rc;
}
