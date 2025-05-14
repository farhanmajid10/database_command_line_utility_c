#include <stdio.h>
#include "../include/file.h"
#include "../include/parse.h"

int main(int argc, char** argv){
       int num_of_employees = 0;
    if(argc < 2){
        printf("%s <file_name>\n", argv[0]);
        return 0;
    }
    int fd = open_file_rw(argv[1]);
    if(fd == -1){
        return -1;
    }
    if(parse_file_header(fd, &num_of_employees)){
        return -1;
    }

    printf("Number of Employees stored: %d\n", num_of_employees);

    return 0;
}
