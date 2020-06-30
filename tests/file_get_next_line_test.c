#include "test.h"

#define N 10L
#define M 265010L
#define FILENAMESMALL "10.txt"
#define FILENAMEBIG "big.txt"

static void makefile(
    char const * const filename,
    size_t const num_lines)
{
  size_t i;
  file_t * file;
  if (dl_open_file(filename, "w", &file) != DL_FILE_SUCCESS) {
    abort();
  }

  for (i=0;i<num_lines;++i) {
    dl_fprintf(file, "%zu\n", i);
  }

  dl_close_file(file);
}

sint_t test(void) 
{
  file_t * file;

  // create test files
  makefile(FILENAMESMALL, N);
  makefile(FILENAMEBIG, M);

  int rv = dl_open_file(FILENAMESMALL,"r",&file);
    
  TESTEQUALS(rv,DL_FILE_SUCCESS,"%d");

  ssize_t ll,i;
  size_t bs = 5;
  char * buffer = char_alloc(bs);

  i = 0;
  while ((ll = dl_get_next_line(file,&buffer,&bs)) > 0) {
    TESTEQUALS(ll,1L,PF_SSIZE_T);
    TESTEQUALS((ssize_t)atoi(buffer),i,PF_SSIZE_T);
    ++i;
  }

  dl_close_file(file);

  rv = dl_open_file(FILENAMEBIG,"r",&file);
  TESTEQUALS(rv,DL_FILE_SUCCESS,"%d");

  i = 0;
  while ((ll = dl_get_next_line(file,&buffer,&bs)) >= 0) {
    TESTEQUALS(buffer[ll],'\0',"%c");
    ++i;
  }

  TESTEQUALS(i,M,PF_SSIZE_T);

  dl_close_file(file);

  return 0;
}
