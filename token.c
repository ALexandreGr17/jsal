#include "token.h"
#include "stack.h"
#include <stdlib.h>
#include <sys/types.h>

enum parser_state {
	NORMAL,
	VAL,
	KEY
};

void token_init(Token* token){
	token->key = NULL;
	token->nb_val = 0;
	token->val_cap = 10;
	token->val = malloc(sizeof(Token*) * token->val_cap);
}

char is_writable_char(char c){
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') 
		|| c == '(' || c == ')' || c == '_' || c == '"';
}

void strcopy(const char* s1, char* s2){
	for(size_t i = 0; s1[i]; i++){
		s2[i] = s1[i];
	}
}

Token* parse(char* text){
	while(*text != '{'){
		text++;
	}
	
	Stack stack = {0};
	enum parser_state state = NORMAL;
	size_t buffer_size = 100;
	char* buffer = malloc(buffer_size);
	Token* token = malloc(sizeof(Token));
	token_init(token);
	stack_push(&stack, token);
	token->val[0] = malloc(sizeof(Token));
	token = token->val[0];
	token_init(token);
	
	size_t index_buffer = 0;

	while (*text) {
		switch (state) {
			case VAL:
				if (*text == ':' || (!is_writable_char(*text) && *text != ' ')){
					state = KEY;
					text--;
					break;
				}
				if(index_buffer+1 >= buffer_size){
					buffer_size += 20;
					buffer = realloc(buffer, buffer_size);
				}
				buffer[index_buffer] = *text;
				buffer[index_buffer+1] = 0;
				index_buffer++;
				break;

			case KEY:
				token->key = calloc(sizeof(char), index_buffer+1);
				strcopy(buffer, token->key);
				index_buffer = 0;
				stack_push(&stack, (void*)token);
				if(token->nb_val >= token->val_cap){
					token->val_cap += 10;
					token->val = realloc(token->val, sizeof(Token*) * token->val_cap);
				}
				token->val[token->nb_val] = malloc(sizeof(Token));
				token = token->val[token->nb_val];
				token_init(token);
				state = NORMAL;
				break;

			case NORMAL:
				if (is_writable_char(*text)) {
					state = VAL;
					text--;
				}
				else if (*text == ','){
					token->key = calloc(sizeof(char), index_buffer+1);
					strcopy(buffer, token->key);
					if(!token->nb_val){
						free(token->val);
						token->val = NULL;
						token->val_cap = 0;
					}
					index_buffer = 0;
					token = stack_pop(&stack);
					token->nb_val++;
				}
				break;
		}
		text++;
	}
	token->key = calloc(sizeof(char), index_buffer+1);
	strcopy(buffer, token->key);
	if(!token->nb_val){
		free(token->val);
		token->val = NULL;
		token->val_cap = 0;
	}
	token = stack_pop(&stack);
	token->nb_val++;
	
	free(buffer);
	return token;
}



/* 
 * " -> val
 * : -> key
 * * -> NORMAL
 * */
