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
 * Copyright 2022 Yannick Abouem
 */

#include "include/revolution.h"
#include <sys/wait.h>
#include <unistd.h>

int copy_sys_files()
{
    char* command = "cp";
    char* opt = "-axvnu";
    char* root = "/";
    char* target = "/mnt/";

    int pid;

    pid = fork();
    if (pid == 0) {
        execl(command, opt, root, target);
    }

    waitpid(pid, NULL, 0);

    return 0;
}
