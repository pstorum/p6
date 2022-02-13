#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "p6.h"

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))
#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

struct block *head = NULL;

int main(){
	void *p;

    print_data();
    p = myalloc(16);
    print_data();
    p = myalloc(16);
    printf("%p\n", p);
}

void * myalloc(int allo){
	void *heap = sbrk(1024);
	int padded_block_size;

	if (head == NULL) {
	    head = sbrk(1024);
	    head->next = NULL;
	    head->size = 1024 - PADDED_SIZE(sizeof(struct block));
	    head->in_use = 0;
	}
	struct block *holding = head;

	while(holding != NULL){
		if(holding->in_use == 0){
			struct block *n = holding;

			if (holding->size >= allo){
				n->in_use = 1;
				padded_block_size = PADDED_SIZE(sizeof(struct block));
				return PTR_OFFSET(n, padded_block_size);
			}
		}
		holding = holding->next;
	}
	return NULL;
}

void print_data(void){
	struct block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}