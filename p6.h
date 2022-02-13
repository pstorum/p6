// llist.h

#ifndef P6_H
#define P6_H

struct block {
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
};

void * myalloc(int allo);
void print_data(void);

#endif