/*------------------------------------------------------------------
 *  This routine performs coordinate transformations from Radar to
 *  GIS and Radar and back.
 *  C program to calculate Distance between Two Points on Earth
 *-----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* function prototypes */
double toRadians(const double);
double toDegrees(const double);
double distance(double, double, double, double);

int GIS2Radar(double *range,
              double *bearing,
              double glonInit,
              double glatInit,
              double glonFinal,
              double glatFinal);

int RtoG (double range,
          double bearing,
          double glonInit,
          double glatInit,
          double *glonFinal,
          double *glatFinal);



int main( int argc, char *argv[] ) {
    double lat1 = 37.0;// North
    double long1 = 75.0;// West
    double lat2 = 18.0;// North
    double long2 = 66.0;// West
    
    // compute the range and bearing bwteen the two GIS points
    printf("\n\nGiven...\n");
    printf("Initial Latitude: %6.2lf, Initial Longitude: %6.2lf\n", lat1, long1);
    printf("Final Latitude: %6.2lf, Final Longitude: %4.2lf\n", lat2, long2);
    printf("Resulting...\n");

    double rng, bear;
    int r1 = GIS2Radar(&rng, &bear, long1, lat1, long2, lat2);
    if(r1) {
        // print the ranger and bearing, where bearin is relative to North
        //printf("range = %lf km, bearing = %d degrees\n", rng, (int)(toDegrees(bear)+360.0) % 360 );
        printf("\t---> Range = %6.2lf km, and Bearing = %4d degrees\n", rng, (int)bear );
    } else {
        printf("Error in GIS2Radar()\n\n");
    }

    
    // compute the destination Longitude & Latitude based on
    // starting Lat-Long and Range & Bearing
    double glonFinal, glatFinal;
    printf("\n\nGiven...\n");
    printf("Initial Latitude: %6.2lf, Initial Longitude: %6.2lf\n", lat1, long1);
    printf("with Range: %6.2lf, and Bearing: %4.2lf\n", rng, bear);
    printf("Resulting...\n");

    int r2 = RtoG(rng, bear, long1, lat1, &glonFinal, &glatFinal);
    if(r2) {
        printf("\t---> Destination Latitude: %6.2lf, Destination Longitude: %6.2lf\n\n", glatFinal, glonFinal);
    } else {
        printf("Error in RtoG()\n\n");
    }
    
    
    return(0);
}


int GIS2Radar(double *range, double *bearing,
              double glonInit, double glatInit,
              double glonFinal, double glatFinal ) {

    int result;
    int good=1, bad=0;
    double pX, pY, dL;
    double lat1, long1, lat2, long2;
        
    *range = distance(glatInit, glonInit, glatFinal, glonFinal);
    
    lat1  = toRadians(glatInit);
    long1 = toRadians(glonInit);
    lat2  = toRadians(glatFinal);
    long2 = toRadians(glonFinal);
    
    dL = long2 - long1;
    pX = cos(lat2)* sin(dL);
    pY = cos(lat1)*sin(lat2) - sin(lat1)*cos(lat2)* cos(dL);
    *bearing = atan2(pX, pY);
    
    // make bearing relative to direction North
    *bearing = (double)( (int)(toDegrees(*bearing)+360.0) % 360 );

    result = good;
    return (result);
}

int RtoG(double range, double bearing,
         double glonInit, double glatInit,
         double *glonFinal, double *glatFinal ) {
    
    int result;
    int good=1, bad=0;
    double R = 6371.0;
    double lat1, lon1, lat2, lon2;
    double ad, theta;
    
    ad = range/R;
    theta = toRadians(bearing);
    lat1  = toRadians(glatInit);
    lon1  = toRadians(glonInit);
    
    lat2 = asin( sin(lat1)*cos(ad) + cos(lat1)*sin(ad)*cos(theta) );
    lon2 = lon1 + atan2( sin(theta)*sin(ad)*cos(lat1), cos(ad) - sin(lat1)*sin(lat2) );
    
    *glatFinal = toDegrees(lat2);
    *glonFinal = toDegrees(lon2);
    
    result = good;
    
    return (result);
}


// Utility function for converting degrees to radians
double toRadians(const double degree)
{
    double one_deg = (M_PI)/180.0;
    return (one_deg * degree);
}

// Utility function for converting radians to degrees
double toDegrees(const double radian)
{
    double one_rad = 180.0/(M_PI);
    return (one_rad * radian);
}
 
// Utility function for computing distance between to lat-long points
double distance(double lat1, double long1, double lat2, double long2)
{
    // Convert the latitudes and longitudes from degree to radians.
    lat1  = toRadians(lat1);
    long1 = toRadians(long1);
    lat2  = toRadians(lat2);
    long2 = toRadians(long2);
     
    // Haversine Formula
    double dlong = long2 - long1;
    double dlat  = lat2 - lat1;
 
    double ans = pow(sin(dlat/2.0), 2) + cos(lat1)*cos(lat2)*pow(sin(dlong/2.0), 2);
 
    ans = 2.0 * asin(sqrt(ans));
 
    // Radius of Earth in Kilometers, R = 6371.0, based on Wikipedia
    // Use R = 3959.0 for miles
    double R = 6371.0;
     
    // Calculate the result
    ans *= R;
 
    return ans;
}
 
