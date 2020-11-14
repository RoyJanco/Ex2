#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include "files_handler.h"

#define BUFFERSIZE 100
HANDLE CreateFileHandleReadSimple(char* filename);
HANDLE CreateFileHandleWriteSimple(char* filename);


HANDLE CreateFileHandleReadSimple(char* filename)
{
    HANDLE hFile;
    DWORD  dwBytesRead = 0;
    char   ReadBuffer[BUFFERSIZE] = { 0 };
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
        printf(TEXT("Terminal failure: unable to open file \"%s\" for read.\n"), filename);
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
    TCHAR test[200] = { NULL };      ///allocate memory!!!!
    swprintf(test, 200, L"%hs", filename);
    hFile = CreateFile(test,                // name of the write
        GENERIC_WRITE,          // open for writing
        FILE_SHARE_WRITE,                      // do not share
        NULL,                   // default security
        OPEN_ALWAYS,             // create new file only
        FILE_ATTRIBUTE_NORMAL,  // normal file
        NULL);                  // no attr. template

    if (hFile == INVALID_HANDLE_VALUE)
    {
 
        printf(TEXT("Terminal failure: Unable to open file \"%s\" for write.\n"), filename);
        return;
    }

    return hFile;

}
