$(document).ready(function(){
    // Default values, currently in pixels - will change to metric once the test is complete
    var minRadius      = 20;
    var maxRadius      = 40;
    var maxLeft        = $(window).width();
    var maxTop         = $(window).height();
    var aircraftRadius = 15;
    var collisionPoint = [];

    // Cache frequently accessed elements
    var cx = $("#sphere_region")[0].getContext('2d');
    var cxPos = {
	x : $("#sphere_region").position().left,
	y : $("#sphere_region").position().top
    }
    var obstacleSphere = null;
    // Variables (int[]) to store two points from clicks
    var point1 = [];
    var point2 = [];

    // variables (bool) that tells which point has been filled
    var point1IsEmpty = true;
    var point2IsEmpty = true;

    // Set the width and height of the canvas
    $("#sphere_region").prop({
	"width":$(window).width()*0.9,
	"height":$(window).height()
    });
    $("#create_random_sphere").click(function(){
	obstacleSphere = randomSphere();
	drawSphere(obstacleSphere);
    });
    $("#ray_box").on("mousemove",function(e){
	if ( point2IsEmpty == false ){
	    point2[0] = e.pageX;
	    point2[1] = e.pageY;
	    point2[2] = 0;
	    drawCollisionScene();
	}
    });
    $("#ray_box").click(function(e){
	if ( point1IsEmpty == false && point2IsEmpty == false ){
	    point1IsEmpty = true;
	    point2IsEmpty = true;
	    $("#notifications").html("No points are selected");
	    drawSphere(obstacleSphere);
	    return;
	}
	if ( point1IsEmpty == true ){
	    point1[0]     = e.pageX;
	    point1[1]     = e.pageY;
	    point1[2]     = 0;
	    point1IsEmpty = false;
	    $("#notifications").html("Point 1 is set. Please select another point");
	    return;
	}
	else if ( point2IsEmpty == true ) {
	    point2[0]     = e.pageX;
	    point2[1]     = e.pageY;
	    point2[2]     = 0;
	    point2IsEmpty = false;
	    $("#notifications").html("Point 1 is set. Point 2 is set");
	}
	drawCollisionScene();
	return;
    });
    function drawCollisionScene(){
	// Draw current sphere
	drawSphere(obstacleSphere);
	// Calculate collision
	var collision = detectCollision(
	    {
		"lat":point2[1],
		"lon":point2[0],
		"alt":point2[2],
		"prevLat":point1[1],
		"prevLon":point1[0],
		"prevAlt":point1[2],
		"radius":aircraftRadius
	    },
	    obstacleSphere);
	if ( collision ){
	    showCollision(collisionPoint);
	}
	return;
    }
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

	drawRay(aircraft.prevLon,aircraft.lon,aircraft.prevLat,aircraft.lat);
	// Calculate whether a collision occurs. Ray tracing calculation is provided by:
	// www.ccs.neu.edu/home/fell/CSU540/programs/RayTracingFormulas.htm

	var a = dlon*dlon + dlat*dlat + dalt*dalt;
	var b = 2*dlon*(aircraft.prevLon-obstacle.lon) + 2*dlat*(aircraft.prevLat-obstacle.lat) + 2*dalt*(aircraft.prevAlt - obstacle.alt);
	var c = Math.pow(aircraft.prevLon-obstacle.lon,2) + Math.pow(aircraft.prevLat-obstacle.lat,2) + Math.pow(aircraft.prevAlt-obstacle.alt,2)-Math.pow(aircraft.radius+obstacle.radius,2);


	var discriminant = Math.pow(b,2) - (4*a*c);
	console.log([a,b,c]);
	console.log(discriminant);
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
	function f(t){
	    var m = ((y2-y)/(x2-x));
	    var b = m*-1*x+y;
	    return m*t + b;
	}
	cx.beginPath();
	cx.moveTo(x,y);
	cx.lineTo(x2*100,f(x2*100));
	cx.strokeStyle="#f00";
	cx.stroke();
	cx.closePath();
    }
});
