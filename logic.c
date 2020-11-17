//File Header
//Authors: Roy janco 311372205 Almog Carmeli 311151070
//Project Father
//Description: father_func.c includes functions that are used by main.c

//Macros & definitions


//Library Includes
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

//Project Includes
#include "logic.h"

// Constants
static const int STATUS_CODE_SUCCESS = 0;
static const int STATUS_CODE_FAILURE = -1;

//Declarations
char* GetFileDirectory(char path[], int operation);
char decrypt_letter(char letter, int key, int flag);
//void decrypt_file(const FILE* p_read, const FILE* p_write, const int key);
int get_number_of_rows(char* file_path);
int get_bytes_per_row(int* bytes_per_row, int num_of_rows, char* file_path);
int partial_sum(int* arr, int start, int end);
int mod_func(int a, int b);
int get_operation(char* flag);


char* GetFileDirectory(char path[],int operation) // if operation=0 decrypt, else encrypt
{
	int i = 0;
	int len = strlen(path) + 15;
	char* namecpy = (char*)malloc((len) * sizeof(char));
	if (namecpy == NULL) {
		printf("argument memory allocation failed, exiting...\n ");
		exit(1);
	}

	char decrypted_name[] = "\\decrypted.txt";
	char encrypted_name[] = "\\encrypted.txt";
	strcpy_s(namecpy, len, path);
	for (i = len; (namecpy[i] != '\\'); i--);
	namecpy[i] = '\0';
	if (operation == 0)
		strcat_s(namecpy, len, decrypted_name);
	else
		strcat_s(namecpy, len, encrypted_name);
	return namecpy;
}

char decrypt_letter(char letter, int key,int flag)
{ //this function encrypts the given letter with a given key
	int flag_upper = isupper(letter);
	int flag_number = isdigit(letter);
	char temp = 0;
	int flag_op = (2 * flag) - 1;
	if (flag_number == 0 && isalpha(letter))
		if (flag_upper) //if letter
			
			return 'A' + mod_func((letter - 'A' + flag_op *key),26);
		else
			return 'a' + mod_func((letter - 'a' + flag_op * key), 26);

	else if (flag_number)
		return '0' + mod_func((letter - '0' + flag_op * key), 10);
	else
		return letter;
}
int get_number_of_rows(char* file_path)
{
	errno_t retval;
	FILE* p_input_file = NULL;
	char c = 0;
	int num_of_rows = 1; // minimum number of rows is 1

	// Open file
	retval = fopen_s(&p_input_file, file_path, "r");
	if (0 != retval)
	{
		printf("Failed to open input file.\n");
		return STATUS_CODE_FAILURE;
	}
	// Parse file and count number of rows
	while (!feof(p_input_file))
	{
		c = fgetc(p_input_file);
		if ('\n' == c)
			num_of_rows++;
	}

	// Close file

	if (NULL != p_input_file)
		retval = fclose(p_input_file);
	if (0 != retval)
	{
		printf("Failed to close input file.\n");
		return STATUS_CODE_FAILURE;
	}
	return num_of_rows;
}

int get_bytes_per_row(int *bytes_per_row, int num_of_rows, char *file_path)
{
	errno_t retval;
	FILE* p_input_file = NULL;
	char c = 0;
	int bytes_count = 0; // minimum number of rows is 1

	// Open file
	retval = fopen_s(&p_input_file, file_path, "r");
	if (0 != retval)
	{
		printf("Failed to open input file.\n");
		return STATUS_CODE_FAILURE;
	}
	// Parse file and count number of rows
	while (!feof(p_input_file))
	{
		c = fgetc(p_input_file);
		bytes_count++;
		//|| feof(p_input_file)
		if ('\n' == c ) //last byte in last row is eof, might be redundant
		{
			bytes_count++; //for CRLF character
			*bytes_per_row = bytes_count;
			bytes_per_row++;
			bytes_count = 0;
		}
		else if (feof(p_input_file))
		{
			bytes_count--;

			*bytes_per_row = bytes_count;
			bytes_per_row++;
			bytes_count = 0;

		}
	}

	// Close file

	if (NULL != p_input_file)
		retval = fclose(p_input_file);
	if (0 != retval)
	{
		printf("Failed to close input file.\n");
		return STATUS_CODE_FAILURE;
	}
	return STATUS_CODE_SUCCESS;
}



int partial_sum(int* arr,int start,int end)
//this function calculates the parital sum of an array from index 0 to index k
{
	int i = 0;
	int sum = 0;
	for (i=start; i <= end; i++)
		sum  = sum +arr[i];

	return sum;

}

int mod_func(int a,int b)
{//calculate the modulu of a number 
	int i = 0;
	if (a >= 0)
		return a % b;
	else
		do(a = a + b);
	while (a < 0);

	return a % b;

}

int get_operation(char* flag)
/* this function return 0 for decryption and 1 for encryption*/
{
	
	if (!strcmp(flag, "-e"))
		return 1;
	else if (!strcmp(flag, "-d"))
		return 0;
	else
		return -1;
}