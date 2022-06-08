#
#set terminal png size 2048,864 enhanced font "Helvetica,20"
#set output 'plots.png'
#

set multiplot layout 1, 2 ;

set title "EDP"
set xlabel "Plasma Frequency (MHz)"
set ylabel "Altitude (km)"
plot "edpData.0" using 2:1 title "March 3, 2021 at 11:00 UT" with lines, \
"edpData.1" using 2:1 title "March 4, 2021 at 23:00 UT" with lines 
#
set title "ION Temperature"
set xlabel "ION Temperature (K)"
set ylabel "Altitude (km)"
plot 'edpData.0' using 3:1 title "March 3, 2021 at 11:00 UT" with lines, \
'edpData.1' using 3:1 title "March 4, 2021 at 23:00 UT" with lines

unset multiplot
#

