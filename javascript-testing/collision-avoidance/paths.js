function simple_path_sigmoid(x,y,targetX,targetY,finalY,t){
    // Sigmoid
    if ( x < targetX ){
	return targetY/((targetY*0.75)+Math.exp(-t));
    }
    else {
	return -finalY/((finalY*0.75)+Math.exp(t));
    }
}
function simple_path(x,y,targetX,targetY,finalY){
    if ( x < targetX ){
	if ( y < targetY ){
	    return Math.exp(-targetY/(targetY*bumpCoeff));
	}
	else {
	    return 0;
	}
    }
    else {
	if ( y > finalY && (queue[0].getPosition()[0] - (queue[1].getPosition()[0]+queue[1].getRadius())) > 5*pxPerMeter ){
	    return -Math.exp(-finalY/(finalY*bumpCoeff));
	}
	else {
	    return 0;
	}
    }
    return 0;
}
