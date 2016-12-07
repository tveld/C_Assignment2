/* Author: Troy Veldhuizen 
*  Assignment: CS 343 Programming Project Two in C
*  Due Date: Monday, October 10, 2016
*/

/* Author: Troy Veldhuizen 
*  Purpose: Checks that all variable
*			line constraints are met
*  Outputs: int: Error code, or 0
*  Error Handleing: None
*/
int check_variable(char *line){
	char word[71], op[6];
	int i, is_op;
	
	sscanf(line, "%s %s", word, op);

	if(strlen(word) > 7){
		return LABLE_TOO_LONG;
	}
	
	for(i = 0; i < strlen(word); ++i){
		if(!isupper(word[i])){
			return INVALID_VARIABLE;
		}
	}
	
	if(line[7] != 32){
		return COLUMN_8;
	} else if(line[8] != 32){
		return COLUMN_9;
	}
	
	is_op = check_op(op);

	if(isupper(line[9])){
		if(is_op == 0){
			return ILLEGAL_OP;
		}
	} else if(is_op == 1){
		return OP_CODE_WRONG_COLUMN;
	}
}
