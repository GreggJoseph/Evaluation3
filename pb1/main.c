#include <stdio.h>
#include <stdbool.h>

// iri_sub Function Prototype declaration
extern void iri_sub_(bool [], int *, float *, float *, int*, int *, float *,
                     float *, float *, float *, float [][20], float []);

int main(void) {

    printf("\nBefore var declarations:\n");

    int    i, j, nalt=21;
    int    jmag, iyyyy, mmdd, iut;
    int    ymdhms[6];
    float  lat, lon;
    float  dhour;
    float  hbeg, hend, hstp;
    float  alt[nalt];
    //char   *datadir = "iri";
    // Rows and columns between C and Fortran are switched.
    float  oarr[100], outf[1000][20];
    
    bool   jf[50] = { true }; //only sets the 1st element to true
    jmag = 1;
    lat = 37.8; lon = 75.4;
    iyyyy = 2021; mmdd = 321; dhour = 11.0+25.0;
    //iyyyy = 2021; mmdd = 322; dhour = 23.0+25.0;
    hbeg = 80.0; //km
    hend = 600.0; //km
    hstp = 26.0; //km
    

    alt[1] = hbeg;
    for( i=2; i<=nalt; i++) {
        alt[i] = alt[i-1] + hstp;
    }
    
    for( i=0 ; i<50 ; i++ ){
        //printf("%s", jf[i] ? "true\n" : "false\n");
        fputs(jf[i] ? "true\n" : "false\n", stdout);
    }
    printf("\n");
    for( i=0 ; i<50 ; i++ ){
        jf[i] = true;
    }
    
    for( i=0 ; i<50 ; i++ ){
        if(i>3 && i<7)   jf[i] = false;
        if(i==8)         jf[i] = true;
        if(i>21 && i<24) jf[i] = false;
        if(i==26)        jf[i] = true; // jf(26) == jf(8) == .true. for foF2
        if(i>27 && i<31) jf[i] = false;
        if(i>32 && i<36) jf[i] = false;
        
        fputs(jf[i] ? "true\n" : "false\n", stdout);
    }
    
    printf("Before running Fortran subroutine...\n");
    iri_sub_(jf, &jmag, &lat, &lon, &iyyyy, &mmdd, &dhour, &hbeg, &hend, &hstp, outf, oarr);
    printf("After running Fortran subroutine...\n");

    printf("NmF2= %10.3f [m^-3], hmF2= %5.1f [km]\n",  oarr[1], oarr[2]);
    printf("Ap= %10.3f, %d, B0= %5.1f\n",  oarr[41], (int)oarr[51], oarr[10]);

    
    printf("Altitude (km)    Ne (m^-3)\n");
    
    for( i=1; i<=nalt; i++) {
        for( j=1 ; j<=11 ; j++ ) {
            printf("%10.3f, %15.7f : ", alt[i], outf[i][j]);
        }
        printf("\n");
    }
    
    for( i=1; i<=100; i++) {
        printf("%10.3f\n", oarr[i]);
    }
    
    return 0;
}

