#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include "files_handler.h"

HANDLE CreateFileHandleReadSimple(char* filename);
HANDLE CreateFileHandleWriteSimple(char* filename);


HANDLE CreateFileHandleReadSimple(char* filename)
{
    HANDLE hFile;
    DWORD  dwBytesRead = 0;
    OVERLAPPED ol = { 0 };

 

    hFile = CreateFileA(filename,               // file to open
        GENERIC_READ,          // open for reading
        FILE_SHARE_READ,       // share for reading
        NULL,                  // default security
        OPEN_EXISTING,         // existing file only
        FILE_ATTRIBUTE_NORMAL , // normal file |FILE_FLAG_OVERLAPPED
        NULL);                 // no attr. template

    if (hFile == INVALID_HANDLE_VALUE)
    {
        //DisplayError(TEXT("CreateFile"));
        printf("Terminal failure: unable to open file \"%s\" for read.\n", filename);
        return;
    }

    

    // It is always good practice to close the open file handles even though
    // the app will exit here and clean up open handles anyway.

    return hFile;
   // CloseHandle(hFile);
}
HANDLE CreateFileHandleWriteSimple(char* filename)
{
    HANDLE hFile;
   // char DataBuffer[] = "This is some test data to write to the file.";
    //DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
    DWORD dwBytesWritten = 0;
    BOOL bErrorFlag = FALSE;
   // TCHAR test[200] = { NULL };      ///allocate memory!!!!
    TCHAR *path =  NULL ;
    if (NULL == (path = (TCHAR*)malloc((1 + strlen(filename)) * sizeof(TCHAR))))
    {
        printf("memory allocation failed, exiting");
        exit(1);
    }

    swprintf(path, 1 + strlen(filename), L"%hs", filename);
    hFile = CreateFile(path,                // name of the write
        GENERIC_WRITE,          // open for writing
        FILE_SHARE_WRITE,                      // do not share
        NULL,                   // default security
        OPEN_ALWAYS,             // create new file only
        FILE_ATTRIBUTE_NORMAL,  // normal file
        NULL);                  // no attr. template

    if (hFile == INVALID_HANDLE_VALUE)
    {
 
        printf("Terminal failure: Unable to open file \"%s\" for write.\n", filename);
        return;
    }
    free(path);
    return hFile;
}
