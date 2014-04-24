// Semestr 4 Laba 1

#include "HexToDec.h"

int initMas(int mas[]){
	for (int i = 0; i < 300; i++)
	{
		mas[i] = 0;
	}
	return 0;
}
int *charToInt(char string[]) {
	int *temp;
	temp = (int*)malloc(sizeof(int)* 300);
	initMas(temp);
	int len = strlen(string);
	for (int i = 0; i <len; i++)
	{
		if (string[i]>47 && string[i] < 58)
			temp[len - i - 1] = string[i] - 48;
		else if (string[i]>64 && string[i] < 71)
			temp[len - i - 1] = string[i] - 65 + 10;
		else
			return NULL;
	}
	return temp;
}
char *intToChar(int mas[]){
	char *string;
	string = (char*)malloc(sizeof(char)* 300);
	int len = lenMas(mas);
	if (len == 0)
	{
		string[0] = '0';
		string[1] = '\0';
	}
	else
	{
		for (int i = 0; i < len; i++)
		{
			string[i] = mas[len - i - 1] + 48;
		}
		string[len] = '\0';
	}
	return string;
}
int lenMas(int mas[]){
	for (int i = 299; i >= 0; i--)
	{
		if (mas[i] != 0)
			return i + 1;
	}
	return 0;
}
int sum(int mas1[], int mas2[]) {
	int len1 = lenMas(mas1);
	int len2 = lenMas(mas2);
	int len;
	if (len1 > len2)
		len = len1;
	else
		len = len2;
	for (int i = 0; i < len; i++)
	{
		mas1[i] = mas2[i] + mas1[i];
	}
	for (int i = 0; i < len; i++)
	{
		if (mas1[i] >= 10)
		{
			mas1[i] = mas1[i] - 10;
			mas1[i + 1] = mas1[i + 1] + 1;
		}
	}
	return 0;
}
int *multi(int mas[]){
	int *temp;
	temp = (int*)malloc(sizeof(int)* 300);
	initMas(temp);
	int len = lenMas(mas);

	for (int i = len; i > 0; i--)
	{
		temp[i] = mas[i - 1];
	}
	temp[0] = 0;

	for (int i = 0; i < 6; i++)
	{
		sum(temp, mas);
	}

	return temp;
}
int *intToMas(int num){
	int *temp;
	temp = (int*)malloc(sizeof(int)* 300);
	initMas(temp);
	temp[0] = num % 10;
	temp[1] = num / 10;
	return temp;
}
char *hexToDec(char string[]){
	int *temp;
	temp = (int*)malloc(sizeof(int)* 300);
	initMas(temp);
	int *result;
	result = (int*)malloc(sizeof(int)* 300);
	initMas(result);
	char *resultS;
	temp = charToInt(string);
	int len = lenMas(temp);
	for (int i = len - 1; i > 0; i--)
	{
		sum(result, intToMas(temp[i]));
		result = multi(result);
	}
	sum(result, intToMas(temp[0]));
	resultS = intToChar(result);
	free(result);
	free(temp);
	return resultS;
}
bool correct_file_name(char file_name[]){
    int l = strlen(file_name);
    if (file_name[l - 4] == '.' && file_name[l - 3] == 't' 
        && file_name[l - 2] == 'x' && file_name[l - 1] == 't')
        return true;
    else
        return false;  
} 
int strScan(char* str,FILE* file){
    int i =0;
    int len = 0;
    if (str==NULL)
        str = (char*)malloc(sizeof(char)*301);
    char c = getc(file);
    while (c!='\n'){    
        if (i<300){
            str[i]= c;
            len++;
        } 
        c = getc(file);
        i++;
    }
    str[len]='\0';
    if (len == i) 
        return 0;
    else
        return 1;
}
char *out_file_name(char in_name[]){
    char *out_name;
    out_name = (char *)malloc(sizeof(char)* 300);
    int i;
    int l = strlen(in_name);
    for (i = 0; i < l - 4; i++)
        out_name[i] = in_name[i];
    out_name[i] = '.';	out_name[i + 1] = 'o';	out_name[i + 2] = 'u';	out_name[i + 3] = 't';
    out_name[i + 4] = '.';	out_name[i + 5] = 't';	out_name[i + 6] = 'x';	out_name[i + 7] = 't';
    out_name[i + 8] = '\0';
    return out_name;
}
int file_convert(char path_from[], char path_to[]) {
    FILE *from, *to;
    char string[301];
    if (correct_file_name(path_from) && (from = fopen(path_from, "r"))){
        if (to = fopen(path_to, "w")){
            strScan(string, from);
            fprintf(to, "%s", hexToDec(string));
            fclose(from);
            fclose(to);
            return 0;
        }
        else{
            printf("Error writing to file.»\n");
                return 1;
        }
    }
    else{
        printf("Incorrect filename or file not found. \n");
        return console_convert();
    }
}
int console_convert(){
    char string[301];
    printf("Enter string to process: \n");
    for (int i =0; i<3; i++){
        if (strScan(string, stdin)==0){
            printf("%s\n", hexToDec(string));
            return 0;
        }
        else if (i!=2){
            printf("Incorrect input, try again, enter string to process: \n");
        }
        else
            printf("Incorrect input, exited.\n");
    }
    return 1;
}
int main(int argc, char* argv[]){
    if (argc > 1)
        return file_convert(argv[1],out_file_name(argv[1]));
    else
        return console_convert();
}