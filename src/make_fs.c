/*
 * make_fs.c
 */

#include "include/revolution.h"
#include <sys/wait.h>
#include <unistd.h>

int make_fs (char* fs, char* disk)
{
    char* command = "mkfs";
    int pid;

    pid = fork();
    if (pid == 0) {
        execl(command, "-t", fs, disk);
    }

    waitpid(pid, NULL, 0);
    return 0;
}
