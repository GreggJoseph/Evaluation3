#include <stdio.h>
#include <stdbool.h>

// iri_sub Function Prototype declaration
extern void iri_sub_(bool [], int *, float *, float *, int*, int *, float *, float *,
                       float *, float *, float [][20], float []);

int main(void) {

    printf("\nBefore var declarations:\n");

    int    jmag, iyyyy, mmdd, iut, hour, ivar;
    float  lat, lon, dhour;
    float  hbeg, hend, hstp;
    //char   *datadir = "iri";
    
    // Rows and columns between C and Fortran are switched.
    float  oarr[100], outf[1000][20];
    
    bool   jf[50] = { true };
    jmag = 1;
    lat = 37.8; lon = 75.4;
    iyyyy = 2021; mmdd = 0303; dhour = 11.+25.;
    hbeg = 100.; //km
    hend = 500.; //km
    hstp = 20.; //km
    
    printf("Before running Fortran subroutine...\n");
    iri_sub_(jf, &jmag, &lat, &lon, &iyyyy, &mmdd, &dhour, &hbeg, &hend, &hstp, outf, oarr);
    printf("After running Fortran subroutine...\n");
    
    printf("outf=%f\n", outf);
    printf("oar=%f\n", oarr);

    return 0;
}

