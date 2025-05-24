#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/select.h>
#include <unistd.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv[]) {
    printf("Usage: %s -n -f <file_path>\n", argv[0]);
    printf("\t-n : create new database file.\n");
    printf("\t-f : (required) path to database file.\n");
    return;
}

int main(int argc, char *argv[]) { 
	int c = 0;
    bool newfile = false;
    char *file_path = NULL;
    int dbfd = -1;
    struct employee_t *employees;
    struct employee_t *employeesOut;
    char *employee_string = NULL;

    struct dbheader_t *headerOut = NULL; 
    while((c = getopt(argc, argv, "nf:a:") )!= -1){
        switch (c){
            case 'n':
                newfile = true;
                break;
            case 'f':
                file_path = optarg;
                break;
            case 'a':
                employee_string = optarg;
                break;
            case '?':
                printf("-%s is unkown option\n", optarg);
                break;
            default:
                printf("Error detected\n");
                return -1;
        }
    }
    if(file_path == NULL){
        printf("File Path is a required argument.\n");
        print_usage(argv);
        return 0;
    }

    if(newfile){
        dbfd = create_db_file(file_path);
        if(dbfd == STATUS_ERROR){
            printf("Unable to create database file.\n");
            return -1;
        }
        int header_create = create_db_header(dbfd, &headerOut);
        if(header_create == STATUS_ERROR){
            printf("Was not able to create the header.\n");
            return -1;
        }
    }else{
        dbfd = open_db_file(file_path);
        if(dbfd == STATUS_ERROR){
            printf("Unable to open database file.\n");
            return -1;
        }
        if(validate_db_header(dbfd, &headerOut) == STATUS_ERROR){
            printf("Failed to validate the database header.\n");
            return STATUS_ERROR;
        }
    }

    if(read_employees(dbfd, headerOut, &employeesOut)){
        printf("Reading employees failed. \n");
        return -1;
    }

    if(employee_string){
        employeesOut = realloc(employeesOut, ++headerOut->count*sizeof(struct employee_t));
        if(employeesOut == NULL){
            printf("Realloc for adding employee_failed.\n");
            return STATUS_ERROR;
        }
        add_employee(headerOut, employeesOut, employee_string);
    }
    
    output_file(dbfd,headerOut,employees);

    printf("newfile : %d\n", newfile);
    printf("file_path: %s\n", file_path);
    return 0;
}


/*
* main function and some utility functions are going to be in this file.
*/
