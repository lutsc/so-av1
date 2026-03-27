#include "library.h"
#include <stdio.h>
#include <pthread.h>

void * thread_test(void * param)
{
  int a = 0;
  a += 1;
  a = 2;
  pthread_exit(0);
};

int main()
{
  printf("Hello world\n");
  test_print_function();

  pthread_t tid;
  pthread_create(&tid, NULL, thread_test, NULL);
  pthread_join(tid, NULL);

  return 0;
}
