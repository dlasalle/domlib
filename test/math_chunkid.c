#include "test.h"

#define N 1000
#define M 1000

sint_t test(void) 
{
  sint_t i, j, k, a;


  for (k=1;k<M;++k) {
    for (j=1;j<=k&&j<N;++j) {
      for (i=0;i<j;++i) {
        a = sint_chunkid(i,j,k);
        TESTLESSTHAN(a,j,PF_SINT_T);
        TESTLESSTHANOREQUAL(sint_chunkstart(a,j,k),i,PF_SINT_T);
        TESTGREATERTHAN(sint_chunkstart(a+1,j,k),i,PF_SINT_T);
      }
    }
  }

  return 0;
}
