#include "test.h"


#define N 1000000
#define M ((N)/2)
#define K 33


sint_t test(void) 
{
  sint_t i, j;
  ss_ht_t * map = ss_ht_create(N,M);

  for (i=0;i<M;++i) {
    j = i*K;
    ss_ht_put(j,j+10,map);
  }

  ss_ht_put(2*N,3,map);
  ss_ht_put(3*N,4,map);
  ss_ht_put(4*N,5,map);

  for (i=0;i<M;++i) {
    j = i*K;
    TESTEQUALS(ss_ht_get(j,map),j+10,PF_SINT_T);
  }
  TESTEQUALS(ss_ht_get(2*N,map),3,PF_SINT_T);

  for (i=M;i>M/2;) {
    --i;
    j = i*K;
    TESTEQUALS(ss_ht_remove(j,map),j+10,PF_SINT_T);
  }

  for (i=0;i<M/2;++i) {
    j = i*K;
    TESTEQUALS(ss_ht_remove(j,map),j+10,PF_SINT_T);
  }

  TESTEQUALS(ss_ht_remove(4*N,map),5,PF_SINT_T);
  TESTEQUALS(ss_ht_remove(2*N,map),3,PF_SINT_T);
  TESTEQUALS(ss_ht_remove(3*N,map),4,PF_SINT_T);

  TESTEQUALS(map->size,0UL,PF_SIZE_T);

  ss_ht_free(map);

  return 0;
}
