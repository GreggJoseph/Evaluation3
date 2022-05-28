#include <stdio.h>
#include <stdbool.h>


// iri_sub Function Prototype declaration
//SUBROUTINE IRI_SUB(JF, JMAG, ALATI, ALONG, IYYYY, MMDD, DHOUR,
//                   HEIBEG, HEIEND, HEISTP, OUTF, OARR)
//extern void iri_sub_ (bool [], int *, float *, float *, int*, int *, float *,
//                     float *, float *, float *, float [][20], float []);
#include <stddef.h>


/* Prototypes for external procedures generated from irisub.for
   by GNU Fortran (Homebrew GCC 11.3.0_1) 11.3.0.

   Use of this interface is discouraged, consider using the
   BIND(C) feature of standard Fortran instead.  */

//void iri_sub_ (int *jf, int *jmag, float *alati, float *along, int *iyyyy, int *mmdd, float *dhour, float *heibeg, float *heiend, float *heistp, float outf[][20], float oarr[]);
    
extern void iri_sub_ (int *, int *, float *, float *, int *, int *, float *, float *,
               float *, float *, float [][20], float *);
    
int main(void) {

    int    i, j, nalt=21;
    int    jmag, iyyyy, mmdd, iut;
    float  lat, lon;
    float  dhour;
    float  hbeg, hend, hstp;    
    float  alt[nalt];
    
    // Rows and columns between C and Fortran are switched, meaning
    // major order for double arrays is swapped between the C & FORTRAN
    float  outf[1000][20], oarr[100];
    //bool   jf[50] = { true }; //only sets the 1st element to true
    int   jf[50];
    
    for( i=0 ; i<50 ; i++ ){
        jf[i] = 1;
        if(i>2 && i<6)   jf[i] = 0;
        if(i==7)         jf[i] = 1; // .true. for foF2
        //if(i>20 && i<23) jf[i] = 0;
        if(i==25)        jf[i] = 1; // .true. for foF2
        //if(i>26 && i<30) jf[i] = 0;
        //if(i>31 && i<35) jf[i] = 0;
    }
    
    
    jmag = 1;
    lat = 37.8; lon = 75.4;
    iyyyy = 2021; mmdd = 321; dhour = 11.0;
    //iyyyy = 2021; mmdd = 322; dhour = 23.0;
    hbeg = 80.0; //km
    hend = 600.0; //km
    hstp = 26.0; //km
    

    alt[0] = hbeg;
    for( i=1; i<nalt; i++) {
        alt[i] = alt[i-1] + hstp;
    }
    
    printf("\n");
    for( i=0 ; i<50 ; i++ ){
       fputs(jf[i] ? " T" : " F", stdout);
    }
    printf("\n");
    printf("%d %f %f %d %d %f", jmag, lat, lon, iyyyy, mmdd, dhour);
    printf("\n%f %f %f", hbeg, hend, hstp );
    
    printf("\nBefore Fortran subroutine...\n");
    iri_sub_(jf,    &jmag, &lat,  &lon, &iyyyy, &mmdd, &dhour,
             &hbeg, &hend, &hstp, outf, oarr);
    printf("After Fortran subroutine...\n\n");

    printf("EDP Peak=%10.3f [m^-3] at Height=%5.1f [km]\n",  oarr[5-1], oarr[6-1]);
    printf("Lat= %10.3f, Lon= %5.1f\n",  oarr[28-1], oarr[32-1] );

    /*
    printf("Altitude (km)    Ne (m^-3)\n");
    
    for( i=0; i<nalt; i++) {
        for( j=0 ; j<11 ; j++ ) {
            printf("%10.3f, %15.7f : \n", alt[i], outf[i][j]);
        }
        printf("\n");
    }
    
    for( i=0; i<100; i++) {
        printf("%10.3f\n", oarr[i]);
    }
     */
    
    return 0;
}

