#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "parse.h"

void list_employees(struct dbheader_t *dbhdr, struct employee_t *employees) {

}

int add_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addstring) {

}

int read_employees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut) {

}

int output_file(int fd, struct dbheader_t *dbhdr, struct employee_t *employees) {

}	

int validate_db_header(int fd, struct dbheader_t **headerOut) {
    if(fd == -1){
        printf("File Descriptor is corrupted.\n");
        return STATUS_ERROR;
    }
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if(header == NULL){
        printf("Calloc didn't work for the header file, check.\n");
        return STATUS_ERROR;
    }

    if(read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t)){
        perror("read");
        free(header);
        return STATUS_ERROR;
    }

    header->version = ntohs(header->version);
    header->count = ntohs(header->count);
    header->filesize = ntohs(header->filesize);
    header->magic = ntohl(header->magic);

    if(header->version != 1){
        free(header);
        printf("Header version is improper.\n");
        return STATUS_ERROR;
    }
    if(header->magic != HEADER_MAGIC){
        free(header);
        printf("Header magic is not accurate.\n");
        return STATUS_ERROR;
    }

    struct stat db_stat = {0};

    fstat(fd, &db_stat);
    if(header->filesize != db_stat.st_size){
        free(header);
        printf("Corrupted file. Different filesize.\n");
        return STATUS_ERROR;
    }
    

    
}

int create_db_header(int fd, struct dbheader_t **headerOut) {
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if(header == NULL){
        printf("Calloc did not work to create dbheader.\n");
        return STATUS_ERROR;
    }

    header->magic = HEADER_MAGIC;
    header->version = 1;
    header->count = 0;
    header->filesize = sizeof(struct dbheader_t);
    *headerOut = header;

    return STATUS_SUCCESS;
}


/*
* This file is going to do the bulk of the work. It will have all the heavy lifting functions. This will be responsible for 
* taking the data in the database file, parsing it and then expanding it into the employee structure in memory and then 
* collapsing it back into the file again at the end of program execution.
*/
