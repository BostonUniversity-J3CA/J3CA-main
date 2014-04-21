set title "Simulated Aircraft Path (Level Flight)"
set xlabel "X position (m)"
set ylabel "Y position (m)"
set xrange [0:100]
set yrange [-10:10]
plot "sim.dat" using 7:8 title 'Actual', '' using 3:4 title 'GPS (unfiltered)',  '' using 5:6 title 'GPS (filtered)'
pause(-1)
