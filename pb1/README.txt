

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


