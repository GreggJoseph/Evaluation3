How to compile and Some Developmental Notes
----------------------------------------------------

At the command line type:
> cd iri
> make

This will create the iri2016 shared library, iri.so. Once the iri.so file
exists you can run the 'nm' command to get the name for reference in a C
routine.  For example,
   > nm ./iri.so | grep -in _sub
0000000000046d27 T _igrf_sub_
000000000000b1b7 T _iri_sub_

gives 1 routine with the iri prefix.  I believe the iri_sub is the one I
want to use.  So, in a C routine I would use the 'iri_sub_()' function call.



Next type
> make test
> ./test.exe

This will compile and link the C code to the iri.so file.

 
NOTE: May need to properly set the DYLD_LIBRARY_PATH env variable. Use an absolute path!
    > export DYLD_LIBRARY_PATH=/Users/gfenton/Downloads/jobs/ERT-Jobs/evaluation/pb1/iri


I compiled the iri/irisub.for routine with:
    > gfortran -flto -fc-prototypes-external -c irisub.for
    
    This provided me an IRI_SUB() prototype to possibly use ???

#include <stddef.h>
#ifdef __cplusplus
#include <complex>
#define __GFORTRAN_FLOAT_COMPLEX std::complex<float>
#define __GFORTRAN_DOUBLE_COMPLEX std::complex<double>
#define __GFORTRAN_LONG_DOUBLE_COMPLEX std::complex<long double>
extern "C" {
#else
#define __GFORTRAN_FLOAT_COMPLEX float _Complex
#define __GFORTRAN_DOUBLE_COMPLEX double _Complex
#define __GFORTRAN_LONG_DOUBLE_COMPLEX long double _Complex
#endif

/* Prototypes for external procedures generated from irisub.for
   by GNU Fortran (Homebrew GCC 11.3.0_1) 11.3.0.

   Use of this interface is discouraged, consider using the
   BIND(C) feature of standard Fortran instead.  */


void iri_sub_ (int_fast32_t *jf, int *jmag, float *alati, float *along, int *iyyyy, int *mmdd, 
           float *dhour, float *heibeg, float *heiend, float *heistp, float *outf, float *oarr);

Changed the int_fast32_t to int, so...

I removed all the extraneous #include directives.
extern void iri_sub_ (int *, int *, float *, float *, int *, int *, float *, float *,
               float *, float *, float [][20], float *);


