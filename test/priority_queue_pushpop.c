#include "test.h"

#define M 12000UL
#define N 16000UL




sint_t test(void)
{
  size_t l,i;
  real_t j;

  /* maximum priority queue */
  
  rs_pq_t * q = rs_pq_create(M,N);

  for (i=M;i<(sint_t)N;++i) {
    rs_pq_push(i/((real_t)N),i,q);
    for (l=0;l<q->size;++l) {
      TESTEQUALS(q->index[q->elements[l].val-q->min],l,PF_SIZE_T);
    }
  }

  TESTEQUALS(N-M,q->size,PF_SIZE_T);

  for (i=0;i<q->size;++i) {
    TESTEQUALS(q->index[((ssize_t)q->elements[i].val)-((ssize_t)q->min)],i,
        PF_SIZE_T);
  }

  j = q->elements[0].key;
  rs_pq_pop(q);
  for (i=1;i<N-M;++i) {
    TESTLESSTHANOREQUAL(q->elements[0].key,j,PF_REAL_T);
    j = q->elements[0].key;
    rs_pq_pop(q);
    for (l=0;l<q->size;++l) {
      TESTEQUALS(q->index[q->elements[l].val-q->min],l,PF_SIZE_T);
    }
  }

  TESTEQUALS(0UL,q->size,PF_SIZE_T);

  rs_pq_free(q);

  /* minimum priority queue */

  mrs_pq_t * mq = mrs_pq_create(M,N);

  for (i=M;i<(sint_t)N;++i) {
    mrs_pq_push(i/((real_t)N),i,mq);
    for (l=0;l<mq->size;++l) {
      TESTEQUALS(mq->index[mq->elements[l].val-mq->min],l,PF_SIZE_T);
    }
  }

  TESTEQUALS(N-M,mq->size,PF_SIZE_T);

  for (i=0;i<mq->size;++i) {
    TESTEQUALS(mq->index[((ssize_t)mq->elements[i].val)-((ssize_t)mq->min)],i,
        PF_SIZE_T);
  }

  j = mq->elements[0].key;
  mrs_pq_pop(mq);
  for (i=1;i<N-M;++i) {
    TESTGREATERTHANOREQUAL(mq->elements[0].key,j,PF_REAL_T);
    j = mq->elements[0].key;
    mrs_pq_pop(mq);
    for (l=0;l<mq->size;++l) {
      TESTEQUALS(mq->index[mq->elements[l].val-mq->min],l,PF_SIZE_T);
    }
  }

  TESTEQUALS(0UL,mq->size,PF_SIZE_T);

  mrs_pq_free(mq);

  return 0;
}
