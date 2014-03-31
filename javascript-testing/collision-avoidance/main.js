var cx = null;
var num_obstacles = 1;
var obstacles = [];
var queue = [];
var anim = window.webkitRequestAnimationFrame ? window.webkitRequestAnimationFrame : window.mozRequestAnimationFrame ? window.mozRequestAnimationFrame : window.requestAnimationFrame ? window.requestAnimationFrame : null;
var play = true;
// Scaling information
var pxPerMeter = 10; // 10 pixels = 1 meter
var width      = 200*pxPerMeter;
var height     = 100*pxPerMeter;
function draw(pos,radius,color){
    cx.beginPath();
    cx.arc(pos[0],pos[1],radius,0,Math.PI*2,false);
    cx.strokeStyle=color;
    cx.stroke();
    cx.closePath();
}
function update(){
    if ( play === true ){
	var collision = [0,0,0];
	var t         = -1;
	var t2        = -1;
	var closeness = 0;
	cx.clearRect(0,0,width,height);
	for ( var i = queue.length-1; i > -1; i-- ){
	    collision = [0,0,0];
	    t  = -1;
	    t2 = -1;
	    queue[i].move();
	    draw(queue[i].getPosition(),queue[i].getRadius(),queue[i].getColor());
	    if ( i != 0 ){
		if ( detectCollisionPoint(queue[0],queue[i],collision,ray={"val":null}) === true ){
		    t  = timeUntilPoint(queue[0],collision);
		    t2 = timeUntilPoint(queue[i],collision);
		    closeness = ray.val?500:30;
		    $("#display").html(closeness);
		    if ( Math.abs(t-t2) < closeness && ( t >= 0 || t2 >= 0 ) ){
			cx.beginPath();
			cx.rect(collision[0]-5,collision[1]-5,10,10);
			cx.strokeStyle="#0f0";
			cx.stroke();
			cx.closePath();
			queue[i].setColor("#f00");
			// Calculate a new trajectory around the obstacle
			collision[1]+=10;
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
	"width"   : width,
	"height"  : height
    }).css({
	"position" : "absolute",
	"top"      : 0,
	"left"     : 0
    })[0].getContext('2d');

    queue.push(new Aircraft());
    // Create the obstacles
    var index = 0;
    for ( var i = 0; i < num_obstacles; i++ ){
	queue.push(new Aircraft());
	index = queue.length-1;
	queue[index].setPosition([rand(width/2,width),rand(0,height/2),0]);
	queue[index].setVelocity([rand(-2,0),rand(0,2),0]);
	queue[index].setRadius(rand(2,6)+queue[0].getRadius());
	queue[index].setColor("#00f");
    }
    $("#field").click(function(){
	play = !play;
    });
    anim(update);
});
