#
# Makefile for problem #3
.PHONY: clean test install

#
# Files and Directories
#
TGT= pb3
DST= ./
#
#
# Code Units
SOURCES = $(wildcard *.c)  
HEADERS = $(wildcard *.h)  
OBJECTS = $(subst .c,.o,$(SOURCES))

#
Objs1 =pb3.o
Objs  =${Objs1}

Headers =

#
# Compiler/Loader Invokations
CC = gcc-11

#
# Compiler/Loader Options
#
# -DMAC: Compile directive for Apple Mac specific code pragma statements.
# -DOMP: Compile directive for OpenMP parallelization code pragma statements.
#

######- GNU compiler -#######

# >>> Serial GNU compile
# optimized
CcFlags = -c -DMAC 
#CcFlags = -c -O2 -std=c99 -Wall -Wextra -Wconversion -pedantic
linkFlags =

# debug
#CcFlags = -c -g -std=c99 -DMAC -Wall -Wextra -Wconversion -pedantic
#CcFlags = -c -g -std=c99 -DMAC -Wall -Wextra -Wconversion -pedantic
#linkFlags = -g


# >>> Parallel GNU compile
# optimized
#CcFlags = -c -fopenmp -O2 -std=c99 -DOMP -std=c99 -Wall -Wextra -Wconversion -pedantic
#CcFlags = -c -fopenmp -O2 -fcommon -std=c99 -DMAC -DOMP
#linkFlags = -fopenmp -O2

# debug
#CcFlags = -c -fopenmp -g -std=c99 -DOMP -Wall -Wextra -Wconversion -pedantic
#CcFlags = -c -fopenmp -g -fPIC -fcommon -std=c99 -DMAC -DOMP -std=c99 -Wall -pedantic
#CcFlags = -c -fopenmp -g -fcommon -std=c99 -DMAC -DOMP -Wall -pedantic
#linkFlags = -fopenmp -g 


######- Intel compiler -#######
# >>> Serial Intel optimized
#CcFlags = -c -O2 -std=c99 -DMAC -Wall -pedantic
#linkFlags = 

# >>> Parallel Intel optimized
#CcFlags = -c -qopenmp -O2 -std=c99 -DMAC -DOMP -Wall -Wextra -Wconversion -pedantic
#linkFlags = -qopenmp -qopt-report=1

# debug
#CcFlags = -c -qopenmp -g -std=c99 -DMAC -DOMP -Wall -Wextra -Wconversion -pedantic
#linkFlags = -qopenmp -g


#
# Include the needed libraries
Libs =-lm
#
# make new executable
#
${TGT}:	${Objs}
		/bin/rm -f $(TGT)
		$(CC) $(linkFlags) -o $(TGT) $(Objs) $(Libs)
#
.c.o:
		$(CC) $(CcFlags) $<
#
# Define source dependencies
#
$(OBJECTS)   : $(HEADERS)

#
# clean up the directory and binaries
#
clean :
	/bin/rm -f core *.o *.opt* ${TGT} make.log

#
# install
#
install:	${TGT}
	mv  ${TGT} ${DST}/${TGT}


test:
	@echo "*** "
	@echo "*** >>> Testing the source listings <<< ***"
	@echo ": "
	@echo "(Sources are) --> " $(SOURCES)
	@echo ": "
	@echo "(Headers are) --> " $(HEADERS)
	@echo ": "
	@echo "(Objects to be created are) --> " $(OBJECTS)
	@echo ": "
	@echo "*** "
	@echo "*** "


