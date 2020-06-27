#include "test.h"

#define N 1600UL




sint_t test(void)
{
  size_t i;
  real_t j;
  
  rs_pq_t * q = rs_pq_create(0,N);

  real_t * p = real_alloc(N);

  for (i=0;i<N;++i) {
    p[i] = (N % (i+10))/(real_t)N;
    rs_pq_push(p[i],i,q);
  }

  while (q->size > 0) {
    j = rs_pq_top(q);
    i = rs_pq_pop(q);
    TESTEQUALS(p[i],j,PF_REAL_T);
  }

  dl_free(p);
  rs_pq_free(q);

  return 0;
}
