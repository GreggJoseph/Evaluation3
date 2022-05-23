public class GeoMath
    {
        public static readonly double EarthRadius = 6378.1; //#Radius of the Earth km
        public Tuple<double,double> GetPointByDistanceAndHeading(double fmLat, double fmLon, double heading, double distanceKm)
        {      
            
            double bearingR = heading.ToRadians();
            
            double latR = fmLat.ToRadians();
            double lonR = fmLon.ToRadians();

            double distanceToRadius = distanceKm / EarthRadius;

            double newLatR = Math.Asin(Math.Sin(latR) * Math.Cos(distanceToRadius)
                            + Math.Cos(latR) * Math.Sin(distanceToRadius) * Math.Cos(bearingR));

            double newLonR = lonR + Math.Atan2(
                                                Math.Sin(bearingR) * Math.Sin(distanceToRadius) * Math.Cos(latR),
                                                Math.Cos(distanceToRadius) - Math.Sin(latR) * Math.Sin(newLatR)
                                               );

            return  new Tuple<double, double>(newLatR.ToDegrees(), newLonR.ToDegrees());
            
        }
    }

    public static class NumericExtensions
    {
        public static double ToRadians(this double degrees)
        {
            return (Math.PI / 180) * degrees;
        }
        public static double ToDegrees(this double radians)
        {
            return (180 / Math.PI) * radians;
        }
    }



R = 6378.1 #Radius of the Earth
brng = 1.57 #Bearing is 90 degrees converted to radians.
d = 15 #Distance in km

#lat2  52.20444 - the lat result I'm hoping for
#lon2  0.36056 - the long result I'm hoping for.

lat1 = math.radians(52.20472) #Current lat point converted to radians
lon1 = math.radians(0.14056) #Current long point converted to radians

lat2 = math.asin( math.sin(lat1)*math.cos(d/R) +
     math.cos(lat1)*math.sin(d/R)*math.cos(brng))

lon2 = lon1 + math.atan2(math.sin(brng)*math.sin(d/R)*math.cos(lat1),
             math.cos(d/R)-math.sin(lat1)*math.sin(lat2))

lat2 = math.degrees(lat2)
lon2 = math.degrees(lon2)

print(lat2)
print(lon2)

