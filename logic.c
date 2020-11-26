//File Header
//Authors: Roy janco 311372205 Almog Carmeli 311151070
//Project Casear
//Description: logic.c includes core functions that used by main.c

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

/*
* Returns a path for the output file
* Input Arguments:
*   path: An array of chars, of the input file path
*	operation: An integer indicating encryption or decryption mode.
*	opearion=0 -> decryption; operation=1 -> encyrption
* Return:
*   namecpy: A pointer to the name of the path of the output file
*/
char* GetFileDirectory(char path[], int operation);

/*
* Returns the decrypted or encrypted character given key and flag.
* Input Arguments:
*   letter: a char of the current letter to be decrypted or encrypted.
*	key: An integer of the key of the decryption/encryption
*	flag: An integer indicating encryption or decryption mode.
*	flag=0 -> decryption; flag=1 -> encyrption
* Return:
*   letter: A char of the decryped or encrypted letter.
*/
char decrypt_letter(char letter, int key, int flag);

//void decrypt_file(const FILE* p_read, const FILE* p_write, const int key);

/*
* Counts number of rows in the given file.
* Input Arguments:
*   file_path: a pointer to the file path.
* Return:
*   num_of_rows: An integer of the number of rows in the file.
*/
int get_number_of_rows(char* file_path);

/*
* Counts number of bytes per row in the given file
* Input Arguments:
*   num_of_rows: An integer of number of rows in the file.
*	file_path: a pointer to the file path.
* Output:
*	bytes_per_row: An array of integers.
*	Each element in the array is the number of bytes for the corresponding line in file.
* Return:
*   STATUS_CODE_FAILURE: -1 if could not open file.
*/
int get_bytes_per_row(int* bytes_per_row, int num_of_rows, char* file_path);

/*
* Calculates the parital sum of an array from index start to index end.
* Input Arguments:
*   arr: An array of integers.
*	start: An integer for the start index of the summation.
*	end: An integer for the end index of the summation.
* Return:
*   sum: An integer of the sum of the array.
*/
int partial_sum(int* arr, int start, int end);

/*
* Calculates a modulo b
* Input Arguments:
*   a: An integer a.
*	b: An integer b.
* Return:
*   An integer of the result of a mod b.
*/
int mod_func(int a, int b);

/*
* This function returns 0 for decryption and 1 for encryption.
* Input Arguments:
*	flag: A string that specifies decryption or encrpytion.
*	flag = "-d" -> decryption, flag = "-e" -> encryption.
* Return:
*   0 for decryption, 1 for encryption, else returns -1.
*/
int get_operation(char* flag);

/*Creates output file in write mode. Overruns old file if exists. 
* Input Arguments:
*	path: A pointer to the file path.
* Return:
*	-1 if failed to create file.
*	0 if succeded to create file.
*/
int create_output_file(char* path);

//Implementation

char* GetFileDirectory(char path[],int operation) // if operation=0 decrypt, else encrypt
{
	int i = 0;
	int len = strlen(path) + 15;
	/*Allocate memory for namecpy (path for output file)*/
	char* namecpy = (char*)malloc((len) * sizeof(char));
	if (namecpy == NULL) {
		printf("argument memory allocation failed, exiting...\n ");
		exit(1);
	}

	char decrypted_name[] = "\\decrypted.txt";
	char encrypted_name[] = "\\encrypted.txt";
	strcpy_s(namecpy, len, path);
	
	/*Delete name of the input file from the full path*/
	for (i = len; (namecpy[i] != '\\'); i--);
	namecpy[i] = '\0';
	if (operation == 0)
		strcat_s(namecpy, len, decrypted_name); //concatenate "\decrypted.txt" to path
	else
		strcat_s(namecpy, len, encrypted_name); //concatenate "\encrypted.txt" to path
	return namecpy;
}

char decrypt_letter(char letter, int key,int flag)
{ //this function encrypts the given letter with a given key and flag
	int flag_upper = isupper(letter);
	int flag_number = isdigit(letter);
	char temp = 0;
	int flag_op = (2 * flag) - 1; // flag_op = -1 for decryption, flag_op = 1 for encryption.
	
	
	if (flag_number == 0 && isalpha(letter)) // If current character is a letter
		if (flag_upper) // if letter is uppercase
			
			return 'A' + mod_func((letter - 'A' + flag_op *key),26);
		else // if letter is lowercase
			return 'a' + mod_func((letter - 'a' + flag_op * key), 26);

	else if (flag_number) // if current character is a number
		return '0' + mod_func((letter - '0' + flag_op * key), 10);
	else // if current character is not a letter nor number
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
	if (NULL != p_input_file)
	{
		while (!feof(p_input_file))
		{
			c = fgetc(p_input_file);
			if ('\n' == c)
				num_of_rows++;
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
	if (NULL != p_input_file)
	{
		while (!feof(p_input_file))
		{
			c = fgetc(p_input_file);
			bytes_count++;
			//|| feof(p_input_file)
			if ('\n' == c) //last byte in last row is eof, might be redundant
			{
				bytes_count++; //for CRLF character
				*bytes_per_row = bytes_count;
				bytes_per_row++; //increase pointer of bytes_per_row
				bytes_count = 0;
			}
			else if (feof(p_input_file))
			{
				/*If got to EOF decrease count, since count was increased earlier*/
				bytes_count--;

				*bytes_per_row = bytes_count;
				bytes_per_row++;
				bytes_count = 0;

			}
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
//this function calculates the parital sum of an array from index start to index end
{
	int i = 0;
	int sum = 0;
	for (i=start; i <= end; i++)
		sum  = sum +arr[i];

	return sum;

}

int mod_func(int a,int b)
{//calculate a modulo b. 
	/* We implemented modulo function this way since % operator
	doesn't work negative number*/
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

int create_output_file(char* path)
{
	errno_t retval;
	FILE* p_output_file = NULL;
	/*Open output file in write mode. Overruns old file if exists. */
	retval = fopen_s(&p_output_file, path, "w");
	if (0 != retval)
	{
		printf("Failed to create output file.\n");
		return STATUS_CODE_FAILURE;
	}
	/* Close file */
	if (NULL != p_output_file)
		retval = fclose(p_output_file);
	if (0 != retval)
	{
		printf("Failed to close output file.\n");
		return STATUS_CODE_FAILURE;
	}
	return STATUS_CODE_SUCCESS;
}