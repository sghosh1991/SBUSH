#include "parser.h"
#include "stdio.h"
#include <stdlib.h>
#include <errno.h>

char * myerror(int err)
{
	switch(err)
	{
		case 2:
			return "Command Not Found";

		case 13:
			return "Permission denied.";
	}
	return "error occured.";

}


void execute_cmd(parseInfo * info)
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

    if(info->pipeNum==0)
    {
        printf("forking");
    	pid=fork();

    	if (pid < 0)
		{
			printf("fork error:%d\n", errno);
			exit(EXIT_FAILURE);
		}
        if(pid==0)
        {
            printf("executing %s\n",info->CommArray[0]->commandName);
            char* envp[]={NULL};
            int ret = execve(info->CommArray[0]->commandName,info->CommArray[0]->VarList,envp);
            if(ret == -1)
            {
            	printf("%s",myerror(errno));
            	exit(EXIT_FAILURE);
            }
        }
        printf("\ndone\n");
    }
    else
    {
        pipes=(int*)malloc(2*info->pipeNum*sizeof(int));
        for(i=0; i<info->pipeNum; i++)
        {
        	if(pipe(pipes+i*2) == -1)
        		printf("Pipe creation error:%d",errno);
        }
        printf("Multiple Commands");
        for(i=0; i<=info->pipeNum;i++)
        {
            pid=fork();
            if (pid < 0)
			{
				printf("fork error:%d\n", errno);
				exit(EXIT_FAILURE);
			}
        	printf("pid=%d",pid);
            if(pid==0)
            {
                printf("in child%d",i);

                if(i!=0)
                {
                    if(dup2(pipes[i*2-2],0)==-1)
                    	printf("Dup2 error:%d",errno);
                }
                if(i!=info->pipeNum)
                {

                    if(dup2(pipes[i*2+1],1)==-1)
                    	printf("Dup2 error:%d",errno);
                }

                for(j=0;j<info->pipeNum;j++)
                {
                    close(pipes[j*2]);
                    close(pipes[j*2+1]);
                }
                printf("debug:%d\n",i);
                printf("debug:%s ", info->CommArray[i]->commandName);
                char* envp[]={NULL};
                int ret=execve(info->CommArray[i]->commandName,info->CommArray[i]->VarList,envp);
                if(ret == -1)
				{
					printf("%s",myerror(errno));
					exit(EXIT_FAILURE);
				}
            }
        }
        printf("\nin multiple's parent\n");

        for(i=0;i<info->pipeNum;i++)
		{
			  close(pipes[i*2]);
			  close(pipes[i*2+1]);
			  printf("closed");
		}
    }
	printf("\nin singles's parent\n");
    for (i = 0; i <= info->pipeNum; i++)
        	printf("child returned:%d\n",wait(&status));
}
