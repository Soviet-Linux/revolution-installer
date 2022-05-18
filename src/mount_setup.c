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
 * Copyright 2022 AntaresMKII
 */
#include "include/revolution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>

int mount_setup(p_list *list)
{
    char mnt_point[100];
    part *curr = list->first;

    if (curr == NULL) {
        return 1;
    }

    printf("Choose the mounting point for the following partitions.\n");
    printf("You can continue to the next step by entering c.\n");

    while (curr != NULL) {
        printf("Partition %s of type %s :", curr->path, curr->fs);
        scanf("%s", mnt_point);

        if (strcmp(mnt_point, "c") == 0) {
            break;
        }
        else {
            curr->mnt_point = (char *) malloc(strlen(mnt_point));
            strcpy(curr->mnt_point, mnt_point);

            curr = curr->next;
        }
    }

    return 0;
}
