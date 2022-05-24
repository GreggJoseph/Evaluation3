#include <stdio.h>
#include <stdbool.h>


extern void iri_sub_(int **, int *, float *, float *, int*, int *, float *, float *,
                       float *, float *, float *, float *);

int main(void) {

    printf("Before running Fortran subroutine:\n");

    
    int    *jf[50], jmag, iyyyy, mmdd, iut, hour, ivar;
    float  alati,along,dhour,heibeg,heiend,heistp,vstp,outf,oarr;
    //bool
    
    jmag=1;
    alati=37.8; along=75.4;
    iyyyy=2021; mmdd=0303; dhour=11;
    heibeg=2; //km
    heiend=200; //km
    heistp=0.5; //km
    

    iri_sub_(jf,&jmag,&alati,&along,&iyyyy,&mmdd,&dhour,&heibeg,&heiend,&heistp,&outf,&oarr);
    
    printf("After running Fortran subroutine:\n");
    printf("outf=%f\n", outf);
    printf("oar=%f\n", oarr);


//printf("\nBefore running Fortran function:\n");
//printf("c=%f\n", c);
//printf("d=%f\n", d);
//
//printf("After running Fortran function:\n");
//printf("ffunc = %f\n", ffunc_(&c,&d));
//printf("c=%f\n", c);
//printf("d=%f\n", d);

    return 0;
}

