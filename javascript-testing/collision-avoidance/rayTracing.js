function rayTraceCollision(/*const int[]*/aircraft,/*const int[]*/obstacle,/*int*/radius,/*int[]*/collisionPoint){
    /**
     * This function will transfer over to C++
     * Here the program will detect if there is a possible
     * collision assuming a linear trajectory. TRUE means there is a collision.
     * Parameters: 
     * - aircraft is an object with the aircraft's current GPS coordinates and bounding radius, in the properties:
     * lat, lon, alt, radius, prevLat, prevLon, prevAlt
     * - obstacle is an object with the obstacle's current GPS coordinates and bounding radius, in the properties:
     * lat, lon, alt, radius
     * If a collision is detected, the array collisionPoint
     * will be updated with the coordinates of the projected collision.
     */
    
    // aircraft - [ 0 => lon, 1 => lat, 2 => alt, 3 => prevLon, 4 => prevLat, 5 => prevAlt ]
    
    // This creates a ray that goes beyond the obstacle 
    var dlon = aircraft[0] - aircraft[3];
    var dlat = aircraft[1] - aircraft[4];
    var dalt = aircraft[2] - aircraft[5];

    cx.beginPath();
    cx.moveTo(aircraft[0],aircraft[1]);
    cx.lineTo(1500,aircraft[1]);
    cx.strokeStyle="#f00";
    cx.stroke();
    cx.closePath();
    
    // Calculate whether a collision occurs. Ray tracing calculation is provided by:
    // www.ccs.neu.edu/home/fell/CSU540/programs/RayTracingFormulas.htm
    
    var a = dlon*dlon + dlat*dlat + dalt*dalt;
    var b = 2*dlon*(aircraft[3]-obstacle[0]) + 2*dlat*(aircraft[4]-obstacle[1]) + 2*dalt*(aircraft[5] - obstacle[2]);
    var c = Math.pow(aircraft[3]-obstacle[0],2) + Math.pow(aircraft[4]-obstacle[1],2) + Math.pow(aircraft[5]-obstacle[2],2)-Math.pow(radius,2);
    
    
    var discriminant = Math.pow(b,2) - (4*a*c);
    var collision = discriminant >= 0;
    if ( collision ){
	var t1 = (-b-Math.sqrt(Math.pow(b,2)-4*a*c))/(2*a);
	var t2 = (-b+Math.sqrt(Math.pow(b,2)-4*a*c))/(2*a);
	if ( t1 > 0 ){
	    var t = t1;
	}
	else {
	    if ( t2 > 0 ){
		var t = t2;
	    }
	}
	collisionPoint[0] = aircraft[3] + t*dlon;
	collisionPoint[1] = aircraft[4] + t*dlat;
	collisionPoint[2] = aircraft[5] + t*dalt;
	return true;
    }
    else {
	return false;
    }
}
    
