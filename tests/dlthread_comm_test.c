#include "test.h"

#define N 1234567
#define M 837


static void myfunc(void * ptr)
{
  int * res;

  size_t myid = dlthread_get_id(DLTHREAD_COMM_ROOT);
  size_t nthreads = dlthread_get_nthreads(DLTHREAD_COMM_ROOT);

  res = (int*)ptr;

  res[myid] = 0;

  OMPTESTTRUE(myid<M,res[myid]);
  if (res[myid] != 0) {
    return;
  }
  OMPTESTTRUE(nthreads == M,res[myid]);
  if (res[myid] != 0) {
    return;
  }


  OMPTESTTRUE(dlthread_get_id(DLTHREAD_COMM_SINGLE) == 0,res[myid]);
  if (res[myid] != 0) {
    return;
  }
  OMPTESTTRUE(dlthread_get_nthreads(DLTHREAD_COMM_SINGLE) == 1,res[myid]);
  if (res[myid] != 0) {
    return;
  }
}


sint_t test(void)
{
  int i;
  int res[M];

  for (i=0;i<M;++i) {
    res[i] = -1;
  }

  dlthread_launch(M,&myfunc,res);

  for (i=0;i<M;++i) {
    TESTEQUALS(res[i],0,"%d");
  }

  return 0;
}
