function simple_path_sigmoid(x,y,targetX,targetY,finalY,t){
    // Sigmoid
    if ( x < targetX ){
	return targetY/((targetY*0.75)+Math.exp(-t));
    }
    else {
	return -finalY/((finalY*0.75)+Math.exp(t));
    }
}
function simple_path(x,y,targetX,targetY,finalY,t){
    // Bump function
    var coeff = 0.75;
    if ( x < targetX ){
	if ( x*x != targetY ){
	    return Math.exp(-targetY/(targetY*coeff));
	}
    }
    else {
	if ( y > finalY ){
	    return -Math.exp(-finalY/(finalY*coeff));
	}
	else {
	    return 0;
	}
    }
    return 0;
}
