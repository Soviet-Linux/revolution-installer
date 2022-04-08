/*
 * copy_sys_files.c
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
