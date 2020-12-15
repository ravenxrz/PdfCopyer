# Pdfcopyer

复制pdf文本后，再使用Alt+1快捷键，即可得到去掉换行符的文本。

使用Alt+2， 自动将代码文本中的行号去掉。如：

```c
1    #include <stdio.h> 
2    #include <stdlib.h> 
3    #include "common.h" 
4 
5    volatile int counter = 0; 
6    int loops; 
7 
8    void *worker(void *arg) { 
9        int i; 
10       for (i = 0; i < loops; i++) { 
11           counter++; 
12       } 
13       return NULL; 
14   } 
15 
16   int 
17   main(int argc, char *argv[]) 
18   {  
19       if (argc != 2) { 
20           fprintf(stderr, "usage: threads <value>\n"); 
21           exit(1); 
22       } 
23       loops = atoi(argv[1]); 
24       pthread_t p1, p2; 
25       printf("Initial value : %d\n", counter); 
26 
27       Pthread_create(&p1, NULL, worker, NULL); 
28       Pthread_create(&p2, NULL, worker, NULL); 
29       Pthread_join(p1, NULL); 
30       Pthread_join(p2, NULL); 
31       printf("Final value    : %d\n", counter); 
32       return 0; 
33   } 
```

复制上述文本后，使用alt+2，得到：

```c++
#include <stdio.h> 
#include <stdlib.h> 
#include "common.h" 
 
volatile int counter = 0; 
int loops; 
 
void *worker(void *arg) { 
    int i; 
   for (i = 0; i < loops; i++) { 
       counter++; 
   } 
   return NULL; 
} 
 
int 
main(int argc, char *argv[]) 
{  
    if (argc != 2) { 
        fprintf(stderr, "usage: threads <value>\n"); 
        exit(1); 
    } 
    loops = atoi(argv[1]); 
    pthread_t p1, p2; 
    printf("Initial value : %d\n", counter); 
 
    Pthread_create(&p1, NULL, worker, NULL); 
    Pthread_create(&p2, NULL, worker, NULL); 
    Pthread_join(p1, NULL); 
    Pthread_join(p2, NULL); 
    printf("Final value    : %d\n", counter); 
    return 0; 
} 
```



## Change Los

2020-12-15

1. alt+2， 处理代码复制前的行号问题。



2020-11-23

1. alt+1，去掉赋值pdf文本的换行符问题。

