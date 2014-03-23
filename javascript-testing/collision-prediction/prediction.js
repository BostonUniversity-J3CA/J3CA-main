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
    var point = [0,0,0];
    var t = detectCollisionPoint(obj1,obj2,point);
    var vel1  = obj1.getVelocity();
    var pos1  = obj1.getOrigPosition();
    
    if ( t == true ){
	console.log(point);
    }
    /*var x = pos1.x + vel1.x*t;
    var y = pos1.y + vel1.y*t;

    cx.beginPath();
    cx.rect(x-5,y-5,10,10);
    cx.strokeStyle="#0f0";
    cx.stroke();
    cx.closePath();
    $("#time_display").html(t+"<br/>"+x+"<br/>"+y);*/
    if ( t > 0 ){
	return true;
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
