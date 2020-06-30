#include "test.h"

#define N 16000




sint_t test(void)
{
  sint_t i;
  real_t j,l;

  real_t * p = real_alloc(N);

  trs_pq_t * q = trs_pq_create(N);

  for (i=0;i<N;++i) {
    trs_pq_push((real_t)i,i,q);
    p[i] = (N%(i+10))/(real_t)N;
  }

  for (i=0;i<N;++i) {
    trs_pq_update(p[i],i,q);
  }

  l = trs_pq_top(q);
  while (q->size > 0) {
    i = trs_pq_peek(q);
    j = trs_pq_top(q);
    TESTEQUALS(p[i],j,PF_REAL_T);
    trs_pq_pop(q);
    /* make sure they priority queue still works */
    TESTLESSTHANOREQUAL(j,l,PF_REAL_T);
  }

  trs_pq_free(q);

  return 0;
}
