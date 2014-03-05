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
var NUM_OBSTACLES = 20;
var DETECTION_DISTANCE  = 600;
var MIN_TIME_DIFF       = 5;
var IGNORE_TIME         = -0.5;
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
    var R  = (obj1.getRadius()+obj2.getRadius()); // Assume our aircraft is a point, and give the other aircraft a radius of our aircraft radius plus
    // the obstacle's aircraft radius
    var vel1 = obj1.getVelocity();
    var vel2 = obj2.getVelocity();
    var pos1 = obj1.getPosition();
    var pos2 = obj2.getPosition();
    
    var dv   = [vel1.x-vel2.x,vel1.y-vel2.y,vel1.z-vel2.z];
    var dp   = [pos1.x-pos2.x,pos1.y-pos2.y,pos1.z-pos2.z];

    var times= [];
    for ( var i = 0, n = dv.length; i < n; i++ ){
	if ( dv[i] == 0 ){
	    times[i] = 0;
	}
	else {
	    times[i] = ( R - dp[i] ) / dv[i];
	}
    }
    /*if ( Math.sqrt(times[0]^2+times[1]^2) < DETECTION_DISTANCE ){
	return true;
    }*/
    var timediff = Math.abs(times[0]-times[1]);
    var dd       = Math.sqrt( Math.pow(dp[0],2) + Math.pow(dp[1],2) );
    //$("#time_display").html(timediff+"<br/>"+dd);
    if ( timediff < MIN_TIME_DIFF ){
	if ( times[0] > IGNORE_TIME && times[1] > IGNORE_TIME ){
	    if ( dd < DETECTION_DISTANCE ){
		return true;		    
	    }
	}
    }
    return false;
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
