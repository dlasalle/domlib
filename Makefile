CC = gcc
RM = rm -rfv
ARCHIVE = ar rscv

ifdef DEBUG
  OPTOPTS = -g -DDEBUG -DUSE_ASSERTS=1
else
  OPTOPTS = -mtune=native -march=native -O3 -DNDEBUG=1 -DNDEBUG2=2
endif

ifdef USE_GKLIB
  GKOPT = -DUSE_GKLIB -I./GKlib
else
  GKOPT =
endif

ifdef NOMATH 
  MOPT = -DNOMATH 
else
  MOPT =
endif

LIBS = -fopenmp -lpthread 
CWARN = -Wall -Wmissing-prototypes -Wmissing-declarations \
        -Wstrict-aliasing -Wextra -Werror -Wno-unused-parameter \
        -Wno-unused-function
CSTD = -std=c99
CSPEC = -fstrict-aliasing -static

COPTS = $(OPTOPTS) $(CSTD) $(CWARN) $(GKOPT) $(CSPEC) $(MOPT)


BASEOBJS = dlfile.o dlutil.o dlenv.o dlstring.o dlcmdline.o dlterm.o \
           dlthread.o dlthread_pool.o

all: libdom.a

test: libdom.a
	make -C test test

# Libraries ###################################################################

libdom.a: domlib.o $(BASEOBJS)
	$(RM) $@
	$(ARCHIVE) $@ $^

# BASE OBJECTS ################################################################

%.o: %.c *.h
	$(CC) $(COPTS) -c $< $(LIBS) -o $@

clean:
	$(RM) *.o && \
	$(RM) *.swp 

distclean: clean
	$(RM) libdom.a

rebuild: distclean all 

.PHONY: test
