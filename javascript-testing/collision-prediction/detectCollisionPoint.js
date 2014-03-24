/**
 * I am using the following equations to solve for the point of collision
 *   x_0 + v_x*t = x2_0 + v2_x*s
 *   y_0 + v_y*t = y2_0 + v2_y*s
 *   z_0 + v_z*t = z2_0 + v2_z*s
 */
/* bool */function detectCollisionPoint(/*Aircraft*/obj1, /*Aircraft*/obj2, /*int []*/ collisionPoint){
    var t = calculateT(obj1,obj2);
    if ( isNaN(t) ){
	// No collision!
	return false;
    }
    else {
	var pos = obj1.getPosition();
	var vel = obj1.getVelocity();
	var x   = pos.x + vel.x*t;
	var y   = pos.y + vel.y*t;
	cx.beginPath();
	cx.rect(x-5,y-5,10,10);
	cx.strokeStyle="#0f0";
	cx.stroke();
	cx.closePath();
    }
}
/* bool */function detectCollisionPoint_cramersRule(/*Aircraft*/ obj1, /*Aircraft*/ obj2, /*int []*/ collisionPoint){
    var pos1 = obj1.getPosition();
    var pos2 = obj2.getPosition();
    var old1 = obj1.getPrevPosition();
    var old2 = obj2.getPrevPosition();
    var vel1 = obj1.getVelocity();
    var vel2 = obj2.getVelocity();

    var t,s,dx,dy,dz;
    // Use Cramer's rule to solve for the parametic variables s and t
    var d = det([
	[ -vel1.x, vel2.x ],
	[ -vel1.y, vel2.y ]
    ]);
    var ansx = ( pos1.x - pos2.x );
    var ansy = ( pos1.y - pos2.y );
    if ( d != 0 ){
	dx = det([
	    [ ansx, vel2.x ],
	    [ ansy, vel2.y ]
	]);
	dy = det([
	    [ -vel1.x, ansx ],
	    [ -vel1.y, ansy ]
	]);
	t = dx / d;
	s = dy / d;
    }
    else {
	d = det([
	    [ -vel1.y, vel2.y ],
	    [ -vel1.z, vel2.z ]
	]);
	ansy = ( pos1.y - pos2.y );
	ansz = ( pos1.z - pos2.z );
	if ( d != 0 ){
	    dy = det([
		[ ansy, vel2.y ],
		[ ansz, vel2.z ]
	    ]);
	    dz = det([
		[ -vel1.y, ansy ],
		[ -vel2.z, ansz ]
	    ]);
	    t = dy / d;
	    s = dz / d;
	}
	else {
	    d = det([
		[ -vel1.x, vel2.x ],
		[ -vel1.z, vel2.z ]
	    ]);
	    ansx = ( pos1.x - pos2.x );
	    ansz = ( pos1.z - pos2.z );
	    if ( d != 0 ){
		dx = det([
		    [ ansx, vel2.x ],
		    [ ansz, vel2.z ]
		]);
		dz = det([
		    [ -vel1.x, ansx ],
		    [ -vel2.z, ansz ]
		]);
		t = dx / d;
		s = dz / d;
	    }
	    else {
		// No collision will occur!
		return false;
	    }
	}
    }
    var x = pos1.x + vel1.x*t;
    var y = pos1.y + vel1.y*s;
    cx.beginPath();
    cx.rect(x-5,y-5,10,10);
    cx.strokeStyle="#0f0";
    cx.stroke();
    cx.closePath();
}
function det(matrix){
    var det = 0;
    if ( matrix.length != matrix[0].length ){
	return -1;
    }
    else {
	det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	return det;
    }
}
