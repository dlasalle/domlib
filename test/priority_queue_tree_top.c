#include "test.h"

#define N 1600UL




sint_t test(void)
{
  size_t i;
  real_t j;
  
  trs_pq_t * q = trs_pq_create(N);

  real_t * p = real_alloc(N);

  for (i=0;i<N;++i) {
    p[i] = (N % (i+10))/(real_t)N;
    trs_pq_push(p[i],i,q);
  }

  while (q->size > 0) {
    j = trs_pq_top(q);
    i = trs_pq_pop(q);
    TESTEQUALS(p[i],j,PF_REAL_T);
  }

  dl_free(p);
  trs_pq_free(q);

  return 0;
}
