#!/bin/bash
dmax=50
dmin=0
dstep=1
vmax=25
vmin=5
vstep=2
ovmin=0
ovmax=-20
ovstep=-1
percent=10
k=0
vsteps=$((($vmax-$vmin)/$vstep+1))
ovsteps=$((($ovmax-$ovmin)/$ovstep+1))
dsteps=$((($dmax-$dmin)/$dstep+1))
for r in $(seq $ovmin $ovstep $ovmax); do
	for i in $(seq $dmin $dstep $dmax); do
		for j in `seq $vmin $vstep $vmax`; do
			echo $j $i 0 0 $r 0 0 | ./run >> results.dat
			k=$(($k+1))
			if [ $(((100*$k)/((vsteps\*dsteps\*ovsteps)))) -ge $percent ]; then
				echo $percent %
				percent=$(($percent+10))
			fi
		done
	done
done
gnuplot success.p
