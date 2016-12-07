/* Author: Troy Veldhuizen 
*  Assignment: CS 343 Programming Project Two in C
*  Due Date: Monday, October 10, 2016
*/

#include <stdio.h>
#include <string.h>
#include "const_data.h"
#include "check_file.h"

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

	if(argc != 2){
		printf("%s\n", ARGC_ERROR);
		printf("%s\n", ARG_USAGE);
		return 1;
	}
	
	fin = fopen(argv[1], "r");
	fout = fopen(OUT_FILE, "w");

	if(!fin){
		printf("%s\n", FILE_NOT_FOUND_ERROR);
		return 1;
	}
	
	check_file(fin, fout);
	
	fclose(fin);
	fclose(fout);
	return 0;	
}
