

At the command line type:
> cd iri
> make

This will create the iri2016 shared library, iri.so. Once the iri.so file
exists you can run the 'nm' command to get the name for reference in a C
routine.  For example,
   > nm ./iri.so | grep -in iri
734:000000000000b567 T _iri_sub_
735:0000000000037b9d T _iri_tec_
736:0000000000015f47 T _iri_web_
737:0000000000038b3f T _irit13_

gives 4 routines with the iri prefix.  I believe the iri_sub is the one I 
want to use.  So, in a C routine I would use the 'iri_sub_()' function call.



Next type
> cd ..
> make

This will compile and link the C code to the iri.so file.

 
NOTE: Need to properly set the DYLD_LIBRARY_PATH env variable. Use an absolute path!
    > export DYLD_LIBRARY_PATH=/Users/gfenton/Downloads/jobs/ERT-Jobs/evaluation/pb1/iri


