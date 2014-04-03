// Scaling information
var pxPerMeter = screen.width/100; // 100 meters = screen width
var width      = screen.width; // meters
var height     = screen.height; // meters

// PARAMETERS THAT AFFECT PROGRAM - Feel free to change these parameters
// PLEASE NOTE: currently the drawing area is set up using the default JavaScript settings. This means that the canvas is inverted: the origin is
// the top left corner of the screen, and positive y moves down the screen. Position x still moves to the right
var num_obstacles = 1;
var obstacle_position = [rand(25,75),0,0]; // [x,y,z] ( in meters )
var obstacle_velocity = [rand(-15,15),rand(0,20),0]; // [vx,vy,vz] ( in meters per second )
var obstacle_radius   = rand(0.5,3);
var aircraft_radius   = 0.5; // meters
var aircraft_position = [0,30,0];
var aircraft_velocity = [12,0,0];
var avoidBy           = 3; // avoid the obstacle by n meters
var bumpCoeff         = 10; // A coefficient for the bump function that determines the bump's steepness
// NOTE: The program assumes that our aircraft is a point to make calculations easier. Which means that it makes each obstacle's radius = 
// obstacle_radius + aircraft_radius

// Detection range variables ( in seconds )
var rayTracingDetection    = 100; // Detection range for when ray tracing is used
var nonRayTracingDetection = 30;  // Detection range for when ray tracing is NOT used

// Please do not touch these variables!
var tracker = null;
var cx = null;
var queue = [];
var obstacles = [];
var anim = window.webkitRequestAnimationFrame ? window.webkitRequestAnimationFrame : window.mozRequestAnimationFrame ? window.mozRequestAnimationFrame : window.requestAnimationFrame ? window.requestAnimationFrame : null;
var play = true;
function draw(pos,radius,color,tracker){
    if ( !tracker ){
	cx.beginPath();
	cx.arc(pos[0],height-(pos[1]),radius,0,Math.PI*2,false);
	cx.strokeStyle=color;
	cx.strokeWidth="2";
	cx.stroke();
	cx.closePath();
    }
    else {
	tracker.beginPath();
	tracker.arc(pos[0],height-(pos[1]),radius,0,Math.PI*2,false);
	tracker.strokeStyle=color;
	tracker.strokeWidth="2";
	tracker.stroke();
	tracker.closePath();
    }
}
// Main drawing function: runs approximately 1/60 second (AKA 60 frames per second)
function update(){
    if ( play === true ){
	// Define the collision array, the collision times, and detection range (in seconds) 
	var collision = [0,0,0];
	var t         = -1;
	var t2        = -1;
	var closeness = 0;
	// Clear the screen
	cx.clearRect(0,0,width,height);
	// Now, we're going to loop through all of the aircraft, move them, and check for collisions
	for ( var i = queue.length-1; i > -1; i-- ){
	    // Reset the variables
	    collision = [0,0,0];
	    t  = -1;
	    t2 = -1;
	    queue[i].move();
	    // Draw the aircraft
	    if ( i != 0 ){ // If the current aircraft is NOT our aircraft
		draw(queue[i].getPosition(),queue[i].getRadius(),queue[i].getColor());
		// The ray variable tells our program if ray tracing was used or not. If ray.val == TRUE, then ray tracing was used
		// JavaScript does not let the programmer pass values by reference. Only objects are passed by reference
		// So ray should actually be a boolean passed by reference to the function detectCollisionPoint
		if ( detectCollisionPoint(queue[0],queue[i],collision,ray={"val":null}) === true ){
		    t  = timeUntilPoint(queue[0],collision); // Calculates the time it will take our aircraft to reach the collision point
		    t2 = timeUntilPoint(queue[i],collision);
		    closeness = ray.val ? rayTracingDetection+(10*Math.exp(-queue[i].getVelocity()[0])) : nonRayTracingDetection;  
		    $("#display").html(t-t2+"<br/>"+closeness);
		    if ( Math.abs(t-t2) < closeness && ( t >= 0 || t2 >= 0 ) ){
			// Draw the detection point
			cx.beginPath();
			cx.rect((collision[0])-5,height-(collision[1])-5,10,10);
			cx.strokeStyle="#0f0";
			cx.stroke();
			cx.closePath();
			// Set the obstacle to a red color
			queue[i].setColor("#f00");
			// Calculate a new trajectory around the obstacle
			collision[1] += avoidBy + queue[i].getRadius();
			collision[0]  = queue[i].getPosition()[0]+queue[i].getRadius()*2;
			// This function will be changed to adjust how quickly our aircraft should ascend
			queue[0].newTrajectory(collision,Math.abs(t-t2));
		    }
		}
		else {
		    queue[i].setColor("#00f");
		}
	    }
	    else {
		draw(queue[0].getPosition(),2,"#000",tracker);
	    }
	}
    }
    anim(update);
}
function timeUntilPoint(aircraft,point){
    var t   = -1;
    var pos = aircraft.getPosition();
    var vel = aircraft.getVelocity();
    for ( var i = 0; i < 3; i++ ){
	if ( vel[i] != 0 ){
	    return ( point[i] - pos[i] ) / vel[i];
	}
    }
    return t;
}
function rand(min,max){
    return min + Math.floor(Math.random()*(max-min+1));
}
$(document).ready(function(){
    cx = $("#field").attr({
	"width"   : width,
	"height"  : height
    }).css({
	"position" : "absolute",
	"top"      : 0,
	"left"     : 0
    })[0].getContext('2d');

    tracker = $("#tracker").attr({
	"width"  : width,
	"height" : height
    })[0].getContext('2d');

    queue.push(new Aircraft());
    queue[0].setRadius(aircraft_radius*pxPerMeter);
    queue[0].setPosition([aircraft_position[0]*pxPerMeter,aircraft_position[1]*pxPerMeter,aircraft_position[2]*pxPerMeter]);
    queue[0].setVelocity([aircraft_velocity[0]*pxPerMeter/60,aircraft_velocity[1]*pxPerMeter/60,aircraft_velocity[2]*pxPerMeter/60]);
    queue[0].setDefaultY(30*pxPerMeter);
    avoidBy *= pxPerMeter;
    // Create the obstacles
    var index = 0;
    for ( var i = 0; i < num_obstacles; i++ ){
	queue.push(new Aircraft());
	index = queue.length-1;
	queue[index].setPosition([obstacle_position[0]*pxPerMeter,obstacle_position[1]*pxPerMeter,obstacle_position[2]*pxPerMeter]);
	queue[index].setVelocity([obstacle_velocity[0]*pxPerMeter/60,obstacle_velocity[1]*pxPerMeter/60,obstacle_velocity[2]*pxPerMeter/60]);
	queue[index].setRadius(obstacle_radius*pxPerMeter+aircraft_radius*pxPerMeter);
	queue[index].setColor("#00f");
    }
    $("#field").click(function(){
	play = !play;
    });
    anim(update);
});
