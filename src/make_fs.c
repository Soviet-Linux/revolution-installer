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
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int make_fs (char* fs, char* disk)
{
    char* command = "/usr/sbin/mkfs";
    int pid;
    char* fs_arg;

    fs_arg = strcat("-t ", fs);

    pid = fork();
    if (pid == 0) {
        execl(command, fs_arg, disk);
    }

    waitpid(pid, NULL, 0);
    return 0;
}
