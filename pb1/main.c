#include <stdio.h>

//extern float ffunc_(float *, float *);
extern float  iri_web_(int *, int *, float *, float *, int*, int *, int *, int *,
                       float *, float *, int *, float *, float *, float *, float *, float *);

int main(void) {
    float a=1.0, b=2.0, c=5.0, d=6.0;

    printf("Before running Fortran subroutine:\n");
    printf("a=%f\n", a);
    printf("b=%f\n", b);

    //fsub_(&a,&b);
    //iri_web(jmag,jf,xlat,xlon,iy,mmdd,iut,hour,hxx,htec_max,ivar,vbeg,vend,vstp,outf,oar);
    
    int jmag,jf,iy,mmdd,iut,hour,ivar;
    float xlat,xlon,hxx,htec_max,vbeg,vend,vstp,outf,oar;
    
    jmag=1;
    jf=8;
    xlat=37.8; xlon=75.4;
    iy=2021; mmdd=0303; iut=1; hour=11;
    hxx=2;//km
    htec_max=20000;
    ivar=1;
    vbeg=0; vend=12; vstp=2;
    
    
    iri_web_(&jmag,&jf,&xlat,&xlon,&iy,&mmdd,&iut,&hour,
             &hxx,&htec_max,&ivar,&vbeg,&vend,&vstp,&outf,&oar);

    printf("After running Fortran subroutine:\n");
    printf("a=%f\n", a);
    printf("b=%f\n", b);



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

