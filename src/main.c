/*
 * main.c
 */

#include "include/revolution.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    partition_disk(1, "/dev/sda");

    return 0;
}
