
#########################################################################
#
# Makefile for iri code and test driver C function (main.c)
# Created by:  G. Fenton 5/22/2022
#
#  > make
#  > make test
#  > ./test.exe - to run driver function
#
#########################################################################

CC = gcc-11
FC = gfortran    
FFLAGS = -std=legacy -fPIC 
LFLAGS = -shared 
OBJECTS = iritest.o irisub.o irifun.o iritec.o iridreg.o igrf.o cira.o iriflip.o

ECHO   = echo

%.o : %.for
	$(FC) $(FFLAGS) -c $< 

iri.so: $(OBJECTS)
	$(FC) $(LFLAGS) $(OBJECTS) -o iri.so 


#-- clean up the compile directory and binaries
clean :
	@$(ECHO)
	@$(ECHO) "Cleaning Up Object code "
	@$(ECHO) "------------------------"
	/bin/rm -f core *.o *.so *.exe edpData.* *.png
	@$(ECHO)

test: main.o iri.so
	$(CC) -o test.exe main.c iri.so
	./test.exe

