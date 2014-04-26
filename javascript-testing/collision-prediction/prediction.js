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
var playAnimation = false;
// Constants
var num_obstacles = 1;
var max_closeness = 1; // The difference in seconds between the s and t constants in the collision formula. If s = t, then the obstacle and our
// aircraft will be at the same exact point in space at that time.
var velocityRange = [
    [-10,30],
    [-10,30],
    [0,0]
];
var positionRange = [];
var defPosition = [0,300,0];
var ourVel      = [12*pxPerMeter,0,0];
function rand(min,max){
    return min + Math.floor(Math.random()*(max-min+1));
}
function update(){
    cx.clearRect(0,0,canvasWidth,canvasHeight);
    var position = ourcraft.move();
    var color    = "#00f";
    var r        = ourcraft.getRadius();
    cx.beginPath();
    cx.arc(Math.round(position[0]),Math.round(position[1]),1,0,2*Math.PI,false);
    cx.strokeStyle="#000";
    cx.stroke();
    cx.closePath();
    for ( var i = 0, n = obstacles.length; i < n; i++ ){
	position = obstacles[i].move();
	color = willCollide(ourcraft,obstacles[i])?(color="#f00"):(color="#00f");
	obstacles[i].color = color;

	cx.beginPath();
	cx.arc(Math.round(position[0]),Math.round(position[1]),obstacles[i].getRadius()+r,0,2*Math.PI,false);
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
    var point   = [0,0,0];
    var t1 = -1;
    var t2 = -1;
    
    if ( detectCollisionPoint(obj1,obj2,point) ){
	t1 = getT(obj1,point);
	t2 = getT(obj2,point);
	$("#main").html(t1-t2);
	if ( Math.abs(t1 - t2) <= max_closeness ){
	    drawCollisionPoint(point);
	    return true;
	}
    }
    return false;
}
function drawCollisionPoint(point){
    cx.beginPath();
    cx.rect(point[0]-5,point[1]-5,10,10);
    cx.strokeStyle="#0f0";
    cx.stroke();
    cx.closePath();
}
/*int*/function getT(/*Aircraft*/ aircraft, /*vector<int>*/ point){
    /*vector<int>*/var pos  = aircraft.getPosition();
    /*vector<int>*/var vel  = aircraft.getVelocity();
    /*int*/        var t    = -1;       
    for ( var i = 0; i < 3; i++ ){
	if ( vel[i] != 0 ){
	    t = ( point[i] - pos[i] ) / vel[i];
	    return t;
	}
    }
    return t;
}
function animate(){
    if ( playAnimation ){
	window.webkitRequestAnimationFrame(update);
    }
    return;
}
function systemStart(){
    playAnimation = false;
    ourcraft = new Aircraft();
    ourcraft.setOrigPosition(defPosition[0],defPosition[1],defPosition[2]);
    ourcraft.setPosition(defPosition[0],defPosition[1],defPosition[2]);
    ourcraft.setVelocity(ourVel[0],ourVel[1],ourVel[2]);
    obstacles = [];
    for ( var i = 0; i < num_obstacles; i++ ){
	obstacles[i] = new Aircraft();
	obstacles[i].setVelocityRange(velocityRange);
	obstacles[i].setPositionRange(positionRange);
	obstacles[i].setRandomValues();
    }
}
function saveOptions(){
    num_obstacles = $("#num_objects").val();
    max_closeness = $("#closeness").val();
    defPosition   = [$("#pos_x").val()*1,$("#pos_y").val()*1,$("#pos_z").val()*1];
    ourVel        = [$("#vel_x").val()*1,$("#vel_y").val()*1,$("#vel_z").val()*1];
    velocityRange = [[$("#min_x").val(),$("#max_x").val()],[$("#min_y").val(),$("#max_y").val()],[$("#min_z").val(),$("#max_z").val()]];
    positionRange = [[$("#pos_min_x").val(),$("#pos_max_x").val()],[$("#pos_min_y").val(),$("#pos_max_y").val()],[$("#pos_min_z").val(),$("#pos_max_z").val()]];
    $("#options").hide();
    $("#main").show();
    systemStart();
}
$(document).ready(function(){
    cx           = $("#football_field");
    cx.attr({
	width : $(window).width(),
	height: $(window).height()*0.9
    }).css("top","50px");
    cx           = cx[0].getContext('2d');
    canvasWidth  = $(window).width();
    canvasHeight = $(window).height();
    // Display default values
    $("#num_objects").val(num_obstacles);
    var defVal = velocityRange;
    $("#min_x").val(defVal[0][0]);
    $("#max_x").val(defVal[0][1]);
    $("#min_y").val(defVal[1][0]);
    $("#max_y").val(defVal[1][1]);
    $("#min_z").val(defVal[2][0]);
    $("#max_z").val(defVal[2][1]);
    $("#pos_min_x").val(0);
    $("#pos_max_x").val(canvasWidth);
    $("#pos_min_y").val(0);
    $("#pos_max_y").val(canvasHeight);
    $("#pos_min_z").val(0);
    $("#pos_max_z").val(0);
    positionRange = [
	[0,canvasWidth],
	[0,canvasHeight],
	[0,0]
    ];
    var vel = ourVel;
    $("#vel_x").val(vel[0]);
    $("#vel_y").val(vel[1]);
    $("#vel_z").val(vel[2]);
    var orig = defPosition;
    $("#pos_x").val(orig[0]);
    $("#pos_y").val(orig[1]);
    $("#pos_z").val(orig[2]);
    $("#closeness").val(max_closeness);

    // Set button functionality
    $("#options_button").click(function(){
	$("#main").hide();
	$("#options").show();
    });
    $("#start_button").click(function(){
	playAnimation = true;
	animate();
    });
    $("#pause_button").click(function(){
	playAnimation = false;
    });
    $("#reset_button").click(function(){
	systemStart();
	update();
    });
    $("#save_options").click(function(){
	saveOptions();
    });
    systemStart();
});
