#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

typedef struct s_elt Elt;
struct s_elt {
	Elt* next;
	void* data;
};

typedef struct{
	Elt* head;
}Stack;

void stack_push(Stack* stack, void* elt);
void* stack_pop(Stack* stack);
#endif
