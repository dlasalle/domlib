#include "test.h"

#define N 16000




sint_t test(void)
{
  sint_t i;
  real_t j,l;

  real_t * p = real_alloc(N);

  /* minimum priority queue */
  
  rs_pq_t * q = rs_pq_create(0,N);

  for (i=0;i<N;++i) {
    rs_pq_push((real_t)i,i,q);
    p[i] = (N%(i+10))/(real_t)N;
  }

  for (i=0;i<N;++i) {
    rs_pq_update(p[i],i,q);
  }

  l = rs_pq_top(q);
  while (q->size > 0) {
    i = rs_pq_peek(q);
    j = rs_pq_top(q);
    TESTEQUALS(p[i],j,PF_REAL_T);
    rs_pq_pop(q);
    /* make sure they priority queue still works */
    TESTLESSTHANOREQUAL(j,l,PF_REAL_T);
  }

  rs_pq_free(q);

  /* minimum priority queue */

  mrs_pq_t * mq = mrs_pq_create(0,N);

  for (i=0;i<N;++i) {
    mrs_pq_push((real_t)i,i,mq);
    p[i] = (N%(i+10))/(real_t)N;
  }

  for (i=0;i<N;++i) {
    mrs_pq_update(p[i],i,mq);
  }

  l = mrs_pq_top(mq);
  while (mq->size > 0) {
    i = mrs_pq_peek(mq);
    j = mrs_pq_top(mq);
    TESTEQUALS(p[i],j,PF_REAL_T);
    mrs_pq_pop(mq);
    /* make sure they priority queue still works */
    TESTGREATERTHANOREQUAL(j,l,PF_REAL_T);
  }

  mrs_pq_free(mq);

  dl_free(p);

  return 0;
}
