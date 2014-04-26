set title "Thrust vs Position"
set xlabel "X position (m)"
set ylabel "Y position (m)"
set xrange [0:100]
plot "sim.dat" using 3:5 title 'Thrust'
pause(-1)
