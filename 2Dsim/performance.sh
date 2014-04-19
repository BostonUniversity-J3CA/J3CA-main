#!/bin/bash
dmax=50
dmin=0
dstep=1
vmax=15
vmin=5
vstep=1
percent=10
k=0
vsteps=$((($vmax-$vmin)/$vstep+1))
dsteps=$((($dmax-$dmin)/$dstep+1))
for i in $(seq $dmin $dstep $dmax); do
	for j in `seq $vmin $vstep $vmax`; do
		echo $i $j | ./run >> results.dat
		k=$(($k+1))
		if [ $(((100*$k)/((vsteps\*dsteps)))) -ge $percent ]; then
			echo $percent %
			percent=$(($percent+10))
		fi
		done
	done
gnuplot success.p
