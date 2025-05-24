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
    
    printf("%s\n",addstring);

    char *name = strtok(addstring, ",");
    char *address = strtok(NULL, ",");
    char *hours = strtok(NULL, ",");

    strncpy(employees[dbhdr->count - 1].name, name, sizeof(employees[dbhdr->count - 1].name));
    strncpy(employees[dbhdr->count - 1].address, address, sizeof(employees[dbhdr->count - 1].address));

    employees[dbhdr->count - 1].hours = atoi(hours);

    printf("%s:%s:%d\n",employees[dbhdr->count - 1].name, employees[dbhdr->count - 1].address, employees[dbhdr->count - 1].hours);

    return STATUS_SUCCESS;
}

int read_employees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut) {
    if(fd < 0){
        printf("Corrupt file descriptor for reading employees\n");
        return STATUS_ERROR;
    }
    struct employee_t *employees = calloc(0, sizeof(struct employee_t));
    if(employees == NULL){
        printf("Calloc failed in read_employees.\n");
        return STATUS_ERROR;
    }
    int num_of_employees = dbhdr->count;

    read(fd, employees, sizeof(struct employee_t) * num_of_employees);
    
    for(int i = 0; i < num_of_employees; i++){
        employees[i].hours = ntohl(employees[i].hours);
    }
    
    *employeesOut = employees;

    return STATUS_SUCCESS;
}

int output_file(int fd, struct dbheader_t *dbhdr, struct employee_t *employees) {
    if(fd < 0){
        printf("Corrupted file descriptor.\n");
        return STATUS_ERROR;
    }
    dbhdr->count = htons(dbhdr->count);
    dbhdr->filesize = htonl(dbhdr->filesize);
    dbhdr->magic = htonl(dbhdr->magic);
    dbhdr->version = htons(dbhdr->version);

    lseek(fd, 0, SEEK_SET);

    write(fd, dbhdr, sizeof(struct dbheader_t));
    return STATUS_SUCCESS;
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
    header->filesize = ntohl(header->filesize);
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
    *headerOut = header;
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
