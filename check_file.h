/* Author: Troy Veldhuizen 
*  Assignment: CS 343 Programming Project Two in C
*  Due Date: Monday, October 10, 2016
*/
#include "check_space.h"
#include "check_variable.h"


/* Author: Troy Veldhuizen 
*  Purpose: Loops through file, line by line. Calls appropriate
*			check function and writes output. Also counts errors.
*  Inputs: Input File, and Output file
*  Outputs: Void
*  Error Handleing: None
*/
void check_file(FILE *inf, FILE *outf)
{
	int i,output, errorcnt = 0;
	char line[100], first;
	
	while(fgets(line, 100, inf) != NULL){
	
		first = line[0];

		fprintf(outf, "%s", line);

		// is comment
		if(first == '*'){
		// nothing to check for comment
		
		// is space
		} else	if(first == ' '){
			output = check_space(line);
			
			if(output == ILLEGAL_OP){
				fprintf(outf,"%s\n", ILLEGAL_OP_ERROR);
				errorcnt++;
			} else if(output == OP_CODE_WRONG_COLUMN){
				fprintf(outf,"%s\n", OP_CODE_WRONG_COLUMN_ERROR);
				errorcnt++;
			} else if(output == OPER_WRONG_COLUMN){
				fprintf(outf,"%s\n", OPER_WRONG_COLUMN_ERROR);
				errorcnt++;
			} else if(output == END){
				fprintf(outf, END_OF_PROCESSING, errorcnt);
				return;
			}	
		// is variable
		} else if(isalpha(first)) {
			output = check_variable(line);
			
			if(output == LABLE_TOO_LONG){
				fprintf(outf,"%s\n", LABLE_TOO_LONG_ERROR);
				errorcnt++;
			} else if(output == INVALID_VARIABLE){
				fprintf(outf, "%s\n", INVALID_VARIABLE_ERROR);
				errorcnt++;
			} else if(output == COLUMN_8){
				fprintf(outf,"%s\n", COLUMN_8_ERROR);
				errorcnt++;
			} else if(output == COLUMN_9){
				fprintf(outf,"%s\n", COLUMN_9_ERROR);
				errorcnt++;
			} else if(output == ILLEGAL_OP){
				fprintf(outf,"%s\n", ILLEGAL_OP_ERROR);
				errorcnt++;
			} else if(output == OP_CODE_WRONG_COLUMN){
				fprintf(outf,"%s\n", OP_CODE_WRONG_COLUMN_ERROR);
				errorcnt++;
			}
		// column 1 error
		} else {
			fprintf(outf,"%s\n", COLUMN_1_ERROR);
			errorcnt++;
		}
	} // end while
}
