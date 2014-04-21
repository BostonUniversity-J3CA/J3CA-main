Okay, so the collision avoidance algorithm is making progress. I found that this algorithm needed to incorporate the rayTracing algorithm
as well because the algorithm used in collision-prediction only worked for obstacles with velocities in at least 2 directions. For obstacles only
moving in one direction or obstacles with no velocity at all it failed. So I checked for that situation and use ray tracing if it does occur.

Paths.js contains the required function "simple_path". This is the new trajectory that's followed if a collision is detected. Currently, it
uses the bump function which seems to work out well. I found that the rate of ascent can be (approximately) decided by the difference between the numerator and 
denominator in the function.

	    Rate of ascent =~ numerator - denominator

	    Bump = exp(-1/(1-x*x));

So to make life a little easier, I made the denominator some fraction of the numerator:

      	   New_Bump = exp(-N/(N*t));

where t is a coefficient that determines the steepness of the ascent.

---------------------------------------------------------------------------------------------------------------------------------------------------

As with all of my other programs: open index.html in a browser to see the algorithm in action. 

Currently only one obstacle is used in the program. If you would like to change the parameters of the program (such as obstacle velocity, position,
number of them, etc) then open main.js and adjust the corresponding values. They were named in such a way that's obvious which variables affect
which parameter in the program.

----------------------------------------------------------------------------------------------------------------------------------------------------
4/2/2014 - UPDATE

So, I changed the algorithm just a tiny bit...before the aircraft would change it's trajectory and keep ascending until it got to the point of
collision and then would descend back to the original trajectory. This wouldn't work very well if the obstacle was moving in the same direction
as our aircraft. To account for this, I made the algorithm: 1) ascend to a point above the calculated collision point ( collision point + obstacle
radius + safety factor ), 2) fly linearly until it passes the point ( obstacle center + obstacle radius + safety margin ), and 3) descend back to
the original trajectory. 

I believe this only works for one obstacle...currently it may not be easy to expand to multiple objects. I will likely have to reorganize my code
to make it more modular. 

My next step ( after calculating a rough accuracy ) is converting my code into C. This shouldn't be too bad, so will likely take about 2-3 hours 
(including: translating, testing, and debugging). I intend to place all of the necessary functions into one file since they are not very long.

I will keep you guys updated.