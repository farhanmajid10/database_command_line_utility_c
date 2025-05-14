#include <stdio.h>
#include <unistd.h>

#include "../include/common.h"
#include "../include/parse.h"

int parse_file_header(int fd, int *num_of_employees){
    if(fd == -1){
        printf("Bad file descriptor.\n");
        return -1;
    }
    struct db_header_t db = {0};
    if( read(fd, &db, sizeof(db)) != sizeof(db)){
        printf("File could not be read.\n");
        return -1;
    } 
    *num_of_employees = db.count;
    return 0;
}

