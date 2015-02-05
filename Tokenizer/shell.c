#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"
#include "execute.h"

int main (int argc, char *argv[])
{
  char cmdLine[MAXLINE];
  int fd;
  parseInfo *info; //info stores all the information returned by parser.
  struct commandType *com; //com stores command name and Arg list for one command.
  if(argv[1]!=NULL)
  {
	  printf("executing script");
	  fd=open(argv[1],0);
	  printf("opened");
  }

  while(1)
  {
	 //cmdLine = "Santosh 1 2 3 | ls -l";

	  if(argv[1] == NULL)
	  {
		  printf("Santosh> ");
		  gets(cmdLine);
	  }
	  else
	  {
		  printf("here");
		  read_line(fd, cmdLine);
		  while (cmdLine[0] == '#')
			  read_line(fd,cmdLine);
	  }

	  printf("entered: %s",cmdLine);

		if (cmdLine == NULL) {
		  fprintf(stderr, "Unable to read command\n");
		  continue;
		}

		if(!(cmdLine && * cmdLine)){
			printf("No command entered\n");
			continue;

		}

		//calls the parser
		info = parseModified(cmdLine);
		if (info == NULL){
		  free(cmdLine);
		  continue;
		}

		//prints the info struct
		print_info(info);

		execute_cmd(info);
		printf("Out of execute\n");
		exit(0);

		//printf("After Printing\n");

		//com contains the info. of the command before the first "|"
	/*
		com=&info->CommArray[0];
		if ((com == NULL)  || (com->command == NULL)) {
		  free_info(info);
		  free(cmdLine);
		  continue;
		}
	*/
		//com->command tells the command name of com
	/*
		if (isBuiltInCommand(com->command) == EXIT){
		  exit(1);
		}
	*/
		//insert your code here.

		//free_info(info);
		//free(cmdLine);

	  }/* while(1) */

	return 0;
}
