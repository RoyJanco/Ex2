//File Header
//Authors: Roy janco 311372205 Almog Carmeli 311151070
//Project Father
//Description: father_func.c includes functions that are used by main.c

//Macros & definitions


//Library Includes
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

//Project Includes
#include "logic.h"

//Declarations
char* GetPath(char path[]);
char decrypt_letter(char letter, int key);
void decrypt_file(const FILE* p_read, const FILE* p_write, const int key);


char* GetPath(char path[])
{
	int i = 0;
	int len = strlen(path) + 15;
	char* namecpy = (char*)malloc((len) * sizeof(char));
	if (namecpy == NULL) {
		printf("argument memory allocation failed, exiting...\n ");
		exit(1);
	}

	char decrypted_name[] = "\\decrypted.txt";
	strcpy_s(namecpy, len, path);
	for (i = len; (namecpy[i] != '\\'); i--);
	namecpy[i] = '\0';
	strcat_s(namecpy, len, decrypted_name);
	return namecpy;
}

char decrypt_letter(char letter, int key)
{ //this function encrypts the given letter with a given key
	int flag_upper = isupper(letter);
	int flag_number = isdigit(letter);
	if (flag_number == 0)
		if (flag_upper) //if letter
			return 'A' + (letter - 'A' - key) % 26;
		else
			return 'a' + (letter - 'a' - key) % 26;
	else //if digit
		return '0' + (letter - '0' - key) % 10;

}

void decrypt_file(const FILE* p_read,const FILE* p_write,const int key)
{
	char read_letter = 0;
	while (!feof(p_read))
	{
		read_letter = fgetc(p_read);
		if (isdigit(read_letter) || isalpha(read_letter))
			read_letter = (decrypt_letter(read_letter,key));
		fputc(read_letter, p_write);

	}



}