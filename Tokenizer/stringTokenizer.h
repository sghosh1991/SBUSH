/*
 * stringTokenizer.h
 *
 *  Created on: Feb 2, 2015
 *      Author: santosh
 */



typedef struct{
	int numOfTokens;
	char *tokenArr[10];
}Token;

Token* tokenize(char *,char*);
char * substring(char*, int, int);






