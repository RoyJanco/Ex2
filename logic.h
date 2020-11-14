//File Header
//Authors: Roy janco 311372205 Almog Carmeli 311151070
//Project Father
//Description: father_func.h includes functions that are used by main.c

//Macros & definitions

#ifndef __logic_h__
#define __logic_h__


// Function Declarations -------------------------------------------------------
char* GetPath(char path[]);
char decrypt_letter(char letter, int key);
void decrypt_file(const FILE* p_read, const FILE* p_write, const int key);




#endif // !__logic_h__


