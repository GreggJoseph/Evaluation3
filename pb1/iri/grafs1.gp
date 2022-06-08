#
#set terminal png size 2048,864 enhanced font "Helvetica,20"
#set output 'plots.png'
#
set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.5

#
set multiplot layout 1, 2 ;

set title "EDP for March 4, 2021 at 23:00 UT"
set xlabel "Plasma Frequency (MHz)"
set ylabel "Altitude (km)"
plot "edpData.1" using 2:1 with lines linestyle 1 
#
set title "ION Temp. for March 4, 2021 at 23:00 UT"
set xlabel "ION Temperature (K)"
set ylabel "Altitude (km)"
plot "edpData.1" using 3:1 with lines

unset multiplot
#

