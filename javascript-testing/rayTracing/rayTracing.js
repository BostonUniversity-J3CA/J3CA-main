$(document).ready(function(){
    // Default values, in imperial units
    var minRadius      = 6;
    var maxRadius      = 20;
    var maxLeft        = $(window).width();
    var maxTop         = $(window).height();
    var aircraftRadius = 5;
    var collisionPoint = [];

    // Cache frequently accessed elements
    var cx = $("#sphere_region")[0].getContext('2d');
    var cxPos = {
	x : $("#sphere_region").position().left,
	y : $("#sphere_region").position().top
    }
    var obstacleSphere = null;

    // Set the width and height of the canvas
    $("#sphere_region").prop({
	"width":$(window).width()*0.9,
	"height":$(window).height()
    });
    $("#create_random_sphere").click(function(){
	obstacleSphere = randomSphere();
	drawSphere(obstacleSphere);
    });
    $("#ray_box").click(function(e){
	var lon  = 2;
	var lat  = e.pageY;
	var alt  = 0;
	// prevLon is the longitude of the plane last time the GPS
	// coordinates were saved
	var prevLon = 0;
	var prevLat = e.pageY; // Assume latitude and altitude don't change
	var prevAlt = 0;
	
	// Draw current sphere
	drawSphere(obstacleSphere);
	// Calculate collision
	var collision = detectCollision(
	    {
		"lat":lat,
		"lon":lon,
		"alt":alt,
		"prevLat":prevLat,
		"prevLon":prevLon,
		"prevAlt":prevAlt,
		"radius":aircraftRadius
	    },
	    obstacleSphere);
	showCollision(collisionPoint);
	return;
    });
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

	drawRay(aircraft.prevLon,maxLeft,aircraft.prevLat,aircraft.lat);
	// Calculate whether a collision occurs. Ray tracing calculation is provided by:
	// www.ccs.neu.edu/home/fell/CSU540/programs/RayTracingFormulas.htm
	var a = dlon*dlon + dlat*dlat + dalt*dalt;
	var b = 2*dlon*(aircraft.prevLon-obstacle.lon) + 2*dlat*(aircraft.prevLat-obstacle.lat) + 2*dalt*(aircraft.prevAlt - obstacle.alt);
	var c = obstacle.lon*obstacle.lon + obstacle.lat*obstacle.lat + obstacle.alt*obstacle.alt + aircraft.prevLon*aircraft.prevLon + aircraft.prevLat*aircraft.prevLat  + aircraft.prevAlt*aircraft.prevAlt  - 2*(obstacle.lon*aircraft.prevLon + obstacle.lat*aircraft.prevLat + obstacle.alt*aircraft.prevAlt) - ((obstacle.radius+aircraft.radius)*(obstacle.radius+aircraft.radius));
	
	var discriminant = Math.pow(b,2) - (4*a*c);
	var collision = discriminant >= 0;
	if ( collision ){
	    var t = (-b-Math.sqrt(Math.pow(b,2)-4*a*c))/(2*a);
	    collisionPoint[0] = aircraft.prevLon + t*dlon;
	    collisionPoint[1] = aircraft.prevLat + t*dlat;
	    collisionPoint[2] = aircraft.prevAlt + t*dalt;
	    return true;
	}
	else {
	    return false;
	}
    }
    function showCollision(point){
	cx.beginPath();
	cx.rect(point[0]-5,point[1]-5,10,10);
	cx.strokeStyle="#00f";
	cx.stroke();
	cx.closePath();
	return;
    }
    function randomSphere(){
	var radius = randNumber(minRadius,maxRadius);
	var x = randNumber(cxPos.x+radius,maxLeft-radius);
	var y = randNumber(cxPos.y+radius,maxTop-radius);
	return {"radius":radius,"lon":x,"lat":y,"alt":0};
    }
    function randNumber(min,max){
	return min + Math.floor( Math.random() * (max - min + 1) );
    }
    function drawSphere(sphere){
	cx.clearRect(0,0,maxLeft,maxTop);
	cx.beginPath();
	cx.arc(sphere.lon,sphere.lat,sphere.radius+aircraftRadius,0,2*Math.PI);
	cx.strokeStyle = "#000";
	cx.stroke();
	cx.closePath();
	return;
    }
    function drawRay(x,x2,y,y2){
	cx.beginPath();
	cx.moveTo(x,y);
	cx.lineTo(x2,y2);
	cx.strokeStyle="#f00";
	cx.stroke();
	cx.closePath();
    }
});
