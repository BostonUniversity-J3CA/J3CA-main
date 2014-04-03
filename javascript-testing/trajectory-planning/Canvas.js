var Canvas = (function(){
    var self  = this;
    var queue = [];
    var cx    = null
    var play  = true;
    var ids   = {};
    var width = 0;
    var height= 0;

    function update(){
	if ( play === true ){
	    cx.clearRect(0,0,width,height);
	    for ( var i = queue.length-1; i > -1; i-- ){
		queue[i][0](queue[i][1]);
	    }
	}
	window.webkitRequestAnimationFrame(update);
	return;
    }
    function square(params){
	cx.beginPath();
	cx.rect(params.x,params.y,params.w,params.h);
	cx.strokeStyle=params.color;
	cx.stroke();
	cx.closePath();
    }
    this.setDimensions = function(w,h){
	width = w;
	height = h;
    }
    this.setCx = function(canvas){
	cx = canvas;
    }
    this.drawSquare = function(x,y,w,h,color,id){
	queue.push([square,{
	    "x":x,
	    "y":y,
	    "w":w,
	    "h":h,
	    "color":color
	}]);
	if ( ids[id] != null ){
	    queue.splice(ids[id],1);
	}
	ids[id] = queue.length-1;
	return;
    }
    this.pause = function(){
	play = false;
    }
    this.play = function(){
	play = true;
    }
    window.webkitRequestAnimationFrame(update);
    return self;
})();
