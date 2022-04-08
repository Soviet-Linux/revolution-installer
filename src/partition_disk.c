/*
 * partition_disk.c
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

    command = (char*) malloc(sizeof(char) * 12);
    if (command == NULL) {
        return -1;
    }

    if (choice) {
        strcpy(command, "/bin/cfdisk");
    }
    else {
        strcpy(command, "/bin/fdisk");
    }

    pid = fork();

    if (pid == 0) {
        execl(command, disk);
    }

    waitpid(pid, NULL, 0);
    free(command);

    return 0;
}
