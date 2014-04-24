#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <cstdlib>
#include <cstdio>

int initMas(int mas[]);
int *charToInt(char string[]);
char *intToChar(int mas[]);
int lenMas(int mas[]);
int sum(int mas1[], int mas2[]);
int *multi(int mas[]);
int *intToMas(int num);
char *hexToDec(char string[]);
bool correct_file_name(char file_name[]);
int strScan(char* str, FILE* file);
char *out_file_name(char in_name[]);
int file_convert(char path_from[], char path_to[]);
int console_convert();