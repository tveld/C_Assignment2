/* Author: Troy Veldhuizen 
*  Assignment: CS 343 Programming Project Two in C
*  Due Date: Monday, October 10, 2016
*/

#include <stdio.h>
#include <string.h>

// constants

// errors
const char* ARGC_ERROR = "Incorrect number of arguments.";
const char* FILE_NOT_FOUND_ERROR = "File not found";
const char* ILLEGAL_OP_ERROR = "Illegal op code found";
const char* OP_CODE_WRONG_COLUMN_ERROR = "Op code in wrong column";
const char* OPER_WRONG_COLUMN_ERROR = "Operand in wrong column";
const char* LABLE_TOO_LONG_ERROR = "The lable is too long";
const char* INVALID_VARIABLE_ERROR = "This is an invalid lable declaration";
const char* COLUMN_8_ERROR = "Column 8 should be blank";
const char* COLUMN_9_ERROR = "Column 9 should be blank";
const char* COLUMN_1_ERROR = "Column 1 invalid character";
const char* LINE_SIZE_ERROR = "Line has exceeded 71 characters";

// messages
const char* ARG_USAGE = "Usage: bms_process [in-file]";
const char* END_OF_PROCESSING = "End of Processing: %d errors encountered\n";

// files
const char* OUT_FILE = "BMSOut.txt";


// Error codes
const int ILLEGAL_OP = 2;
const int OP_CODE_WRONG_COLUMN = 3;
const int OPER_WRONG_COLUMN = 4;
const int LABLE_TOO_LONG = 5;
const int INVALID_VARIABLE = 6;
const int COLUMN_8 = 7;
const int COLUMN_9 = 8;
const int END = 9;

// function declarations


/* Author: Troy Veldhuizen 
*  Purpose: Loops through file, line by line. Calls appropriate
*			check function and writes output. Also counts errors.
*  Inputs: Input File, and Output file
*  Outputs: Void
*  Error Handleing: None
*/
void check_file(FILE *inf, FILE *outf);


/* Author: Troy Veldhuizen 
*  Purpose: Checks that all variable
*			line constraints are met
*  Outputs: int: Error code, or 0
*  Error Handleing: None
*/
int check_variable(char *line);


/* Author: Troy Veldhuizen 
*  Purpose: Checks that all space line
*			constraints are met
*  Outputs: int: Error code, or 0
*  Error Handleing: None
*/
int check_space(char *line);


/* Author: Troy Veldhuizen 
*  Purpose: Checks if a string is an op
*  Outputs: 1 if op, 0 if not
*  Error Handleing: None
*/
int check_op(char *word);


/* Author: Troy Veldhuizen 
*  Purpose: Creates input and output files,
*			and checks cmd line args.  Calls
			check_file() function.
*  Outputs: int, return state
*  Error Handleing: File not found
*/
int main(int argc, char *argv[])
{
	FILE *fin, *fout;
	
	// check number of args
	if(argc != 2){
		printf("%s\n", ARGC_ERROR);
		printf("%s\n", ARG_USAGE);
		return 1;
	}
	
	fin = fopen(argv[1], "r");
	fout = fopen(OUT_FILE, "w");
	
	// check file not found
	if(!fin){
		printf("%s\n", FILE_NOT_FOUND_ERROR);
		return 1;
	}
	
	check_file(fin, fout);
	
	fclose(fin);
	fclose(fout);
	return 0;	
}


/* Author: Troy Veldhuizen 
*  Purpose: Loops through file, line by line. Calls appropriate
*			check function and writes output. Also counts errors.
*  Inputs: Input File, and Output file
*  Outputs: Void
*  Error Handleing: None
*/
void check_file(FILE *inf, FILE *outf)
{
	int i, output, errorcnt = 0;
	char line[100], first;
	
	// loop through and get each line
	while(fgets(line, 100, inf) != NULL){
	
		first = line[0];

		fprintf(outf, "%s", line);
		
		// is comment
		if(first == '*'){
		// nothing to check for comment
		
		// is space
		} else	if(first == ' '){
			output = check_space(line);
			
			// check for errors
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
				printf(END_OF_PROCESSING, errorcnt);
				return;
			}	
		// is variable
		} else if(isalpha(first)) {
			output = check_variable(line);
			
			// check for errors
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

		// check if line exeeds 71 characters with non extend characters
		if(strlen(line) >71){
			for(i = 71; i < (strlen(line) -1); ++i){
				if(line[i] != 'X' && !(isspace(line[i]))){
					fprintf(outf,"%s\n", LINE_SIZE_ERROR); 
					i = 100;
				}
			}

		}
	} // end while
}


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

	// check if lable is too long
	if(strlen(word) > 7){
		return LABLE_TOO_LONG;
	}
	
	// check if variable is all uppercase
	for(i = 0; i < strlen(word); ++i){
		if(!isupper(word[i])){
			return INVALID_VARIABLE;
		}
	}
	
	// check columns 8 and 9
	if(line[7] != 32){
		return COLUMN_8;
	} else if(line[8] != 32){
		return COLUMN_9;
	}
	
	is_op = check_op(op);
	
	// check Op is illegal
	if(isupper(line[9])){
		if(is_op == 0){
			return ILLEGAL_OP;
		}
	} else if(is_op == 1){
		return OP_CODE_WRONG_COLUMN;
	}
}

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
	
	// compair op	
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

