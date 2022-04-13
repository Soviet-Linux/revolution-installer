/*
 * mount_setup.c
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>

void sl_mnt_part(struct part* part) {
    char* path;
    path = (char*) malloc(strlen(part->mnt_point));
    strcpy(path, part->mnt_point);

    mount(part->dev, path, part->fs, 0, NULL);

    free(path);
}

void cleanup(struct part* part) {
    free(part->mnt_point);
    free(part->dev);
    free(part->fs);
    free(part);
}

int mount_setup()
{
    char mnt_point[256];
    char mnt_dev[256];
    char fs_type[256];

    struct part* part_list;

    do {
        printf("Enter a device to mount (type q to quit): ");
        scanf("%[^\n]", mnt_dev);

        if (strcmp(mnt_dev, "q") == 1) {
            break;
        }

        printf("Enter a mounting point for %s: ", mnt_dev);
        scanf("%[^\n]", mnt_point);

        printf("Enter the filesystem type: ");
        scanf("%[^\n]", fs_type);

        part_list = (struct part*) malloc(sizeof(struct part));
        if (part_list == NULL) {
            fprintf(stderr, "ERROR: failed to allocate memory for part_list\n");
            return -1;
        }

        part_list->dev = (char*) malloc(strlen(mnt_dev));
        part_list->mnt_point = (char*) malloc(strlen(mnt_point));
        part_list->fs = (char*) malloc(strlen(fs_type));

        if (
                part_list->dev       == NULL ||
                part_list->fs        == NULL ||
                part_list->mnt_point == NULL
        ) {
            fprintf(stderr, "ERROR: failed to allocate memory for part_list elements\n");
            return -1;
        }

        strcpy(part_list->dev, mnt_dev);
        strcpy(part_list->mnt_point, mnt_point);
        strcpy(part_list->fs, fs_type);

        printf("Mounting partition\n");
        sl_mnt_part(part_list);
    } while (1);

    cleanup(part_list);

    return 0;
}
