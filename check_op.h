/* Author: Troy Veldhuizen 
*  Assignment: CS 343 Programming Project Two in C
*  Due Date: Monday, October 10, 2016
*/

/* Author: Troy Veldhuizen 
*  Purpose: Checks if a string is an op
*  Outputs: 1 if op, 0 if not
*  Error Handleing: None
*/
int check_op(char *word)
{
	char *op0 = "DFHMDI";
	char *op1 = "DFHMDF";
	char *op2 = "DFHMSD";
	char *end = "END";
	
	if(strcmp(word, op0) == 0){
		return 1;
	} else if(strcmp(word, op1) == 0){
		return 1;
	} else if(strcmp(word, op2) == 0){
		return 1;
	} else if(strcmp(word, end) == 0){
		return 1;
	} else {
		return 0;
	}
}
