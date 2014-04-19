set xrange [0:50]
set yrange [0:15]
set key right bottom
plot "< awk '{if($1 == \"COLLIDE\") print}' results.dat" using 2:3 title "Collide", \
        "< awk '{if($1 == \"SUCCESS\") print}' results.dat" using 2:3 title "Success", \
        "< awk '{if($1 == \"STALL\") print}' results.dat" using 2:3 title "Stall"
pause(-1)
