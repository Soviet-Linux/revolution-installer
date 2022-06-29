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
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int copy_sys_files(char *sq_path, char *target)
{
    int pid;
    int stat;

    pid = fork();

    if (pid == 0) {
        execl("/usr/bin/unsquashfs", "revolution-unsquashfs", "-d", target, sq_path, "*");
    }

    waitpid(pid, NULL, 0);

    return 0;
}

int move_boot_dir()
{
    if (rename("/boot2", "/boot") != 0) {
        printf("Error moving boot directory. ERRNO: %s\n", strerror(errno));
    }

    return 0;
}

int gen_base_dir()
{
    mkdir("/mnt/dev", 0555);
    mkdir("/mnt/media", 0555);
    mkdir("/mnt/mnt", 0755);
    mkdir("/mnt/proc", 0555);
    mkdir("/mnt/run", 0555);
    mkdir("/mnt/sys", 0555);
    mkdir("/mnt/tmp", 0555);

    return 0;
}

int create_grub_conf(p_list* list)
{
    part* root = list->first;
    char* path = "/boot/grub/grub.cfg";
    int fd;
    char* buff;
    char* grub_disk; //for grub disk format
    char sndlast;

    while (root != NULL) {
        if (strcmp(root->mnt_point, "/")) {
            break;
        }

        root = root->next;
    }

    if (root == NULL) {
        return -1;
    }

    //this is not the best way to do this... Will need some rework

    fd = open(path, O_CREAT | O_WRONLY);

    buff = "set default=0\nset timeout=5\n\ninsmod ext2\nset root=";
    write(fd, buff, strlen(buff));

    sndlast = root->path[strlen(root->path) -2];

    if (sndlast == 'a') {
        sndlast = '0';
    }
    else if (sndlast == 'b') {
        sndlast = '1';
    }
    else if (sndlast == 'c') {
        sndlast = '2';
    }
    else {
        printf("This program can't count above 3! You will have to configure the rest of %s by yourself.\n", path);
    }

    grub_disk = (char*) malloc(7);
    grub_disk = strcat("(hd", &sndlast);
    grub_disk = strcat(grub_disk, &root->path[strlen(root->path)-1]);
    grub_disk = strcat(grub_disk, ")");

    buff = grub_disk;
    write(fd, buff, strlen(buff));

    buff = "\n\nmenuentry \"Soviet Linux\" {\n\tlinux /boot/vmlinuz root=";
    write(fd, buff, strlen(buff));
    write(fd, root->path, strlen(root->path));

    buff = " ro\n}";

    close(fd);

    return 0;
}
