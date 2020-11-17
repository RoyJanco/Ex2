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
#define TIMEOUT_IN_MILLISECONDS 10000
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define BUF_SIZE 1
#define ERROR_CODE ((int)(-1))
#define SUCCESS_CODE ((int)(0))
// Constants -------------------------------------------------------------------

static const int STATUS_CODE_SUCCESS = 0;
static const int STATUS_CODE_FAILURE = -1;
int flag_operation = 0;

//Declarations
static HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id);

// Function Definitions --------------------------------------------------------

int main(int argc, char* argv[])
{
	int N=0,mod = 0, lines=0 ,pre_lines = 0;
	char* path = NULL;
	int key = 0, i = 0, thread_num = 0, num_of_rows = 0;
	int* bytes_per_row = NULL;
	DWORD *thread_id; ///malloc to size of threadnum
	DWORD wait_code, exit_code;
	BOOL ret_val,is_error_exitcode=FALSE, is_error_closing_thread= FALSE;
	DECRYPT_THREAD_params_t** p_thread_params;
	flag_operation = get_operation(argv[4]);
	if (flag_operation == -1)
	{
		printf("Invalid input, exiting");
		exit(1);
	}
	path = GetFileDirectory(argv[1],flag_operation);
	key = atoi(argv[2]);
	thread_num = atoi(argv[3]);
	HANDLE *p_thread_handles = (HANDLE*)malloc(thread_num*sizeof(HANDLE));


	/* Get number of rows and bytes per row in "top_secret_file.txt" */
	// call this func
	num_of_rows = get_number_of_rows(argv[1]);
	if (NULL == (bytes_per_row = (int*)malloc(num_of_rows * sizeof(int))))
	{
		printf("memory allocation failed, exiting"); //check memory
		exit(1);
	}
	if(NULL== (thread_id= (DWORD*)malloc(num_of_rows * sizeof(DWORD))))///check
	{
		printf("memory allocation failed, exiting");
		exit(1);

	}
	get_bytes_per_row(bytes_per_row, num_of_rows, argv[1]); //last byte in last row is eof, might be redundant

	if (NULL == (p_thread_params = (DECRYPT_THREAD_params_t**)malloc(thread_num * sizeof(DECRYPT_THREAD_params_t*))))
	{
		printf("memory allocation failed, exiting\n");
		exit(1);
	}
	for (i = 0; i < thread_num; i++) {

		p_thread_params[i] = (DECRYPT_THREAD_params_t*)malloc( sizeof(DECRYPT_THREAD_params_t));
		{
			if (p_thread_params[i] == NULL)
			{
				printf("memory allocation failed, exiting\n");
				exit(1);
			}
		}

	}
	 N = num_of_rows / thread_num;
	 mod= num_of_rows % thread_num;
	for(i=0;i< thread_num;i++)
	{ 
		if (mod > 0)
		{
			lines = N + 1;
			mod--;
		}
		else
			lines = N;
		/* Prepare parameters for thread */
		if (NULL == p_thread_params[i])
		{
			printf("Error when allocating memory");
			return ERROR_CODE;
		}
		if (i==0)
		{
			
			p_thread_params[i]->key = key;
			p_thread_params[i]->end_index = partial_sum(bytes_per_row,0,lines-1)-1;
			p_thread_params[i]->start_index = 0;
			p_thread_params[i]->path_dst = path;
			p_thread_params[i]->path_src = argv[1];
		}
		else
		{
			p_thread_params[i]->key = key;
			p_thread_params[i]->start_index = (p_thread_params[i - 1]->end_index + 1);
			p_thread_params[i]->end_index =( p_thread_params[i]->start_index+(partial_sum(bytes_per_row, pre_lines,pre_lines+lines-1)))-1;
			p_thread_params[i]->path_dst = path;
			p_thread_params[i]->path_src = argv[1];
		}
		pre_lines = pre_lines + lines;

	}

	/* Create thread */
	for (i = 0; i < thread_num; i++)
	{
		p_thread_handles[i] = CreateThreadSimple(DecryptThread, p_thread_params[i], &thread_id[i]);
		if (NULL == p_thread_handles[i])
		{
			printf("Error when creating thread\n");
			return ERROR_CODE; 
		}
	}
	/* Wait */
	wait_code = WaitForMultipleObjects(thread_num, p_thread_handles,TRUE, TIMEOUT_IN_MILLISECONDS); //wait for multi not infinite
	if (WAIT_OBJECT_0 != wait_code)
	{
		printf("Error when waiting\n");
		return ERROR_CODE;
	}
	for (i = 0; i < thread_num; i++)
	{
		/* Check the DWORD returned by MathThread */
		ret_val = GetExitCodeThread(p_thread_handles[i], &exit_code);
		if (0 == ret_val)
		{
			printf("Error when getting thread exit code\n");
		}

		/* Print results, if thread succeeded */
		if (CAESAR_THREAD__CODE_SUCCESS == exit_code)
		{
			printf("Thread %d Succeeded\n",thread_id[i]);
		}
		else
		{
			printf("Error in thread %d: %d\n", thread_id[i], exit_code);
		}
		is_error_exitcode = (is_error_exitcode || !ret_val); //error in exitcode
	}
	/* Close thread handle */
	for (i = 0; i < thread_num; i++) 
		
	{
		ret_val = CloseHandle(p_thread_handles[i]);
		is_error_closing_thread = is_error_closing_thread || (!ret_val);
		if (false == ret_val) // error in closing handle
		{
			printf("Error when closing %d\n", thread_id[i]);
			//return ERROR_CODE;
		}
	}
	/* Free memory */
	free(thread_id);
	free(p_thread_params);
	free(path);
	free(bytes_per_row);
	free(p_thread_handles);
	if (is_error_closing_thread || is_error_exitcode)
		return ERROR_CODE;
	return SUCCESS_CODE;
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

