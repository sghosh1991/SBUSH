#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringTokenizer.h"
#include "parser.h"

#define MAXLINE 81

void init_info(parseInfo *p, char *cmd) {
	printf("init_info: initializaing parseInfo\n");
	
	//Here check if there are any pipes.If so tokenize individual piped commands and make an array of commandTypes*/
	
	char *token;
	singleCommand* parsedSingleCommand;
	int numOfPipes = -1;

	//copy the passed command as the command string will be modified by strtok.
	//And a char *cmd is immutable. Will give segfault

	char command[400];
	strncpy(command,cmd,strlen(cmd)+1);	
						
	token = strtok(command,"|");
	//printf("In PIPE Parse Commnad to parse: %s\n",token);
	
	while(token!=NULL){
		
		printf("In PIPE Parse Commnad to parse: %s\n",token);
		parsedSingleCommand = parse_command(token); //parse the individual command and put it in the commandType struct
		
		printf("In PIPE Parse after returning from single command parse\n");
		if(parsedSingleCommand == NULL){
			printf("IN NULL\n");			
			p=NULL; //assign p to null and check in parse function
			return;
		}
		else{
			printf("IN INIT INFO NOT NULL\n");	
			p->CommArray[++numOfPipes]=parsedSingleCommand;
			
		}
		printf("Before tokenizing %s\n",token);
		printf("%c%c%d\n",token[3],token[4],token[5]);
		token = strtok(NULL,"|");
		printf("After tokenizing %s\n",token);
	}
	
	p->pipeNum = numOfPipes; //store the number of pipes in the command
}



singleCommand* parse_command(char * command) {
	//printf("parse_command: parsing a single command \n");

	//create and return a structure of singleCommand
	singleCommand* cmd = (singleCommand*)malloc(sizeof(singleCommand));

	//parse the command using space tokenization and put it into the singleCommand struct
	char singleCmd[400];
	char *token,*p;
	int count=0;
	int variableListIndex = 0; // index into the Varlist array of command
	printf("Before Copy\n");
	strncpy(singleCmd,command,strlen(command)+1);
	token = strtok(singleCmd," ");
	

	while(token !=NULL){
		
		printf("In SINGLE COMMAND Parse Commnad to parse: %s\n",token);
		//printf("Before copying command name");
		if(count == 0){
			//this is the command name. Put it in command of the struct
			//printf("Before copying command name");		
			strncpy(cmd->commandName,token,strlen(token)+1);
			//printf("After copying command name");
			count++;		
		}
		else if(count > MAX_VAR_NUM-1){
			//printf("IN ELSE IF");
			printf("Max number of args exceeded..Incorrect command");
			cmd = (singleCommand*)NULL;
			return cmd;
		}
		else{
			printf("IN ELSE\n");
			p=(char*)malloc(strlen(token)+1);
			strncpy(p,token,strlen(token)+1);
			cmd->VarList[variableListIndex] = p;
			//strncpy(cmd->VarList[variableListIndex],token,strlen(token)+1);
			count++;	//keep trackof the number of arguments
			variableListIndex++;
	
		}

		token = strtok(NULL," ");

	}/*while end */
	
	// populate the VarNum in singleCommand struct
	cmd->VarNum = variableListIndex;
	
	return cmd;

}/*functiomn end*/

parseInfo *parse (char *cmdLine) {
	parseInfo *Result;
	//char command[MAXLINE];
	/*int com_pos = -1;
	
	if (cmdline[-1] == '\n' && cmdline[-1] == '\0')
		return NULL;*/
	
	//Result = malloc(sizeof(parseInfo));
	//init_info(Result,cmdLine);
	//com_pos=0;
/*  while (cmdline[i] != '\n' && cmdline[i] != '\0') { */
	
	//command[com_pos]='\0';
	//parse_command(command, 0); /* &Result->CommArray[Result->pipeNum]);*/
	
	return Result;
}

void print_info (parseInfo *info) {
	//printf("print_info: printing info about parseInfo struct\n");
	//printf("Number of pipe separated commands %d\n",info->pipeNum);
	
	
	int i,j;

	for(i=0;i<info->pipeNum;i++){

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
		sc->VarNum = tokenSpace->numOfTokens-1;
		for(j=0;j<tokenSpace->numOfTokens-1;j++){
			sc->VarList[j]=tokenSpace->tokenArr[j+1];
		}

		Result->CommArray[i]=sc;

	}

	Result->pipeNum=tokenPipe->numOfTokens; //set the number of pipe separated commands

	return Result;



}
