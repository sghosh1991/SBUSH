#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringTokenizer.h"
#include "parser.h"


void print_info (parseInfo *info) {
	//printf("print_info: printing info about parseInfo struct\n");
	//printf("Number of pipe separated commands %d\n",info->pipeNum);
	
	
	int i,j;

	for(i=0;i<=info->pipeNum;i++){

		printf("Command Name : %s\n",info->CommArray[i]->commandName);
	
		//printf("Command Arguments :\n");
		printf("Number of arguments %d\n",info->CommArray[i]->VarNum);

		for(j=0;j<info->CommArray[i]->VarNum;j++){
			printf("Argument %d : %s \n", j,info->CommArray[i]->VarList[j]);
			}

	}

	return;
}
 
void free_info (parseInfo *info) {
	printf("free_info: freeing memory associated to parseInfo struct\n");
	free(info);
}

parseInfo* parseModified(char *cmd){

	parseInfo *Result;
	Token* tokenPipe;
	Token* tokenSpace;
	singleCommand* sc = NULL;
	int i=0,j=0;
	//printf("In PARSE MODIFIED");
	Result = (parseInfo*)malloc(sizeof(parseInfo));

	tokenPipe = tokenize(cmd,"|");

	printf("In PARSE MODIFIED\n");
	for(i=0;i<tokenPipe->numOfTokens;i++){

		//for each pipe separated token find space separated tokens
		tokenSpace=tokenize(tokenPipe->tokenArr[i]," ");

		//initialize the singleCommand Structure
		sc = (singleCommand*)malloc(sizeof(singleCommand));
		sc->commandName = tokenSpace->tokenArr[0];
		sc->VarNum = tokenSpace->numOfTokens;
		for(j=0;j<tokenSpace->numOfTokens;j++){
			sc->VarList[j]=tokenSpace->tokenArr[j];
		}
		sc->VarList[j]=NULL;

		Result->CommArray[i]=sc;

	}

	Result->pipeNum=tokenPipe->numOfTokens-1; //set the number of pipe separated commands

	return Result;
}

int read_line(int fd, char* buf)
{
	char *byte=buf;
	int ret = read(fd,byte,1);
	if(ret == 0)
	{
		byte = '\0';
		return -1;
	}
	printf("read: %c ",*byte);
	while(*byte++!='\n')
	{
		ret = read(fd,byte,1);
		printf("read: %c ",*byte);
		if (ret == -1)
			return -1;
	}
	*(byte-1)='\0';
	return 1;
}
