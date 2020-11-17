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
extern int flag_operation;

//Declarations
//char decrypt_letter(char letter, int key);
//char* GetFileDirectory(char path[]);

// Function Definitions --------------------------------------------------------



DWORD WINAPI DecryptThread(LPVOID lpParam)
{
	DECRYPT_THREAD_params_t *p_params;
	char* path = NULL;
	int key = 0, i = 0, thread_num = 0;
	HANDLE hfile_read = NULL;
	HANDLE hfile_write = NULL;
	errno_t retval_input, retval_output;
	DWORD dwBytesToWrite = 1;
	DWORD dwBytesWritten = 0;
	
	/* Check if lpParam is NULL */
	
	if (NULL == lpParam)
	{
		return CAESAR_THREAD__CODE_NULL_PTR;
	}

	/* Convert (void *) to parameters type.*/
	
	p_params = (DECRYPT_THREAD_params_t*)lpParam;

	hfile_read = CreateFileHandleReadSimple(p_params->path_src);
	hfile_write = CreateFileHandleWriteSimple(p_params->path_dst);

	char inBuffer[BUF_SIZE];
	int counter = 0;
	DWORD nBytesToRead = 1;
	DWORD dwBytesRead = 0;
	DWORD dwFileSize = GetFileSize(hfile_read, NULL);
	OVERLAPPED stOverlapped = { 0 };
	BOOL bResult = FALSE;
	char temp_char = '0';


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
		temp_char = decrypt_letter(inBuffer[0], p_params->key, flag_operation);
		inBuffer[0] = temp_char;
		WriteFile(hfile_write, inBuffer, dwBytesToWrite, &dwBytesWritten, NULL);
		if (bResult && dwBytesRead == 0)
		{
			printf("End of file\n");
		}
		counter++;
	}
	CloseHandle(hfile_read);
	CloseHandle(hfile_write);
	return CAESAR_THREAD__CODE_SUCCESS;


}
