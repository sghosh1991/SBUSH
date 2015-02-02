#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "stringTokenizer.h"


char * substring(char* str, int front, int back){

	//temporary buffer to hold the token;
	char n[50];
	char *p;
	int i=0;


	//Must handle condition of consequtive delims, delim at the end.Not done till now.

	if(back==front){

		return (char*)NULL;

	}

	while(back < front){
		n[i++]=str[back++];
	}
	n[i] = '\0';

	p = (char*)malloc(sizeof(char)*(front-back+1));
	strcpy(p,n);

	return p;

}


Token* tokenize(char *str,char* delim){

	Token* token=(Token*)malloc(sizeof(Token));
	int tokenCount=0;
	int front=0,back=0;
	char *p;

	//printf("IN TOKENIZER");

	while(str[front]!='\0'){

		if(str[front]== *delim){
			//delimiter found. Extract substring.
			p=substring(str,front,back);
			if(p != NULL){
				token->tokenArr[tokenCount++]=p;
			}

			back = front +1;
			front++;
			continue;
		}

		else{
			front++;
		}
	}//end while

	p = substring(str,front,back);
	if(p != NULL){
		token->tokenArr[tokenCount++]=p;
	}
	token->numOfTokens=tokenCount;

	return token;

}


/*int main(){

	int i;
	char *p;
	char *delim = "|";
	p = "  Hi I |Am|   Santosh  ";
	Token *t;
	t = tokenize(p,delim);

	for(i=0;i<t->numOfTokens;i++){
		printf("Token [%d] : %s\n",i,t->tokenArr[i]);
	}
	return 0;
}
*/
