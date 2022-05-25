

At the command line type:
> cd iri
> make

This will create the iri2016 shared library, iri.so

> cd ..
> make

This will compile and link the C code to the iri.so file.

NOTE: Need to properly set the DYLD_LIBRARY_PATH env variable.

export DYLD_LIBRARY_PATH=/Users/gfenton/Downloads/jobs/ERT-Jobs/evaluation/pb1/iri

