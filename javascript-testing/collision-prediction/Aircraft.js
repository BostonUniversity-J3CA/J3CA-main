function Aircraft(){
    var self         = this;
    var radius       = 2; 
    var position     = [0,300,0];
    var origPosition = [0,300,0];
    var velocity     = [12 * pxPerMeter,0,0];
    var prevPosition = [0,0,0];

    var velocityRange = [
	[-10, 30],
	[-10, 30],
	[0, 0]
    ];

    this.color   = "#00f";
    this.setVelocity = function(x,y,z){
	velocity = [x,y,z];
    }
    this.setPosition = function(x,y,z){
	position = [x,y,z];
    }
    this.move        = function(){
	prevPosition = position.slice(); // This makes a copy of the position array
	position     = [
	    position[0] + velocity[0]/60,
	    position[1] + velocity[1]/60,
	    position[2] + velocity[2]/60
	]; 
	return position;
    }
    this.getPosition = function(){
	return position;
    }
    this.getRadius   = function(){
	return radius;
    }
    this.setRandomValues = function(){
	position = [
	    rand(0,canvasWidth),
	    rand(0,canvasHeight),
	    0
	];
	origPosition = [
	    position[0],
	    position[1],
	    position[2]
	];
	velocity = [
	    rand(velocityRange[0][0], velocityRange[0][1]),
	    rand(velocityRange[1][0], velocityRange[1][1]),
	    rand(velocityRange[2][0], velocityRange[2][1]),
	];
	radius = rand(2,5);
	return self;
    }
    this.setVelocityRange = function(range){
	velocityRange = range;
    }
    this.setOrigPosition = function(x,y,z){
	origPosition = [x,y,z];
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
    this.getVelocityRange = function(){
	return velocityRange;
    }
    return self;
}
