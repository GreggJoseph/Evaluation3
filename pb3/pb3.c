/*------------------------------------------------------------------
 *  This routine sorts the dataset that is read in from a file.
 *
 *  It sorts the data set by date and time
 *  It then calcualtes the median value for the 
 *    foF2 and hmF2 column data.
 *-----------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef MAC
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif


/* function prototypes */

double  *vector(int, int);
void   free_vector(double *, int);
void   scan(int *);
void   readin(int *);
int    comp_function(const void *, const void *);
double medianFilter_classic(double *, int);
double medianFilter_classic2(double *, int);


char datafile[20];
int  n;

struct row {
    char date[20]; //0
    char ddd[20]; //1
    char time[20];//2
    int  cscore; //3
    double foF2; //4
    char foF1[20]; //5
    double foE; //6
    char foEs[20]; //7
    char hEs[20]; //8
    double hmF2; //9
    char hmF1[20]; //10
    double hmE; //12
    double B0; //13
    double B1; //14
    char D1[20]; //15
    int id;
};
struct row  *table;


int main( int argc, char *argv[] ) {
    int i;

	if( argc == 1 ) {
		printf("\n>>> Enter the filename <<<\n\n");
		exit(1);
	}

	strcpy(datafile, argv[1]);
    
	scan(&n);
        
    //printf("n = %d\n\n", n);
    
    table  = (struct row *) calloc((unsigned long) (n+1), sizeof(struct row));
    if(table == NULL) {
        printf("Allocation error in data structure <<table>>...\n\n");
        printf("Program Stopped... (Hit 'Enter' to abort)\n\n");
        int i_c;
        if ((i_c = getchar()) == EOF)
            exit(0);
    }

	readin(&n);
    
    printf("num elements = %ld\n", sizeof(table->date)/sizeof(*table->date));
    printf("size = %ld\n", sizeof(char));

    //qsort(table->date, sizeof(table->date)/sizeof(*table->date), sizeof(*table->date), comp_function);
    for(i=1 ; i<=n ; i++) {
        printf("%d - %s, %s\n", table[i].id, table[i].time, table[i].date);
    }
    
    char temp[20];
    for(i=1; i<=n; i++){
       for(int j=i+1; j<=n; j++){
          if(strcmp(table[i].date, table[j].date) > 0 ){
              
             strcpy(temp, table[i].date); //swapping element[i] with element[j]
             strcpy(table[i].date, table[j].date);
             strcpy(table[j].date, temp);
              
              strcpy(temp, table[i].time); //swapping element[i] with element[j]
              strcpy(table[i].time, table[j].time);
              strcpy(table[j].time, temp);
              
              int k = i;
              table[i].id = j;
              table[j].id = k;
              
              table[i].foF2 = table[j].foF2;
              table[j].foF2 = table[k].foF2;
              table[i].hmF2 = table[j].hmF2;
              table[j].hmF2 = table[k].hmF2;
          }
       }
    }
    
 
    double *foF2, *hmF2;
    foF2 = vector(1, n);
    hmF2 = vector(1, n);
    
    for(i=1 ; i<=n ; i++) {
		printf("%d - %s, %s, %lg, %lg\n", table[i].id, table[i].time, table[i].date, table[i].foF2, table[i].hmF2);
        foF2[i] = table[i].foF2;
        hmF2[i] = table[i].hmF2;
	}

    //printf("foF2: %lg\n", medianFilter_function(&table->foF2, n));
    //printf("hmF2: %lg\n", medianFilter_function(&table->hmF2, n));
    
    printf("Median Filter of (peak plasmafrequency) foF2: %lg\n", medianFilter_classic(foF2, n));
    printf("Median Filter of (peak height) hmF2: %lg\n", medianFilter_classic(hmF2, n));
    
    printf("Median Filter 2 of foF2: %lg\n", medianFilter_classic2(foF2, n));
    printf("Median Filter 2 of hmF2: %lg\n", medianFilter_classic2(hmF2, n));
    
    free( table );
    free_vector(foF2, 1);
    free_vector(hmF2, 1);
    
    return(0);

}

