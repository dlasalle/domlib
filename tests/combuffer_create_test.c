#include "test.h"
#include <omp.h>

#define N 10


static void work(
    void * ptr)
{
  int i;
  int * r_rv;

  int const myid = dlthread_get_id(DLTHREAD_COMM_ROOT);
  int const nthreads = dlthread_get_nthreads(DLTHREAD_COMM_ROOT);

  r_rv = ptr;

  sint_combuffer_t * com = sint_combuffer_create(DLTHREAD_COMM_ROOT);

  for (i=0;i<nthreads;++i) {
    if (i != myid && com->buffers[myid][i].maxsize != N) {
      printf("[%d] buffer[%d]->maxsize = %zu and num threads = %d\n",
          myid,i,com->buffers[myid][i].maxsize,N);
      ++(*r_rv);
    }
  }
  sint_combuffer_free(com);
}


sint_t test(void) 
{
  sint_t rv = 0;

  dlthread_launch(N,&work,&rv);

  return rv;
}
