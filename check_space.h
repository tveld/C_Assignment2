/* Author: Troy Veldhuizen 
*  Assignment: CS 343 Programming Project Two in C
*  Due Date: Monday, October 10, 2016
*/
#include "check_op.h"
#include <stdio.h>
#include <ctype.h>

/* Author: Troy Veldhuizen 
*  Purpose: Checks that all space line
*			constraints are met
*  Outputs: int: Error code, or 0
*  Error Handleing: None
*/
int check_space(char *line){
	int i, pos, is_op;
	char word[71];

	// grab first word
	sscanf(line, "%s", word);
	
	// find first position
	for(i = 0; i < strlen(line); ++i){
		if(!isspace(line[i])){
			pos = i;
			i = strlen(line);
		}
	}
	
	// check if end
	if(strcmp(word, "END") == 0){
		return END;
	}
	// check if possible op
	is_op = check_op(word);

	if((pos == 9) && ((is_op != 1) && (strlen(word) == 6))){
		return ILLEGAL_OP;
	} else if((pos != 9) && (is_op == 1)){
		return OP_CODE_WRONG_COLUMN;
	} else if((pos != 15) && (is_op != 1)){
		return OPER_WRONG_COLUMN;
	} else {
		return 0;
	} 
}



