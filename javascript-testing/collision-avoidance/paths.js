function simple_path_sigmoid(x,y,targetX,targetY,finalY,t){
    // Sigmoid
    if ( x < targetX ){
	return targetY/((targetY*0.75)+Math.exp(-t));
    }
    else {
	return -finalY/((finalY*0.75)+Math.exp(t));
    }
}
function simple_path(x,y,targetX,targetY,finalY,detectionDistance){
    if ( Math.abs(x - queue[1].getPosition()[0]) < detectionDistance*pxPerMeter ){
	if ( y < targetY ){
	    return Math.exp(-targetY/(targetY*bumpCoeff));
	}
	else {
	    return 0;
	}
    }
    else {
	if ( y > finalY ){
	    return -Math.exp(-finalY/(finalY*bumpCoeff));
	}
	else {
	    return 0;
	}
    }
    return 0;
}
