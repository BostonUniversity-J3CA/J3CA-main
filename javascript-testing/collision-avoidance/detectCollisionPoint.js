/* bool */function detectCollisionPoint(/*Aircraft*/obj1, /*Aircraft*/obj2, /*int []*/ collisionPoint,ray){
    var t = calculateT(obj1,obj2);
    if ( isNaN(t) ){
	// Collision may occur in head on. For some reason,
	// it doesn't recognize a head on collision as a collision, so we'll have to manually check
	var aircraft = obj1.getPosition().concat(obj1.getPrevPosition());
	var obstacle = obj2.getPosition().concat(obj2.getPrevPosition());
	var radius   = obj1.getRadius()+obj2.getRadius();
	if ( rayTraceCollision(aircraft,obstacle,radius,collisionPoint) ){
	    ray.val = true;
	    return true;
	}
	return false;
    }
    else {
	var pos = obj1.getPosition();
	var vel = obj1.getVelocity();
	collisionPoint[0] = pos[0] + vel[0]*t;
	collisionPoint[1] = pos[1] + vel[1]*t;
	collisionPoint[2] = pos[2] + vel[2]*t;
	ray.val = false;
	return true;
    }
}
