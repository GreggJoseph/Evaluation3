###########################################################################
target      = test
destination = .
###########################################################################
#  target  - the parameter given to make. I.e. what to build
#  depends - file or other targets target depends on
#  rule    - how to create target (note that rule is preceeded by a TAB char)
#  $(VAR)  - environment variable or variable defined above
#  $@      - Current target
#  $*      - Current target without extension
#  $<      - Current dependency
#
#---------------------------------------------------------------------------
#  Tools & Options
#---------------------------------------------------------------------------
Print                  = @echo
Copy                   = cp
CCompiler              = gcc-11
CppCompiler            = gcc-11
COptions               =  
Linker                 = gcc-11
LinkOptions            = -L/Users/gfenton/Downloads/jobs/ERT-Jobs/pb1/iri
MakeDepend             = makedepend
MakeDir                = mkdir -p
Delete                 = rm -fr
StaticArchiver         = ar
DynamicArchiver        = gcc-11
FortranCompiler        = gfortran
FortranOptions         = -m64
WordCount              = wc
List                   = cat

MakeOptions            = -k -s
MakeDependOptions      =
StaticArchiverOptions  = rc
DynamicArchiverOptions = -shared
WordCountOptions       = --lines

Empty                  =
Space                  = $(Empty) $(Empty)

###########################################################################
#
Libs = -lm
#
###########################################################################
#
Hdrs = 
#
Srcs = main.c
#
Objs = main.o 
#
###########################################################################
#
#  make new executable
#
	
# .c -> .o
%.o : %.c
	$(Print) $@
	@$(CCompiler) $(COptions) -c $(IncludePath) $< -o $@

# .f -> .o
%.o : %.f
	$(Print) $@
	@$(FortranCompiler) $(FortranOptions) -c $< -o $@

$(target) : $(Objs)
	rm -f $(target)
	$(Print) $@
	$(Linker) $(LinkOptions) -o $(target) $(Objs) -liri.so

#
###########################################################################
#
#  remove binaries
#
clean :
	rm -f *.o $(target)
#
###########################################################################
#
# install
#
install: ${TGT}
	install -s ${TGT} ${DST}/${TGT}
#
###########################################################################
 
