//File Header
//Authors: Roy janco 311372205 Almog Carmeli 311151070
//Project Caesar
//Description: main.c includes functions that are used by main.c

// Includes --------------------------------------------------------------------
#include <string.h>
#include <limits.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//includes projects
#include "logic.h"



//Macros & definitions

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

// Constants -------------------------------------------------------------------

static const int STATUS_CODE_SUCCESS = 0;
static const int STATUS_CODE_FAILURE = -1;


//Declarations
char decrypt_letter(char letter, int key);
char* GetPath(char path[]);

// Function Definitions --------------------------------------------------------

int main(int argc, char* argv[])
{
	char* path = NULL;
	int key = 0;
	int i = 0;
	FILE* p_output_file = NULL;
	FILE* p_input_file = NULL;
	errno_t retval_input, retval_output;

	path = GetPath(argv[1]);
	key = ((*argv[2])) - '0';
	printf("%c", decrypt_letter('y',3));



	// Open files
	retval_output = fopen_s(&p_output_file,path,"w");
	if (0 != retval_output)
	{
		printf("Failed to open output file.\n");
		return STATUS_CODE_FAILURE;
	}
	retval_input = fopen_s(&p_input_file, argv[1], "r");
	if (0 != retval_input)
	{
		printf("Failed to open input file.\n");
		return STATUS_CODE_FAILURE;
	}

	// Do something...
	decrypt_file(p_input_file, p_output_file, key);

	// Close files
	if(NULL!=p_output_file)
		retval_output = fclose(p_output_file);
	if(NULL!=p_input_file)
		retval_input = fclose(p_input_file);
	if (0 != retval_output)
	{
		printf("Failed to close output file.\n");
		return STATUS_CODE_FAILURE;
	}
	if (0 != retval_input)
	{
		printf("Failed to close input file.\n");
		return STATUS_CODE_FAILURE;
	}

}

/*void main(int argc, char* argv[])
{
	printf("%s\n", argv[1]);
	encrypt_letter('6', 2);
	char buf[100];
	realpath("this_source.c", buf);
}
*/

