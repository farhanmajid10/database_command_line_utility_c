#ifndef PARSE_H
#define PARSE_H

struct db_header_t{
    unsigned short version;
    unsigned short count;
};
int parse_file_header(int fd, int *num_of_employees);

#endif // !PARSE_H
