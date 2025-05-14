#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/file.h"

int open_file_rw(char* file_name){
    int fd = open(file_name, O_RDWR);
    if(fd < 0){
        perror("open");
        return -1;
    }

    return fd;
}
/*
* The main thing this file is doing at the moment is just opening the file and then giving the number they associated with the file that
* we mentioned.
*/
