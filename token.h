#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

typedef struct s_token Token;

struct s_token {
	char* key;
	size_t nb_val;
	size_t val_cap;
	Token** val;
};

Token* parse(char* text);

#endif
