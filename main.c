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
#include <stdbool.h>



//includes projects
#include "logic.h"
#include "files_handler.h"
#include "DecryptThread.h"


//Macros & definitions

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define BUF_SIZE 1
#define ERROR_CODE ((int)(-1))
#define SUCCESS_CODE ((int)(0))
// Constants -------------------------------------------------------------------

static const int STATUS_CODE_SUCCESS = 0;
static const int STATUS_CODE_FAILURE = -1;


//Declarations
char decrypt_letter(char letter, int key);
char* GetFileDirectory(char path[]);
static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id);

// Function Definitions --------------------------------------------------------

int main(int argc, char* argv[])
{
	char* path = NULL;
	int key = 0, i = 0, thread_num = 0;
	HANDLE thread_handle;
	DWORD thread_id;
	DWORD wait_code;
	DWORD exit_code;
	BOOL ret_val;
	DECRYPT_THREAD_params_t* p_thread_params;
	path = GetFileDirectory(argv[1]);
	key = ((*argv[2])) - '0';
	thread_num = ((*argv[3])) - '0';

	p_thread_params = (DECRYPT_THREAD_params_t*)malloc(sizeof(DECRYPT_THREAD_params_t));
	if (NULL == p_thread_params)
	{
		printf("Error when allocating memory");
		return ERROR_CODE;
	}

	/* Prepare parameters for thread */
	p_thread_params->key = key;
	p_thread_params->end_index = 1;
	p_thread_params->start_index = 1;
	p_thread_params->path_dst = path;
	p_thread_params->path_src = argv[1];


	/* Create thread */
	thread_handle = CreateThreadSimple(DecryptThread, p_thread_params, &thread_id);
	if (NULL == thread_handle)
	{
		printf("Error when creating thread\n");
		return ERROR_CODE;
	}
	/* Wait */
	wait_code = WaitForSingleObject(thread_handle, INFINITE);
	if (WAIT_OBJECT_0 != wait_code)
	{
		printf("Error when waiting\n");
		return ERROR_CODE;
	}

	/* Check the DWORD returned by MathThread */
	ret_val = GetExitCodeThread(thread_handle, &exit_code);
	if (0 == ret_val)
	{
		printf("Error when getting thread exit code\n");
	}

	/* Print results, if thread succeeded */
	if (MATH_THREAD__CODE_SUCCESS == exit_code)
	{
		printf("Succeeded\n");
	}
	else
	{
		printf("Error in thread: %d\n", exit_code);
	}

	/* Free memory */
	free(p_thread_params);

	/* Close thread handle */
	ret_val = CloseHandle(thread_handle);
	if (false == ret_val)
	{
		printf("Error when closing\n");
		return ERROR_CODE;
	}

	return SUCCESS_CODE;

	

	
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

static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id)
{
	HANDLE thread_handle;

	if (NULL == p_start_routine)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	if (NULL == p_thread_id)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	thread_handle = CreateThread(
		NULL,                /*  default security attributes */
		0,                   /*  use default stack size */
		p_start_routine,     /*  thread function */
		p_thread_parameters, /*  argument to thread function */
		0,                   /*  use default creation flags */
		p_thread_id);        /*  returns the thread identifier */

	return thread_handle;
}

