#include "test.h"
#include <omp.h>

#define N 10UL
#define M 200UL
#define NTHREADS 64UL



static void func(
    void * ptr)
{
  int i,j;
  int * rv;

  int const myid = dlthread_get_id(DLTHREAD_COMM_ROOT);
  int const nthreads = dlthread_get_nthreads(DLTHREAD_COMM_ROOT);

  rv = ptr;

  sint_combuffer_t * com = sint_combuffer_create(DLTHREAD_COMM_ROOT);

  for (i=0;i<nthreads;++i) {
    if (i != myid) {
      for (j=0;j<(int)M;++j) {
        sint_combuffer_add(i,myid,com);
      }
      OMPTESTEQUALS(M,com->buffers[myid][i].size,PF_SIZE_T,*rv);
    }
  }
  for (i=0;i<nthreads;++i) {
    if (i != myid) {
      for (j=0;j<(int)M;++j) {
        OMPTESTEQUALS(myid,com->buffers[myid][i].elements[j],"%d",*rv);
      }
    }
  }
  sint_combuffer_free(com);
}


sint_t test(void) 
{
  sint_t rv = 0;

  dlthread_launch(NTHREADS,&func,&rv);

  return rv;
}
