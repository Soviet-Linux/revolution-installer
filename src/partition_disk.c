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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int partition_disk (char choice, char* disk)
{
    char* command;
    int pid;

    command = (char*) malloc(sizeof(char) * 20);
    if (command == NULL) {
        return -1;
    }

    if (choice) {
        strcpy(command, "/usr/sbin/cfdisk");

        pid = fork();

        if (pid == 0) {
            execl(command, "revolution-cfdisk", disk);
        }
    }
    else {
        strcpy(command, "/bin/fdisk");

        pid = fork();

        if (pid == 0) {
            execl(command, "");
        }
    }

    waitpid(pid, NULL, 0);
    free(command);

    return 0;
}
