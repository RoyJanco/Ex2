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
#include "files_handler.h"
#include "DecryptThread.h"


//Macros & definitions

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define BUF_SIZE 1
// Constants -------------------------------------------------------------------

static const int STATUS_CODE_SUCCESS = 0;
static const int STATUS_CODE_FAILURE = -1;


//Declarations
char decrypt_letter(char letter, int key);
char* GetFileDirectory(char path[]);

// Function Definitions --------------------------------------------------------



DWORD WINAPI DecryptThread(LPVOID lpParam)
{
	DECRYPT_THREAD_params_t *p_params;
	char* path = NULL;
	int key = 0, i = 0, thread_num = 0;
	HANDLE hfile_read = NULL;
	HANDLE hfile_write = NULL;
	//FILE* p_output_file = NULL;
	//FILE* p_input_file = NULL;
	errno_t retval_input, retval_output;
	DWORD dwBytesToWrite = 1;
	DWORD dwBytesWritten = 0;
	/* Check if lpParam is NULL */
	if (NULL == lpParam)
	{
		return CAESAR_THREAD__CODE_NULL_PTR;
	}

	/*
	* Convert (void *) to parameters type.
	* In this example, MATH_THREAD_params_t is a simple struct.
	* In general, it could be any type:
	* integer, array, array of struct, string etc.
	*/
	p_params = (DECRYPT_THREAD_params_t*)lpParam;

	hfile_read = CreateFileHandleReadSimple(p_params->path_src);
	hfile_write = CreateFileHandleWriteSimple(p_params->path_dst);

	char inBuffer[BUF_SIZE];
	//char inBuffer = 0;
	int counter = 0;
	DWORD nBytesToRead = 1;
	DWORD dwBytesRead = 0;
	DWORD dwFileSize = GetFileSize(hfile_read, NULL);
	OVERLAPPED stOverlapped = { 0 };
	BOOL bResult = FALSE;
	char temp_char = '0';
	//func (begin)


	SetFilePointer(hfile_read, p_params->start_index, NULL, FILE_BEGIN);

	SetFilePointer(hfile_write, p_params->start_index, NULL, FILE_BEGIN);
	//	while (!(bResult && dwBytesRead == 0)) //whike (n<stop-end)

	while (counter<=(p_params->end_index-p_params->start_index)) //whike (n<stop-end)
	{
		bResult = ReadFile(hfile_read,
			inBuffer,
			nBytesToRead,
			&dwBytesRead,
			NULL);
		//inBuffer[1]='\0';
		//printf("%s", inBuffer);
		temp_char = decrypt_letter(inBuffer[0], p_params->key);
		inBuffer[0] = temp_char;
		WriteFile(hfile_write, inBuffer, dwBytesToWrite, &dwBytesWritten, NULL);
		if (bResult && dwBytesRead == 0)
		{
			printf("End of file\n");
		}
		counter++;
	}

	return CAESAR_THREAD__CODE_SUCCESS;

	// Open files
	/*retval_output = fopen_s(&p_output_file,path,"w");
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
	}*/

}
