/*
 * generate_fstab.c
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
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

//#define DEBUGGING

int generate_fstab (char* part, char* fs)
{
    char* path = "/mnt/etc/fstab";
    char* proc_entry = "proc /proc proc nosuid,noexec,nodev 0 0\n";
    char* sysfs_entry = "sysfs /sys sysfs nosuid,noexec,nodev 0 0\n";
    char* devpts_entry = "devpts /dev/pts devpts gid=5,mode=620 0 0\n";
    char* tmpfs_entry = "tmpfs /run tmpfs defaults 0 0\n";
    char* devtmpfs_entry = "devtmpfs /dev devtmpfs mode=0755,nosuid 0 0\n";
    int fd;
    fd = open(path, O_CREAT | O_WRONLY);

    if (fd == -1) {
        #ifdef DEBUGGING
            perror("Can't open/create fstab, error:");
        #endif
        return errno;
    }

    //write root device entry in fstab
    write(fd, part, strlen(part));
    write(fd, " / ", 3);
    write(fd, fs, strlen(fs));
    write(fd, " defaults 1 1\n", 14);

    //write proc entry in fstab
    write(fd, proc_entry, strlen(proc_entry));

    //write sysfs entry
    write(fd, sysfs_entry, strlen(sysfs_entry));

    //write devpts entry
    write(fd, devpts_entry, strlen(devpts_entry));

    //write tmpfs entry
    write(fd, tmpfs_entry, strlen(tmpfs_entry));

    //write devtmpfs entry
    write(fd, devpts_entry, strlen(devpts_entry));

    close(fd);
    return 0;
}
