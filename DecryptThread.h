// IO_Thread.h

/*
* A thread that adds up to numbers.
*/

#ifndef __DecryptThread_H__
#define __DecryptThread_H__

// Includes --------------------------------------------------------------------

#include <windows.h>

// Types -----------------------------------------------------------------------

/*
* A type for thread return codes
*/
typedef enum
{
	CAESAR_THREAD__CODE_SUCCESS,
	CAESAR_THREAD__CODE_NULL_PTR,
} CAESAR_THREAD__return_code_t;

/*
* A type for thread parameters
*/
typedef struct
{
	char* path_src;
	char* path_dst;
	int start_index;
	int end_index;
	int key;
} DECRYPT_THREAD_params_t;

// Function Declarations -------------------------------------------------------

/*
* Math thread. This thread adds up to numbers.
*/
DWORD WINAPI DecryptThread(LPVOID lpParam);

#endif // __DecryptThread_H__