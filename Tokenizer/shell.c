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
  int fd,ret;
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
		  ret=read_line(fd, cmdLine);
		  while (cmdLine[0] == '#')
			  ret=read_line(fd,cmdLine);
		  if(ret == -1)
			  break;
	  }

	  printf("entered: %s",cmdLine);

		if (cmdLine == NULL) {
		  printf("Unable to read last command\n");
		  continue;
		}

		if(!(*cmdLine)){
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
		static int loop=0;
		printf("Out of execute%d\n",loop++);
		//exit(0);
  }/* while(1) */
  printf("BYE BYE");
  return 0;
}
