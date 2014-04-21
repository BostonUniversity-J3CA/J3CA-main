set size ratio .2
set title "Curve testing"
set xlabel "X position (m)"
set ylabel "Y position (m)"
set xrange [0:100]
set yrange [-5:15]
plot "sim.dat" using 7:8 title 'Actual', "" using 3:6 title 'Commanded'
pause(-1)
