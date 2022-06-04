/*
 * copy_sys_files.c
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
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUNDLEPATH "/run/initramfs/memory/data/soviet-linux/01-core.sb"

int copy_sys_files(char *sq_path, char *target)
{
    char *command = "/usr/bin/unsquashfs";
    char* args[] = {"revolution-unsquashfs", "-x", "-li", "-f", "-d"};
    char path[100];

    int *stat;

    int pid = fork();

    if (pid == 0) {
        strcpy(path, args[4]);
        strcat(path, target);
        execl(command, args[0], args[1], args[2], args[3], path, sq_path);
    }

    waitpid(pid, stat, 0);

    if (*stat != 0) {
        printf("Error extracting files from squashfs image\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
