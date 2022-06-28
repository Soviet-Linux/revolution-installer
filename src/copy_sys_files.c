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

int copy_sys_files(char *sq_path, char *target)
{
    char* dest;
    char* force = "-f";
    int pid;
    int* stat;

    dest = (char *) malloc(strlen(target) + 3);
    if (dest == NULL) {
        return -1;
    }

    dest[0] = '\0';
    strcat(dest, "-d");
    strcat(dest, target);

    pid = fork();

    if (pid == 0) {
        execl("/usr/bin/unsquashfs", "revolution-unsquashfs", dest, force, sq_path);
    }

    waitpid(pid, stat, 0);
    free(dest);

    if (*stat == 0) {
        printf("System files copied successfully!\n");
    }
    else {
        printf("Error extracting files using unsquashfs. ERRNO: %d\n", *stat);
        exit(EXIT_FAILURE);
    }

    return 0;
}
