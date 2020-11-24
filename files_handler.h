//File Header
//Authors: Roy janco 311372205 Almog Carmeli 311151070
//Project Father
//Description: file_handler.h includes functions that create handle for read or write files

#include <Windows.h>

//Macros & definitions

#ifndef __files_handler_h__
#define __files_handler_h__


// Function Declarations -------------------------------------------------------
HANDLE CreateFileHandleReadSimple(char* filename);
HANDLE CreateFileHandleWriteSimple(char* filename);



#endif // !__files_handler_h__


