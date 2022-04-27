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

int copy_sys_files()
{
    char* command = "/usr/bin/tar";
    int pipefd[2];
    int pid1, pid2;

    if (pipe(pipefd)) {
        printf("Error creating pipe\n");
        return -1;
    }

    (pid1 = fork()) && (pid2 = fork());

    if (pid1 == 0) {
        if (pipefd[1] != 0) {
            dup2(pipefd[1], 1);
            close(pipefd[1]);
            close(pipefd[0]);
        }

        if(execl(command,
                    "revolution-tar-producer",
                    "--create",
                    "--one-file-system",
                    "--xattrs",
                    "--file=-",
                    "/")) {
            puts(strerror(errno));
            exit(127);
        }
    }

    else if (pid2 == 0) {
        if (pipefd[0] != 0) {
            dup2(pipefd[0], 0);
            close(pipefd[1]);
            close(pipefd[0]);
        }

        if(execl(command,
                    "revolution-tar-consumer",
                    "--extract",
                    "--xattrs",
                    "--xattrs-include='*'",
                    "--preserve-permissions",
                    "-v",
                    "-f-",
                    "-C/mnt")) {
            puts(strerror(errno));
            exit(127);
        }
    }

    else {
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }

    return 0;
}
