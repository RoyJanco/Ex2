#include <string.h>
#include <limits.h> 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>




//#include <libgen.h>
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

char encrypt_letter(char letter, int key);
char* GetPath(char path[]);


char* GetPath(char path[])
{
	int i = 0;
	int len = strlen(path)+15;
	char * namecpy = (char*)malloc((len) * sizeof(char));
	if (namecpy == NULL) {
		printf("argument memory allocation failed, exiting...\n ");
		exit(1);
	}

	char encrypted_name[] = "\\decrypted.txt";
	strcpy_s(namecpy,len, path);
	for (i = len; (namecpy[i] != '\\') ; i--);
	namecpy[i] = '\0';
	strcat_s(namecpy,len,encrypted_name);
	return namecpy;
}

int main(int argc, char* argv[])
{
	char* path = NULL;
	path=GetPath(argv[1]);
	int key = 0;
	int i = 0;
	key = ((*argv[2]))-'0';
	FILE* p_output_file = NULL;
	FILE* p_input_file = NULL;

	fopen_s(&p_output_file,path,"w");
	fopen_s(&p_input_file, argv[1], "r");

}

/*void main(int argc, char* argv[])
{
	printf("%s\n", argv[1]);
	encrypt_letter('6', 2);
	char buf[100];
	realpath("this_source.c", buf);
}
*/

char encrypt_letter(char letter,int key)
{ //this function encrypts the give letter with a given key
	int flag_upper = isupper(letter);
	int flag_number = isdigit(letter);
	if (flag_number == 0)
		if (flag_upper)
			return 'A' + (letter - 'A' - key) % 26;
		else
			return 'a' + (letter - 'a' - key) % 26;
	else
		return '0' + (letter - '0' - key) % 10;
	
}
