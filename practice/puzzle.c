#include<stdio.h>
#include <pthread.h>

int test[9][9] = {{ 6, 2, 4, 5, 3, 9, 1, 8, 7 },
			  	 { 1, 1, 9, 7, 2, 8, 6, 3, 4 },
			     { 8, 3, 7, 6, 1, 4, 2, 9, 5 },
			     { 1, 4, 3, 8, 6, 5, 7, 2, 9 },
			     { 9, 5, 8, 2, 4, 7, 3, 6, 1 },
			     { 7, 6, 2, 3, 9, 1, 4, 5, 8 },
			     { 3, 7, 1, 9, 5, 6, 8, 4, 2 },
			     { 4, 9, 6, 1, 8, 2, 5, 7, 3 },
			     { 2, 8, 5, 4, 7, 3, 9, 1, 6 } };

typedef struct 
{
	int row;
	int colum;
	int resault;
}MY_ARGS;

void* check_1(void* args){
	MY_ARGS* my_args = (MY_ARGS*)args;
	int map[10];
	int temp = 0;
	for (int i = 0; i < 9; ++i)
	{
		//每次将标志数组清零
		for (int i = 0; i < 10; ++i)
		{
			map[i] = 0;
		}
		for (int j = 0; j < 9; ++j)
		{
			//检查每列
			if (my_args -> row == 0)
			{
				int temp = test[j][i];
				map[temp]++;	
			} else if (my_args -> colum == 0)
			{  
			//检查行
				int temp = test[i][j];
				map[temp]++;
			}
		}
		for (int i = 1; i < 10; ++i)
		{
			if (map[i] != 1)
			{
				return NULL;
			}
		}
	}
	my_args -> resault = 1;
	return NULL;
}

void* check_2(void* args){
	MY_ARGS* my_args = (MY_ARGS*)args;
	int num_i = my_args -> row + 3;
	int num_j = my_args -> colum + 3;
	int map[10];
	for (int i = 1; i < 10; ++i)
	{
		map[i] = 0;
	}
	for (int i = my_args -> row; i < num_i ; ++i)
	{
		for (int j = my_args -> colum; j < num_j; ++j)
		{
			int temp = test[i][j];
			map[temp]++;
		}
	}
	for (int i = 1; i < 10; ++i)
	{
		if (map[i] != 1)
		{
			return NULL;
		}
	}
	my_args -> resault = 1;
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t th_cloum;
	pthread_t th_row;
	
	pthread_t th_1;
	pthread_t th_2;
	pthread_t th_3;
	pthread_t th_4;
	pthread_t th_5;
	pthread_t th_6;
	pthread_t th_7;
	pthread_t th_8;
	pthread_t th_9;

	MY_ARGS args1 = {0, 9, 0};
	MY_ARGS args2 = {9, 0, 0};

	MY_ARGS arg1 = {0, 0, 0};
	MY_ARGS arg2 = {3, 0, 0};
	MY_ARGS arg3 = {6, 0, 0};
	MY_ARGS arg4 = {0, 3, 0};
	MY_ARGS arg5 = {3, 3, 0};
	MY_ARGS arg6 = {6, 3, 0};
	MY_ARGS arg7 = {0, 6, 0};
	MY_ARGS arg8 = {3, 6, 0};
	MY_ARGS arg9 = {6, 6, 0};


	pthread_create(&th_cloum, NULL, check_1, &args1);
	pthread_create(&th_row, NULL, check_1, &args2);
	pthread_create(&th_1, NULL, check_2, &arg1);
	pthread_create(&th_2, NULL, check_2, &arg2);
	pthread_create(&th_3, NULL, check_2, &arg3);
	pthread_create(&th_4, NULL, check_2, &arg4);
	pthread_create(&th_5, NULL, check_2, &arg5);
	pthread_create(&th_6, NULL, check_2, &arg6);
	pthread_create(&th_7, NULL, check_2, &arg7);
	pthread_create(&th_8, NULL, check_2, &arg8);
	pthread_create(&th_9, NULL, check_2, &arg9);


	pthread_join(th_cloum, NULL);
	pthread_join(th_row, NULL);
	pthread_join(th_1, NULL);
	pthread_join(th_2, NULL);
	pthread_join(th_3, NULL);
	pthread_join(th_4, NULL);
	pthread_join(th_5, NULL);
	pthread_join(th_6, NULL);
	pthread_join(th_7, NULL);
	pthread_join(th_8, NULL);
	pthread_join(th_9, NULL);

	if (arg1.resault == 1 && arg2.resault == 1 && arg3.resault == 1 && arg4.resault == 1 && arg5.resault ==1 && arg6.resault == 1 && arg7.resault == 1 && arg8.resault == 1 && arg9.resault == 1 && args1.resault == 1 && args2.resault == 1)
	{
		printf("True\n");
	} else {
		printf("False\n");
	}
	return 0;
}
