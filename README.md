# 操作系统

## 多线程编程

+ ## 常用API

+ ### 创建线程

  ```c
  NAME
       pthread_create -- create a new thread
  SYNOPSIS
  		#include <pthread.h>
  		
  		int
   		pthread_create(pthread_t *thread, const pthread_attr_t *attr,
           void *(*start_routine)(void *), void *arg);
  /*返回值
  如果成功返回0 如果失败返回error number
  ```

+ ## 等待线程终止

  ```c
  NAME
       pthread_join -- wait for thread termination
  
  SYNOPSIS
       #include <pthread.h>
  
       int
       pthread_join(pthread_t thread, void **value_ptr);
  /*返回值
  如果成功返回0 如果失败返回error number
  ```

+ ### 创建锁

  ```c
  NAME
       pthread_mutex_init -- create a mutex
  
  SYNOPSIS
       #include <pthread.h>
  
       int
       pthread_mutex_init(pthread_mutex_t *mutex,
           const pthread_mutexattr_t *attr);
  /*返回值
  如果成功返回0 并把 mutex id 放进mutex，否则返回一个error number
  ```

+ ### 加锁

  ```c
  NAME
       pthread_mutex_lock -- lock a mutex
  
  SYNOPSIS
       #include <pthread.h>
  
       int
       pthread_mutex_lock(pthread_mutex_t *mutex);
  /*返回值
  如果成功返回0 如果失败返回error number
  ```

+ ## 解锁

  ```c
  NAME
       pthread_mutex_unlock -- unlock a mutex
  
  SYNOPSIS
       #include <pthread.h>
  
       int
       pthread_mutex_unlock(pthread_mutex_t *mutex);
  /*返回值
  如果成功返回0 如果失败返回error number
  ```

  

+ ### 多线程编程中race condition的出现

  ### [race_condetion](multithreading/race_condition.c)

+ ### 解决方案

  ### [加锁](multithreading/solverace.c)

+ ### 利用多线程求和数组

  ### [多线程数组求和](multithreading/sum_arr.c)

## 多进程编程

+ ## 常用API

+ ### 创建进程

  ```c
  NAME
       fork -- create a new process
  
  SYNOPSIS
  		 #include <sys/types.h>
       #include <unistd.h>
  
       pid_t
       fork(void);
  //若成功 返回0到子进程 返回子进程的ID到父进程 
  //若失败 返回-1到父进程 
  ```

  ### [创建一个单独的子进程](Unix/testfork.c)
  
+ ### 获取进程ID

  ```c
  SYNOPSIS
       #include <unistd.h>
  
       pid_t
       getpid(void);
  
       pid_t
       getppid(void);
  // getpid 返回进程的processID
  // getppid 返回父进程的processID
  ```

  ### [进程的getpid()示例](实验/2.1.c)

## 进程通信----管道

+ ### 创建管道

  ```c
  #include <unistd.h>
  #define INPUT 0
  #define OUTPUT 1
  int pipe(int file_descript[2])
  //file_descript[INPUT] 用于读
  //file_descript[OUTPUT] 用于往外面写
  ```

+ ### 向管道读和写

  ```c
  resault = write(file_descript[OUTPUT], string, (strlen(string)+1));
  if(resault == -1){
    
  } 
  .....
  resault = read(file_descript[INPUT], buf, sizeof(buf));
  if(resault == -1){
    
  } else if(resault == 0){
    
  } else {
    
  }
  ```

  

## 操作系统概念书后项目

### 第四章 多线程编程

### [项目一：验证数独](practice/puzzle.c)

### [项目二：多线程排序](practice/mysort.c)

### 第三章 进程

### [项目一：Unix外壳和历史特征](practice/myshell.c)

