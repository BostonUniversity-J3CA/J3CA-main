    function detectCollision(aircraft,obstacle){
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

	// This creates a ray that goes beyond the obstacle 
	var dlon = aircraft.lon - aircraft.prevLon;
	var dlat = aircraft.lat - aircraft.prevLat;
	var dalt = aircraft.alt - aircraft.prevAlt;

	// Calculate whether a collision occurs. Ray tracing calculation is provided by:
	// www.ccs.neu.edu/home/fell/CSU540/programs/RayTracingFormulas.htm

	var a = dlon*dlon + dlat*dlat + dalt*dalt;
	var b = 2*dlon*(aircraft.prevLon-obstacle.lon) + 2*dlat*(aircraft.prevLat-obstacle.lat) + 2*dalt*(aircraft.prevAlt - obstacle.alt);
	var c = Math.pow(aircraft.prevLon-obstacle.lon,2) + Math.pow(aircraft.prevLat-obstacle.lat,2) + Math.pow(aircraft.prevAlt-obstacle.alt,2)-Math.pow(aircraft.radius+obstacle.radius,2);


	var discriminant = Math.pow(b,2) - (4*a*c);
	var collision = discriminant >= 0;
	if ( collision ){
	    var t1 = (-b-Math.sqrt(Math.pow(b,2)-4*a*c))/(2*a);
	    var t2 = (-b+Math.sqrt(Math.pow(b,2)-4*a*c))/(2*a);
	    if ( t1 > 0 ){
		return t = t1;
	    }
	    else {
		if ( t2 > 0 ){
		    return t = t2;
		}
	    }
	    collisionPoint[0] = aircraft.prevLon + t*dlon;
	    collisionPoint[1] = aircraft.prevLat + t*dlat;
	    collisionPoint[2] = aircraft.prevAlt + t*dalt;
	    return true;
	}
	else {
	    return false;
	}
    }
function predictCollision(aircraft,obstacle){
    /* This function works similarily to detectCollision().
     * However, this function can PREDICT if a collision will occur,
     * as well as if a collision is currently occurring.
     */
    var dx = aircraft.lon - obstacle.lon;
    var dy = aircraft.lat - obstacle.lat;
    var dz = aircraft.alt - obstacle.alt;
    var R  = aircraft.radius + obstacle.radius;
    var bx = obstacle.prevLon;
    var by = obstacle.prevLat;
    var bz = obstacle.prevAlt;
    var m  = Math.sqrt(Math.pow(obstacle.lon-bx,2)+Math.pow(obstacle.lat-by,2)+Math.pow(obstacle.alt-bz,2));
    
    var t  = calculateT(bx,by,bz,aircraft,m,dx,dy,dz,R);
    var data = "<tr>";
    data += "<td>"+aircraft.lon+"</td><td>"+aircraft.lat+"</td><td>"+aircraft.alt+"</td>";
    data += "<td>"+obstacle.lon+"</td><td>"+obstacle.lat+"</td><td>"+obstacle.alt+"</td>";
    data += "<td>"+t+"</td></tr>";
    $("#data").append(data);
    if ( Math.abs(t) < MAX_CLOSENESS ){
	return true;
    }
    return false;
}