double medianFilter_classic(double a[], int nn) {
    double mf;
    //printf("nn = %d, (nn+1)/2=%d\n", nn, (nn+1)/2);
    //printf("a[(nn+1)/2] = %lg\n", a[(nn+1)/2]);
    
    if(nn % 2 == 0){ // even
        mf = ( a[nn/2] + a[nn/2+1] ) / 2;
    } else { //odd
        int m = (nn+1)/2;
        mf = ( a[m] );
    }
    return (mf);
}

double medianFilter_classic2(double a[], int nn) {
    double mf;
    if(nn % 2 == 0){ // even
        mf = ( a[nn/2-1] + a[nn/2] ) / 2;
    } else { //odd
        mf = ( a[(nn-1)/2] );
    }
    return (mf);
}

int comp_function(const void *a, const void *b) {
    return (strcmp((char *)a,(char *)b));
}


/*********************************************************************
* scan.c
*   Determin the number of file entries, return pointer to number
***********************************************************************/
void scan(int *nc)
{
  int     nnc=0;
  int     lcnt, i;
  char    head[3][256];

  char   y0[20], y1[20], y2[20];
  int    y3;
  double  y4, y5, y6, y7, y8, y9, y10, y11, y12, y13;

  FILE    *fp1;

/*
 * SCAN Data file for data of interest, Date (y0), Time (y2), foF2(y4), and hmF2 (y9)
 */
    if((fp1 = fopen(datafile, "r")) == NULL) {
       printf("\n\n\nUnable to open Calibration file <%s>.\n"
              "Check to see if the file exists in default directory  - or -\n"
              "Program Stopped... \n\n", datafile);
       exit(0);
    }

   for(i=0; i<2 ; i++)
       fgets(head[i], 255, fp1);
    
    while( (lcnt = fscanf(fp1,"%s %s %s %d %lg %s %lg %s %s %lg %s %lg %lg %lg",
          &y0, &y1, &y2, &y3, &y4, &y5, &y6, &y7, &y8, &y9, &y10, &y11, &y12, &y13)) == 14 ) {
          nnc++;
          if( lcnt != 14)
              printf("\nERROR reading <%s> file, at line {%d}.\n", datafile, nnc);
    }
    
    fclose(fp1);

    *nc = nnc;
    return;
}



/************************************************************************
* SUBROUTINE readin
* Reads in data and fills problem data arrays.
************************************************************************/
void readin(int *nc)
{

  int   i;
  char  head[3][256];
  FILE  *fp1;

   if((fp1 = fopen(datafile, "r")) == NULL) {
     printf("\n\n\nUnable to open file <%s>.\n"
            "Check to see if the file exists in default directory  - or -\n"
            " Give the proper path name.\n\n"
            "Program Stopped... \n\n", datafile);
     exit(0);
   }

   for(i=0; i<2 ; i++){
       fgets(head[i], 255, fp1);
       //puts(head[i]);
   }
        
   for( i=1 ; i<= *nc ; i++ ) {
       if( fscanf(fp1,"%s %s %s %d %lg %s %lg %s %s %lg %s %lg %lg %lg",
                  &table[i].date,
                  &table[i].ddd,
                  &table[i].time,
                  &table[i].cscore,
                  &table[i].foF2,
                  &table[i].foF1,
                  &table[i].foE,
                  &table[i].foEs,
                  &table[i].hEs,
                  &table[i].hmF2,
                  &table[i].hmF1,
                  &table[i].hmE,
                  &table[i].B0,
                  &table[i].B1) != 14 ) {
           printf("\nInput file error in <%s>\n\nQuit Program...\n\n",datafile);
           exit(0);
       }
       table[i].id = i;
   }

   fclose( fp1 );
   return;
}


/*********************************************************************
 *  VECTOR.C
 * Allocates a double vector with range [nl..nh].
 *********************************************************************/
double *vector(int nl, int nh)
{
    double *v;
    int len;

    len = nh - nl + 1;

    v = (double *) calloc((unsigned) len, sizeof(double));
    if (!v) {
        printf("Allocation failure in vector()\n\n");
        exit(1);
    }

    return v-nl;
}




/**********************************************************************
 *  FREE_VEC.C
 * Frees a double vector allocated by vector().
 *********************************************************************/
void free_vector(double *v, int nl)
{
      free(( char * ) (v + nl)) ;
}


