#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_VALUE 80
#define IS_COUT -1
#define IS_CIN 1
#define NALMOL 0

int state = NALMOL;

int getarray(char args[], char* array[]){
	char* p = NULL;
	if (args[strlen(args) - 1] == '\n')
		{
			args[strlen(args) - 1] = ' ';
		}
		//退出
		if (strncmp(args, "exit", 4) == 0)
		{
			return -1;
		}
		p = strtok(args, " ");
		int i = 0;
		while(p != NULL){
            if(*p != ' '){
            	if (*p == '>'){
            		state = IS_COUT;
            	} else if (*p == '<')
            	{
            		state = IS_CIN;
            	}
        		array[i] = p;
    			// printf("array[%d] = %s\n", i, array[i]);
    			i++;
            }
			p = strtok(NULL, " ");
		}
		return 0;
}

int main(void)
{
	while(1){
		
		char args[MAX_VALUE] = { };
		char* array[sizeof(args)] = { };
		char* filename = NULL;
		pid_t pid;
		int i = 0;
		int status;
		//命令提示语句
		printf("osh>");
		fgets(args, sizeof(args), stdin);
		fflush(stdout);

		int flag = getarray(args, array);
		if (flag == -1)
		{
			break;
		}
		for (int i = 0; *(array + i) != NULL; ++i)
		{
			if (**(array + i) == '>' || **(array + i) == '<')
			{
				filename = *(array + i + 1);
			}
		}

		// for (int i = 0; *(array+i) != NULL; ++i)
		// {
		// 	printf("array[%d] = %s\n",i ,*(array+i));
		// }
		// printf("state = %d\n", state);
		//printf("filename = %s\n", filename);

		if ((pid = fork()) < 0)
		{
			printf("fork error");
		} else if (pid == 0)
		{
			if (state == NALMOL)
			{
				execvp(array[0], array);
		    	exit(127);
			} else if (state == IS_COUT)
			{
				if(freopen(filename,"w",stdout)==NULL)
        			printf("move cout to the myfile error");
    			
				char* ret[sizeof(args)] = { };
				for (int i = 0; *(array + i) != NULL; ++i)
				{
					if (**(array + i) == '>')
					{
						break;
					} else {
						*(ret + i) = *(array + i); 
					}
				}
				// for (int i = 0; *(ret + i) != NULL; ++i)
				// {
				// 	printf("ret[%d] = %s\n", i, *(ret + i));
				// }
				execvp(ret[0], ret);
				fclose(stdout);
			} else if (state == IS_CIN)
			{
				char* file_in[sizeof(args)] = {};
				char* ret[sizeof(args)] = {};
				FILE* cin_file = fopen(filename, "r");
				fgets(args, sizeof(args), cin_file);
				getarray(args, file_in);
				for (int i = 0; *(file_in + i) != NULL; ++i)
				{
					if (**(file_in + i) == '<')
					{
						break;
					} else {
						*(ret + i) = *(file_in + i); 
					}
				}
				// for (int i = 0; *(array+i) != NULL; ++i)
				// {
				// 	printf("array[%d] = %s\n",i ,*(array+i));
				// }
				execvp(ret[0], ret);
				exit(127);
				fclose(cin_file);
			}
			
        }else {
        	if((pid = waitpid(pid, &status, 0)) < 0){
                printf("waitpit error");
            }
        }
	}
	return 0;
}
