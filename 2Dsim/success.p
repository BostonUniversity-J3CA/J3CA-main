set xrange [0:50]
set yrange [0:30]
set key right bottom
set xlabel 'Obstacle Distance at Detection (m)'
set ylabel 'Aircraft Velocity (m/s)'
plot "< awk '{if($1 == \"COLLIDE\") print}' results.dat" using 2:3 title "Collide", \
        "< awk '{if($1 == \"SUCCESS\") print}' results.dat" using 2:3 title "Success", \
        "< awk '{if($1 == \"STALL\") print}' results.dat" using 2:3 title "Stall" pt 4
pause(-1)
