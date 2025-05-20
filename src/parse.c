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

}

int create_db_header(int fd, struct dbheader_t **headerOut) {
	
}


/*
* This file is going to do the bulk of the work. It will have all the heavy lifting functions. This will be responsible for 
* taking the data in the database file, parsing it and then expanding it into the employee structure in memory and then 
* collapsing it back into the file again at the end of program execution.
*/
