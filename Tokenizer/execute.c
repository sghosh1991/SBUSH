#include "parser.h"
#include "stdio.h"
#include <stdlib.h>
void execute(parseInfo * info)
{
    int i,j,*pipes,status;

	int pid;
    printf("pipes=%d \n",info->pipeNum);

    for(i=0; i<=info->pipeNum; i++)
    {
    	printf("info: %s\n", info->CommArray[i]->commandName);
    	printf("varnum=%d\n",info->CommArray[i]->VarNum);
		for(j=0;j<info->CommArray[i]->VarNum; j++)
			printf("varList=%s\n",info->CommArray[i]->VarList[j]);

    }

    pipes=(int*)malloc(2*info->pipeNum);

    if(info->pipeNum==0)
    {
        printf("forking");
    	pid=fork();

        if(pid==0)
        {
            printf("executing %s\n",info->CommArray[0]->commandName);
            execvp(info->CommArray[0]->commandName,info->CommArray[0]->VarList);
            printf("Unknown Command");
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
