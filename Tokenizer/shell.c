#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"


int main (int argc, char **argv)
{

  
  char* cmdLine;
  parseInfo *info; //info stores all the information returned by parser.
  struct commandType *com; //com stores command name and Arg list for one command.
  
  while(1){
    

	 //cmdLine = "Santosh 1 2 3 | ls -l";
	  printf("Santosh> ");
    gets(cmdLine);


    if (cmdLine == NULL) {
      fprintf(stderr, "Unable to read command\n");
      continue;
    }



	if(!(cmdLine && * cmdLine)){

		printf("No command entered\n");
		continue;
		
	}

	if(strcmp(cmdLine,"exit") == 0){
		exit(0);
	}




    //calls the parser
    info = parseModified(cmdLine);
    if (info == NULL){
      free(cmdLine);
      continue;
    }
    //prints the info struct
    print_info(info);
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
  
