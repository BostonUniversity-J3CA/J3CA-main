rayTracing ( the beginning parts of the collision detection algorithm ) tested the effectiveness of ray tracing for detecting collisions with
a stationary sphere. This part of the algorithm takes it one step forward and will PREDICT if and when a collision between a ray and a moving
sphere will occur without looping. Without loops, the algorithm is more efficient.

To test this algorithm, open index.html in any non-IE browser ( Google Chrome, Firefox, and Safari all work. Opera hasn't been tested )

1) Click the "Start" button to begin the program
   1.1) INFO: the black dot/circle is our aircraft, the blue dots are other aircraft that represent potential obstacles. If they turn red, then
   	the program has calculated that that obstacle will intersect with our aircraft. A green box shows the point of intersection. Intersection
	is based on a time range ( not absolute time ). So if our aircraft and the obstacle will reach the intersection point within t seconds of
	each other, then it's considered a collision.
2) Click the "Pause" button to pause the program
3) Click the "Reset" button to reset the program. Click "Start" to begin again
4) Click "Options" to adjust the programs parameters. Aircraft velocity, position, number of obstacles, and detection range ( time t from 1.1 )
   can all be adjusted. Click "Save" to set the parameters

