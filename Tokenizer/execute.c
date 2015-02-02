#include "parser.h"
#include "stdio.h"
#include <stdlib.h>
void execute(parseInfo * info)
{
    int i,*pipes,status;
	int *p;
pid_t pid;
    printf("pipes=%d hi1\n",info->pipeNum);
	printf("hi");
    for(i=0; i<=info->pipeNum; i++)
    {
	printf("hi");

	printf("varList1=%s\n",info->CommArray[i]->VarList[1]);
	printf("varList0=%s\n",info->CommArray[i]->VarList[0]);
        printf("info: %s\n", info->CommArray[i]->commandName);
        printf("varnum=%d\n",info->CommArray[i]->VarNum);


    }

    pipes=(int*)malloc(4);


    if(info->pipeNum==0)
    {
        pid=fork();
        if(pid==0)
        {
            printf("executing %s\n",info->CommArray[0]->commandName);
            execvp(info->CommArray[0]->commandName,info->CommArray[0]->VarList);
        }
        printf("\ndone\n");
    }
    else
    {
        printf("HI");
        for(i=0; i<=info->pipeNum;i++)
        {
            pid=fork();
        	printf("HI%d",pid);
            if(pid==0)
            {
               printf("in child%d",i);
                if(i!=0)
                {
                    dup2(pipes[i*2],0);
                }
                if(i!=info->pipeNum)
                {
                    dup2(pipes[i*2+1,1]);
                }

                for(i=0;i<=info->pipeNum;i++)
                {
                    close(pipes[i*2]);
                    close(pipes[i*2+1]);
                }
                execvp(info->CommArray[i]->commandName,info->CommArray[i]->VarList);
            }

        }
         for(i=0;i<=info->pipeNum;i++)
        {
              close(pipes[i*2]);
              close(pipes[i*2+1]);
		printf("closed");
        }

   }
        printf("\nin parent\n");
        for (i = 0; i < info->pipeNum; i++)
                wait(&status);



}
