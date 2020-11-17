//File Header
//Authors: Roy janco 311372205 Almog Carmeli 311151070
//Project Father
//Description: father_func.h includes functions that are used by main.c

//Macros & definitions

#ifndef __logic_h__
#define __logic_h__


// Function Declarations -------------------------------------------------------
char* GetFileDirectory(char path[], int operation);
char decrypt_letter(char letter, int key, int flag);
//void decrypt_file(const FILE* p_read, const FILE* p_write, const int key);
int get_number_of_rows(char* file_path);
int get_bytes_per_row(int* bytes_per_row, int num_of_rows, char* file_path);
int partial_sum(int* arr, int start, int end);
int mod_func(int a, int b);
int get_operation(char* flag);

#endif // !__logic_h__


