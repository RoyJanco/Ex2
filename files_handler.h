//File Header
//Authors: Roy janco 311372205 Almog Carmeli 311151070
//Project Father
//Description: father_func.h includes functions that are used by main.c

#include <Windows.h>

//Macros & definitions

#ifndef __files_handler_h__
#define __files_handler_h__


// Function Declarations -------------------------------------------------------
HANDLE CreateFileHandleReadSimple(char* filename);
HANDLE CreateFileHandleWriteSimple(char* filename);



#endif // !__files_handler_h__


