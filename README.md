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

## 操作系统概念书后项目

### 第四章 多线程编程

### [项目一：验证数独](practice/puzzle.c)

### [项目二：多线程排序](practice/mysort.c)

### 第三章 进程

### [项目一：Unix外壳和历史特征](practice/myshell.c)

