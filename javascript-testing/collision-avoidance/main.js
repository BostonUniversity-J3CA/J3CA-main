// Scaling information
var pxPerMeter = 10; // 10 pixels = 1 meter
var width      = 100; // meters
var height     = 60; // meters

// PARAMETERS THAT AFFECT PROGRAM - Feel free to change these parameters
// PLEASE NOTE: currently the drawing area is set up using the default JavaScript settings. This means that the canvas is inverted: the origin is
// the top left corner of the screen, and positive y moves down the screen. Position x still moves to the right
var num_obstacles = 1;
var obstacle_position = [rand(width/2,width),rand(0,height/2),0]; // [x,y,z] ( in meters )
var obstacle_velocity = [rand(-0.5,0),rand(0,0.5),0]; // [vx,vy,vz] ( in meters per second )
var obstacle_radius   = rand(0.2,1);
var aircraft_radius   = 1; // meters
var aircraft_position = [0,25,0];
var aircraft_velocity = [0.5,0,0];
// NOTE: The program assumes that our aircraft is a point to make calculations easier. Which means that it makes each obstacle's radius = 
// obstacle_radius + aircraft_radius

// Detection range variables ( in seconds )
var rayTracingDetection    = 500; // Detection range for when ray tracing is used
var nonRayTracingDetection = 30;  // Detection range for when ray tracing is NOT used

// Please do not touch these variables!
var cx = null;
var queue = [];
var obstacles = [];
var anim = window.webkitRequestAnimationFrame ? window.webkitRequestAnimationFrame : window.mozRequestAnimationFrame ? window.mozRequestAnimationFrame : window.requestAnimationFrame ? window.requestAnimationFrame : null;
var play = true;
function draw(pos,radius,color){
    cx.beginPath();
    cx.arc(pos[0]*pxPerMeter,pos[1]*pxPerMeter,radius/2*pxPerMeter,0,Math.PI*2,false);
    cx.strokeStyle=color;
    cx.stroke();
    cx.closePath();
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
	cx.clearRect(0,0,width*pxPerMeter,height*pxPerMeter);
	// Now, we're going to loop through all of the aircraft, move them, and check for collisions
	for ( var i = queue.length-1; i > -1; i-- ){
	    // Reset the variables
	    collision = [0,0,0];
	    t  = -1;
	    t2 = -1;
	    queue[i].move();
	    // Draw the aircraft
	    draw(queue[i].getPosition(),queue[i].getRadius(),queue[i].getColor());
	    if ( i != 0 ){ // If the current aircraft is NOT our aircraft
		// The ray variable tells our program if ray tracing was used or not. If ray.val == TRUE, then ray tracing was used
		// JavaScript does not let the programmer pass values by reference. Only objects are passed by reference
		// So ray should actually be a boolean passed by reference to the function detectCollisionPoint
		if ( detectCollisionPoint(queue[0],queue[i],collision,ray={"val":null}) === true ){
		    t  = timeUntilPoint(queue[0],collision); // Calculates the time it will take our aircraft to reach the collision point
		    t2 = timeUntilPoint(queue[i],collision);
		    closeness = ray.val ? rayTracingDetection : nonRayTracingDetection;  
		    if ( Math.abs(t-t2) < closeness && ( t >= 0 || t2 >= 0 ) ){
			// Draw the detection point
			cx.beginPath();
			cx.rect(collision[0]*pxPerMeter-5,collision[1]*pxPerMeter-5,10,10);
			cx.strokeStyle="#0f0";
			cx.stroke();
			cx.closePath();
			// Set the obstacle to a red color
			queue[i].setColor("#f00");
			// Calculate a new trajectory around the obstacle
			collision[1]+=10;
			// This function will be changed to adjust how quickly our aircraft should ascend
			queue[0].newTrajectory(collision,Math.abs(t-t2));
		    }
		}
		else {
		    queue[i].setColor("#00f");
		}
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
	"width"   : width*pxPerMeter,
	"height"  : height*pxPerMeter
    }).css({
	"position" : "absolute",
	"top"      : 0,
	"left"     : 0
    })[0].getContext('2d');

    queue.push(new Aircraft());
    queue[0].setRadius(aircraft_radius);
    queue[0].setPosition(aircraft_position);
    queue[0].setVelocity(aircraft_velocity);
    // Create the obstacles
    var index = 0;
    for ( var i = 0; i < num_obstacles; i++ ){
	queue.push(new Aircraft());
	index = queue.length-1;
	queue[index].setPosition(obstacle_position);
	queue[index].setVelocity(obstacle_velocity);
	queue[index].setRadius(obstacle_radius+aircraft_radius);
	queue[index].setColor("#00f");
    }
    $("#field").click(function(){
	play = !play;
    });
    anim(update);
});
