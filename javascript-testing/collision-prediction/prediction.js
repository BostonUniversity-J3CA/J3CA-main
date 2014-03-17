var zoom         = 2; // This factor will make the displays actually see-able
var pxPerMeter   = $(window).width()/100; // Window width divided by 100 meters. The length of our flight area
var flightDistance = 100; // meters
var ourcraft     = null;
var obstacles    = [];
// These variables are used for drawing to the screen
var cx           = null;
var canvasWidth  = 0;
var canvasHeight = 0;
// Animation variables
var playAnimation = true;
// Constants
var NUM_OBSTACLES = 1;
var MAX_CLOSENESS = 3; // The difference in seconds between the s and t constants in the collision formula. If s = t, then the obstacle and our
// aircraft will be at the same exact point in space at that time.
function Aircraft(){
    var self     = this;
    var radius   = 2*zoom; // The length of the aircraft is 1 meter but I'm applying a factor of safety of 2
    var position = {
	x : 0,  // Will be in pixels converted from meters using the factor pxPerMeter defined above
	y : 300, // Arbitrary for now, just as an example
	z : 0
    }
    var origPosition = {
	x : 0,
	y : 300,
	z : 0
    }
    var velocity = {
	x : 12 * pxPerMeter, // Meters per second converted to pixels per second
	y : 0, 
	z : 0
    }
    var prevPosition = {
	x : 0,
	y : 0,
	z : 0
    }
    this.color   = "#00f";
    this.setVelocity = function(x,y,z){
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
    }
    this.setPosition = function(x,y,z){
	position.x = x;
	position.y = y;
	position.z = z;
    }
    this.move        = function(){
	prevPosition.x = position.x;
	prevPosition.y = position.y;
	prevPosition.z = position.z;
	position.x += velocity.x/60; // Velocity is in pixels per second, dividing by 60 will give pixels per frame
	position.y += velocity.y/60;
	position.z += velocity.z/60;
	return position;
    }
    this.getPosition = function(){
	return position;
    }
    this.getRadius   = function(){
	return radius;
    }
    this.setRandomValues = function(){
	position = {
	    x : rand(0,canvasWidth),
	    y : rand(0,canvasHeight),
	    z : 0
	};
	origPosition = {
	    x : position.x,
	    y : position.y,
	    z : position.z
	}
	velocity = {
	    x : rand(-10,30),
	    y : rand(-10,30),
	    z : 0
	};
	radius = rand(2,5);
	return self;
    }
    this.getOrigPosition = function(){
	return origPosition;
    }
    this.getVelocity = function(){
	return velocity;
    }
    this.getPrevPosition = function(){
	return prevPosition;
    }
    return self;
}
function rand(min,max){
    return min + Math.floor(Math.random()*(max-min+1));
}
function update(){
    cx.clearRect(0,0,canvasWidth,canvasHeight);
    var position = ourcraft.move();
    var color    = "#00f";
    cx.beginPath();
    cx.arc(Math.round(position.x),Math.round(position.y),ourcraft.getRadius(),0,2*Math.PI,false);
    cx.strokeStyle="#000";
    cx.stroke();
    cx.closePath();
    for ( var i = 0, n = obstacles.length; i < n; i++ ){
	position = obstacles[i].move();
	color = willCollide(ourcraft,obstacles[i])?(color="#f00"):(color="#00f");
	obstacles[i].color = color;

	cx.beginPath();
	cx.arc(Math.round(position.x),Math.round(position.y),obstacles[i].getRadius(),0,2*Math.PI,false);
	cx.strokeStyle=obstacles[i].color
	cx.stroke();
	cx.closePath();
    }
    if ( playAnimation == true ){
	window.webkitRequestAnimationFrame(update);
    }
    return;
}
function willCollide(obj1,obj2){
    var vel1 = obj1.getVelocity();
    var vel2 = obj2.getVelocity();
    var pos1 = obj1.getPosition();
    var pos2 = obj2.getPosition();
    var t    = 0;
    var s    = 0;
    var code1= 0;
    var code2= 0;

    if ( vel1.x != 0 ){
	code1 += 1;
    }
    if ( vel1.y != 0 ){
	code1 += 2;
    }
    if ( vel1.z != 0 ){
	code1 += 4;
    }
    if ( vel2.x != 0 ){
	code2 += 1;
    }
    if ( vel2.y != 0 ){
	code2 += 2;
    }
    if ( vel2.z != 0 ){
	code2 += 4;
    }
    if ( code2 == 0 ){
	// If the obstacle is stationary
	if ( code1 > 0 ){
	    if ( code1 % 2 == 1 ){
		// If the code is odd, then the velocity in x is always not zero
		t = ( pos2.x - pos1.x ) / vel1.x;
		s = 0;
	    }
	    else if ( code1 == 4 ){
		t = ( pos2.z - pos1.z ) / vel1.z;
		s = 0;
	    }
	    else {
		t = ( pos2.y - pos1.y ) / vel1.y;
		s = 0;
	    }
	}
	else {
	    return false; // In this scenario, neither of the aircraft are moving....so no collision is remotely possible
	}
    }
    else if ( code1 == 0 ){
	// If our aircraft is stationary but another aircraft is moving
	if ( code2 > 0 ){
	    if ( code2 % 2 == 1 ){
		// If the code is odd
		t = 0;
		s = ( pos1.x - pos2.x ) / vel2.x;
	    }
	    else if ( code2 == 4 ){
		// If only the z velocity is non-zero
		t = 0;
		s = ( pos1.z - pos2.z ) / vel2.z;
	    }
	    else {
		// If only the y velocity is non-zero
		t = 0;
		s = ( pos1.y - pos2.y ) / vel2.y;
	    }
	}
	else {
	    return false; // Both aircraft are not moving
	}
    }
    else {
	if ( code1 == code2 ){
	    if ( code1 % 2 == 1 ){
		t = ( pos2.x - pos1.x ) / ( vel1.x - vel2.x );
	    }
	    else if ( code1 == 4 ){
		t = ( pos2.z - pos1.z ) / ( vel1.z - vel2.z );
	    }
	    else{
		t = ( pos2.y - pos1.y ) / ( vel1.y - vel2.y );
	    }
	}
	else {
	    var ourPos = [0,0]; 
	    var ourVel = [0,0];
	    var obsPos = [0,0];
	    var obsVel = [0,0];
	    var pos1IsSet = false;
	    var pos2IsSet = false;
	    // Check for a velocity in the x-direction
	    if ( code1 % 2 == 1 ){
		if ( pos1IsSet == false ){
		    ourPos[0] = pos1.x;
		    ourVel[0] = vel1.x;
		    pos1IsSet = true;
		}
		else {
		    ourPos[1] = pos1.x;
		    ourVel[1] = vel1.x;
		}
	    }
	    if ( code1 == 4 ){
		// There's a velocity in the z-direction
		if ( pos1IsSet == false ){
		    ourPos[0] = pos1.z;
		    ourVel[0] = vel1.z;
		    pos1IsSet = true;
		}
		else {
		    ourPos[1] = pos1.z;
		    ourVel[1] = vel1.z;
		}
	    }
	    else {
		// There's a velocity in the y-direction
		if ( pos1IsSet == false ){
		    ourPos[0] = pos1.y;
		    ourVel[0] = vel1.y;
		    pos1IsSet = true;
		}
		else {
		    ourPos[1] = pos1.y;
		    ourVel[1] = vel1.y;
		}
	    }
	    // Now compare our aircraft's position and velocity to that of the obstacle to solve for t and s
	    if ( code2 % 2 == 1 ){
		// The obstacle has a velocity in the x-direction
		if ( pos2IsSet == false ){
		    obsPos[0] = pos2.x;
		    obsVel[0] = vel2.x;
		    pos2IsSet = true;
		}
		else {
		    obsPos[1] = pos2.x;
		    obsVel[1] = vel2.x;
		}
	    }
	    if ( code2 == 4 ){
		// The obstacle has a velocity in the z-direction
		if ( pos2IsSet == false ){
		    obsPos[0] = pos2.z;
		    obsVel[0] = vel2.z;
		    pos2IsSet = true;
		}
		else {
		    obsPos[1] = pos2.z;
		    obsVel[1] = vel2.z;
		}
	    }
	    else {
		// The obstacle has a velocity in the x-direction
		if ( pos2IsSet == false ){
		    obsPos[0] = pos2.y;
		    obsVel[0] = vel2.y;
		    pos2IsSet = true;
		}
		else {
		    obsPos[1] = pos2.y;
		    obsVel[1] = vel2.y;
		}
	    }
	    if ( ourVel[0] != 0 && ourVel[1] != 0 && obsVel[0] != 0 && obsVel[1] != 0 ){
		t = solveForTWithS(ourPos,ourVel,obsPos,obsVel,obj1.getRadius(),obj2.getRadius());
		s = ( ourPos[1] - obsPos[1] + ( t * ourVel[1] ) ) / ourVel[1];
	    }
	    else if ( obsVel[0] != 0 && obsVel[1] != 0 ){
		// This function still needs to be written
		s = ( obsPos[1] - ourPos[1] ) / obsVel[1];
		if ( ourVel[0] != 0 ){
		    t = ( obsPos[0] - ourPos[0] + ( s * obsVel[0] ) ) / ( ourVel[0] );
		}
		else {
		    t = ( obsPos[0] - ourPos[0] + ( s * obsVel[0] ) ) / ( ourVel[1] );
		}
	    }
	}
    }
    $("#time_display").html(t.toFixed(0)+","+s.toFixed(0)+","+(t-s).toFixed(0));
    if ( Math.abs(t - s) < MAX_CLOSENESS ) {
	cx.beginPath();
	cx.arc(t*vel1.x-s*vel2.x,t*vel1.y-s*vel2.y,20,0,Math.PI*2,true);
	cx.strokeStyle="#0f0";
	cx.stroke();
	cx.closePath();
	return true;
    }
    return false;
}
function solveForTWithS(pos1,pos2,vel1,vel2,radius1,radius2){
    var t = ( pos2[0]-pos1[0] ) / vel1[1];
    t    += vel2[0] * ( pos1[1] - pos2[1] ) / Math.pow(vel1[1],2);
    t    /= 1 - ( vel2[1] * vel2[0] / vel1[1] );
    return t;
}
function toggleAnim(){
    playAnimation = !playAnimation;
    animate();
    return;
}
function animate(){
    if ( playAnimation ){
	window.webkitRequestAnimationFrame(update);
    }
    return;
}
$(document).ready(function(){
    cx           = $("#football_field");
    cx.attr({
	width : $(window).width(),
	height: $(window).height()*0.9
    });
    cx           = cx[0].getContext('2d');
    canvasWidth  = $(window).width();
    canvasHeight = $(window).height();
    ourcraft = new Aircraft();
    for ( var i = 0; i < NUM_OBSTACLES; i++ ){
	obstacles[i] = new Aircraft().setRandomValues();
    }
    animate();
}).click(toggleAnim);
