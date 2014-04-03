function Aircraft(){
    var self         = this;
    var position     = [0,300,0];
    var defaultY     = 300;
    var velocity     = [2,0,0];
    var prevPosition = [0,0,0];
    var id           = "";
    var color        = "#000";
    var radius       = 3;
    var point        = null;
    var t            = 0;
    var pointIsLocked= false;
    var angle        = 0;
    
    function linear(){
	prevPosition = position.slice();
	position[0]+=velocity[0];
	position[1]+=velocity[1];
	position[2]+=velocity[2];
    }
    function bump(){
	prevPosition = position.slice();
	position[0] += velocity[0];
	var add = simple_path(position[0],position[1],point[0],point[1],defaultY);
	position[1] += add;
	position[2] += velocity[2];
	if ( position[0] >= point[0] ){
	    pointIsLocked = false;
	}
	if ( height-position[1] < defaultY+5 && height-position[1] > defaultY-5 ){
	    self.move     = linear;
	}
    }
    this.move = linear;
    this.newTrajectory = function(pt){
	if ( pointIsLocked === false ){
	    point = pt;
	    pointIsLocked = true;
	    self.move = bump;
	}
    }
    this.setColor    = function(col){
	color = col;
    }
    this.setPosition = function(pos){
	position = pos;
    }
    this.setVelocity = function(vel){
	velocity = vel;
    }
    this.setId       = function(name){
	id = name;
    }
    this.setRadius   = function(r){
	radius = r;
    }
    this.getColor    = function(){
	return color;
    }
    this.getRadius   = function(){
	return radius;
    }
    this.getId       = function(){
	return id;
    }
    this.getPosition = function(){
	return position;
    }
    this.getVelocity = function(){
	return velocity;
    }
    this.getPrevPosition = function(){
	return prevPosition;
    }
    this.setDefaultY     = function(y){
	defaultY = y;
    }
    return self;
}
