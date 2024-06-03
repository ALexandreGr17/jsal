#include "stack.h"
#include <stdlib.h>

void stack_push(Stack *stack, void* elt){
	Elt* new_elt = malloc(sizeof(Elt));
	new_elt->data = elt;
	new_elt->next = stack->head;
	stack->head = new_elt;
}

void* stack_pop(Stack *stack){
	Elt* old_head = stack->head;
	stack->head = old_head->next;
	void* data = old_head->data;
	free(old_head);
	return data;
}
