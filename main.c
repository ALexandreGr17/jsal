#include <stdio.h>
#include "token.h"
int main(void) {
	char* test_json = "{\ntest: {test2:true, test1:false}, test3:maybe";
	Token* json = parse(test_json);
	return 0;
}
