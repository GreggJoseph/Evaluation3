#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>


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
extern void read_ig_rz_ ();
extern void readapf107_ ();
float wp(float);

#define PI 3.1415926535897932
FILE *out;

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
    int    jf[50];
    
    //c Please also make sure to use the default setting for the switches jf
    //c as noted in this comment section further down:
    //c       jf(4,5,6,21,23,28,29,30,33,35,39,40,47)=.false. all others .true.
    for( i=0 ; i<50 ; i++ ){
        jf[i] = 1; //sets all to true
        
        if(i>2 && i<6)   jf[i] = 0; // jf[4,5,6] = false
        if(i==20)        jf[i] = 0; // jf[21] = false
        if(i==22)        jf[i] = 0; // jf[23] = false
        if(i>26 && i<30) jf[i] = 0; // jf[28,29,30] = false
        if(i==32)        jf[i] = 0; // jf[33] = false
        if(i==34)        jf[i] = 0; // jf[35] = false
        if(i>37 && i<40) jf[i] = 0; // jf[39, 40] = false
        if(i==46)        jf[i] = 0; // jf[47] = false
    }
    
    
    jmag = 0;
    lat = 37.8; lon = 75.4;
    iyyyy = 2021; mmdd = 303; dhour = 11.0;
    //iyyyy = 2021; mmdd = 304; dhour = 23.0;
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
    
    
    read_ig_rz_();
    readapf107_();
    printf("\n\n * Before Fortran subroutine...\n");
    
    iri_sub_(jf,    &jmag, &lat,  &lon, &iyyyy, &mmdd, &dhour,
             &hbeg, &hend, &hstp, outf, oarr);
    
    printf("\n *After Fortran subroutine...\n\n");

    
    
    printf("EDP Peak=%10.3f [m^-3] at Height=%5.1f [km]\n",  oarr[5-1], oarr[6-1]);
    printf("Geo Lat= %10.3f, Geo Lon= %5.1f\n",  oarr[28-1], oarr[32-1] );



    
    if((out = fopen("edpData.dat", "w")) == NULL) {
         printf("\n\n\nUnable to open the file <%s>.\n", "edpData.dat");
         printf("Program Stopped... \n\n");
         exit(0);
       }

    // electron density (frequency MHz), ion temp (K)
    printf("\n   Alt (km),  Plasma Freq. (MHz),  ION Temp (K)\n");
    for( i=0; i<nalt; i++) {
        printf("%10.3f, %15.7f, %15.7f\n", alt[i], wp(outf[i][1-1])/(2.0*PI), outf[i][3-1]);
        fprintf(out,"%10.3f, %15.7f, %15.7f\n",
                alt[i], wp(outf[i][1-1])/(2.0*PI), outf[i][3-1]);
    }
    
    /*
    for( i=0; i<nalt; i++) {
        for( j=0 ; j<20 ; j++ ) {
            printf("%10.3f, %15.7f : \n", alt[i], outf[i][j]);
        }
        printf("\n");
    }
     */
    
    /*
    for( i=0; i<100; i++) {
        printf("%10.3f\n", oarr[i]);
    }
     */

    fclose(out);
    system("gnuplot -p grafs.gp");
    
    return 0;
}

// Plasma angular Frequency function, takes an Electron number density value (M^3)
float wp(float ne) {
    float e = 1.602176462e-19;
    float e0 = 8.854187817e-12;
    float me = 9.10938188e-31;
    
    // return plasma frequency in MHz
    return( sqrt((ne * e*e) / (e0 * me)) * 1.0e-6);
}
