function normalize(vector){
    var length = Math.sqrt(Math.pow(vector.x,2)+Math.pow(vector.y,2)+Math.pow(vector.z,2));
    var vec    = {
	x : vector.x / length,
	y : vector.y / length,
	z : vector.z / length
    }
    return vec;
}
function sphere_calculateCollision(aircraft,obstacle){
    var pos1  = aircraft.getPosition();
    var dir1  = normalize(aircraft.getVelocity());
    var orig1 = aircraft.getOrigPosition();
    var obs1  = obstacle.getPosition();
    var R     = aircraft.getRadius() + obstacle.getRadius();

    var ray   = subtract(pos1,orig1);
    var cylpt = subtract(obs1,pos1);
    var cross1 = cross(cylpt,ray);
    var cross2 = cross(dir1,ray);

    var d = dot(ray,ray);
    var a = dot(cross2,cross2);
    var b = 2 * dot(cross2,cross1);
    var c = dot(cross1,cross1) - (R*R*d);
    console.log(cross2,ray,dir1);
    /*if ( a == 0 ){
	// Calculate ray-circle intersection
	return detectCollision(aircraft,obstacle);
    }*/

    var t  = (-b+Math.sqrt(Math.pow(b,2)-4*a*c))/(2*a);
    var mt = (-b-Math.sqrt(Math.pow(b,2)-4*a*c))/(2*a);

    if ( t <= 0 ){
	if ( mt > 0 ){
	    return mt;
	}
	else {
	    return 0;
	}
    }
    else {
	return t;
    }
    return 0;
}
function subtract(a,b){
    var vector = {};
    for ( var i in a ){
	vector[i] = a[i]-b[i];
    }
    return vector;
}
function cross(a,b){
    return {
	x:a.y*b.z - b.y*a.z,
	y:b.x*a.z - a.x*b.z,
	z:a.x*b.y - a.y*b.x
    };
}
function dot(a,b){
    var sum = 0;
    for ( var i in a ){
	sum += a[i]*b[i];
    }
    return sum;
}
/*function calculateT(aircraft,obstacle){
    var pos1 = aircraft.getPosition();
    var pos2 = obstacle.getPosition();
    var vel1 = aircraft.getVelocity();
    var vel2 = obstacle.getVelocity();
    var r    = aircraft.getRadius() + obstacle.getRadius();

    var P1x = pos1.x;
    var P1y = pos1.y;
    var P1z = pos1.z;
    var V1x = vel1.x;
    var V1y = vel1.y;
    var V1z = vel1.z;

    var P2x = pos2.x;
    var P2y = pos2.y;
    var P2z = pos2.z;
    var V2x = vel2.x;
    var V2y = vel2.y;
    var V2z = vel2.z;

    var t = Math.sqrt(V2y*V1z - V1y*V2z + (8*Math.pow(P1x,2)*Math.pow(V2x,2)*V1y*V2y*V1z*V2z - 4*Math.pow(P1x,2)*Math.pow(V2x,2)*Math.pow(V1y,2)*Math.pow(V2z,2) - 4*Math.pow(P1x,2)*Math.pow(V2x,2)*Math.pow(V2y,2)*Math.pow(V1z,2) + 8*P1x*P2x*Math.pow(V2x,2)*Math.pow(V1y,2)*Math.pow(V2z,2) - 16*P1x*P2x*Math.pow(V2x,2)*V1y*V2y*V1z*V2z + 8*P1x*P2x*Math.pow(V2x,2)*Math.pow(V2y,2)*Math.pow(V1z,2) + 8*P1x*P1y*V1x*Math.pow(V2x,2)*V1y*Math.pow(V2z,2) - 8*P1x*P1y*V1x*Math.pow(V2x,2)*V2y*V1z*V2z - 8*P1x*P1y*Math.pow(V2x,3)*V1y*V1z*V2z + 8*P1x*P1y*Math.pow(V2x,3)*V2y*Math.pow(V1z,2) - 8*P1x*P2y*V1x*Math.pow(V2x,2)*V1y*Math.pow(V2z,2) + 8*P1x*P2y*V1x*Math.pow(V2x,2)*V2y*V1z*V2z + 8*P1x*P2y*Math.pow(V2x,3)*V1y*V1z*V2z - 8*P1x*P2y*Math.pow(V2x,3)*V2y*Math.pow(V1z,2) - 8*P1x*P1z*V1x*Math.pow(V2x,2)*V1y*V2y*V2z + 8*P1x*P1z*V1x*Math.pow(V2x,2)*Math.pow(V2y,2)*V1z + 8*P1x*P1z*Math.pow(V2x,3)*Math.pow(V1y,2)*V2z - 8*P1x*P1z*Math.pow(V2x,3)*V1y*V2y*V1z + 8*P1x*P2z*V1x*Math.pow(V2x,2)*V1y*V2y*V2z - 8*P1x*P2z*V1x*Math.pow(V2x,2)*Math.pow(V2y,2)*V1z - 8*P1x*P2z*Math.pow(V2x,3)*Math.pow(V1y,2)*V2z + 8*P1x*P2z*Math.pow(V2x,3)*V1y*V2y*V1z + 4*P1x*V1x*V1y*Math.pow(V2y,2)*V2z + 4*P1x*V1x*V1y*Math.pow(V2z,3) - 4*P1x*V1x*Math.pow(V2y,3)*V1z - 4*P1x*V1x*V2y*V1z*Math.pow(V2z,2) - 4*P1x*V2x*Math.pow(V1y,2)*V2y*V2z + 4*P1x*V2x*V1y*Math.pow(V2y,2)*V1z - 4*P1x*V2x*V1y*V1z*Math.pow(V2z,2) + 4*P1x*V2x*V2y*Math.pow(V1z,2)*V2z - 4*Math.pow(P2x,2)*Math.pow(V2x,2)*Math.pow(V1y,2)*Math.pow(V2z,2) + 8*Math.pow(P2x,2)*Math.pow(V2x,2)*V1y*V2y*V1z*V2z - 4*Math.pow(P2x,2)*Math.pow(V2x,2)*Math.pow(V2y,2)*Math.pow(V1z,2) - 8*P2x*P1y*V1x*Math.pow(V2x,2)*V1y*Math.pow(V2z,2) + 8*P2x*P1y*V1x*Math.pow(V2x,2)*V2y*V1z*V2z + 8*P2x*P1y*Math.pow(V2x,3)*V1y*V1z*V2z - 8*P2x*P1y*Math.pow(V2x,3)*V2y*Math.pow(V1z,2) + 8*P2x*P2y*V1x*Math.pow(V2x,2)*V1y*Math.pow(V2z,2) - 8*P2x*P2y*V1x*Math.pow(V2x,2)*V2y*V1z*V2z - 8*P2x*P2y*Math.pow(V2x,3)*V1y*V1z*V2z + 8*P2x*P2y*Math.pow(V2x,3)*V2y*Math.pow(V1z,2) + 8*P2x*P1z*V1x*Math.pow(V2x,2)*V1y*V2y*V2z - 8*P2x*P1z*V1x*Math.pow(V2x,2)*Math.pow(V2y,2)*V1z - 8*P2x*P1z*Math.pow(V2x,3)*Math.pow(V1y,2)*V2z + 8*P2x*P1z*Math.pow(V2x,3)*V1y*V2y*V1z - 8*P2x*P2z*V1x*Math.pow(V2x,2)*V1y*V2y*V2z + 8*P2x*P2z*V1x*Math.pow(V2x,2)*Math.pow(V2y,2)*V1z + 8*P2x*P2z*Math.pow(V2x,3)*Math.pow(V1y,2)*V2z - 8*P2x*P2z*Math.pow(V2x,3)*V1y*V2y*V1z - 4*P2x*V1x*V1y*Math.pow(V2y,2)*V2z - 4*P2x*V1x*V1y*Math.pow(V2z,3) + 4*P2x*V1x*Math.pow(V2y,3)*V1z + 4*P2x*V1x*V2y*V1z*Math.pow(V2z,2) + 4*P2x*V2x*Math.pow(V1y,2)*V2y*V2z - 4*P2x*V2x*V1y*Math.pow(V2y,2)*V1z + 4*P2x*V2x*V1y*V1z*Math.pow(V2z,2) - 4*P2x*V2x*V2y*Math.pow(V1z,2)*V2z - 4*Math.pow(P1y,2)*Math.pow(V1x,2)*Math.pow(V2x,2)*Math.pow(V2z,2) + 8*Math.pow(P1y,2)*V1x*Math.pow(V2x,3)*V1z*V2z - 4*Math.pow(P1y,2)*Math.pow(V2x,4)*Math.pow(V1z,2) + 8*P1y*P2y*Math.pow(V1x,2)*Math.pow(V2x,2)*Math.pow(V2z,2) - 16*P1y*P2y*V1x*Math.pow(V2x,3)*V1z*V2z + 8*P1y*P2y*Math.pow(V2x,4)*Math.pow(V1z,2) + 8*P1y*P1z*Math.pow(V1x,2)*Math.pow(V2x,2)*V2y*V2z - 8*P1y*P1z*V1x*Math.pow(V2x,3)*V1y*V2z - 8*P1y*P1z*V1x*Math.pow(V2x,3)*V2y*V1z + 8*P1y*P1z*Math.pow(V2x,4)*V1y*V1z - 8*P1y*P2z*Math.pow(V1x,2)*Math.pow(V2x,2)*V2y*V2z + 8*P1y*P2z*V1x*Math.pow(V2x,3)*V1y*V2z + 8*P1y*P2z*V1x*Math.pow(V2x,3)*V2y*V1z - 8*P1y*P2z*Math.pow(V2x,4)*V1y*V1z - 4*P1y*Math.pow(V1x,2)*Math.pow(V2y,2)*V2z - 4*P1y*Math.pow(V1x,2)*Math.pow(V2z,3) + 4*P1y*V1x*V2x*V1y*V2y*V2z + 4*P1y*V1x*V2x*Math.pow(V2y,2)*V1z + 8*P1y*V1x*V2x*V1z*Math.pow(V2z,2) - 4*P1y*Math.pow(V2x,2)*V1y*V2y*V1z - 4*P1y*Math.pow(V2x,2)*Math.pow(V1z,2)*V2z - 4*Math.pow(P2y,2)*Math.pow(V1x,2)*Math.pow(V2x,2)*Math.pow(V2z,2) + 8*Math.pow(P2y,2)*V1x*Math.pow(V2x,3)*V1z*V2z - 4*Math.pow(P2y,2)*Math.pow(V2x,4)*Math.pow(V1z,2) - 8*P2y*P1z*Math.pow(V1x,2)*Math.pow(V2x,2)*V2y*V2z + 8*P2y*P1z*V1x*Math.pow(V2x,3)*V1y*V2z + 8*P2y*P1z*V1x*Math.pow(V2x,3)*V2y*V1z - 8*P2y*P1z*Math.pow(V2x,4)*V1y*V1z + 8*P2y*P2z*Math.pow(V1x,2)*Math.pow(V2x,2)*V2y*V2z - 8*P2y*P2z*V1x*Math.pow(V2x,3)*V1y*V2z - 8*P2y*P2z*V1x*Math.pow(V2x,3)*V2y*V1z + 8*P2y*P2z*Math.pow(V2x,4)*V1y*V1z + 4*P2y*Math.pow(V1x,2)*Math.pow(V2y,2)*V2z + 4*P2y*Math.pow(V1x,2)*Math.pow(V2z,3) - 4*P2y*V1x*V2x*V1y*V2y*V2z - 4*P2y*V1x*V2x*Math.pow(V2y,2)*V1z - 8*P2y*V1x*V2x*V1z*Math.pow(V2z,2) + 4*P2y*Math.pow(V2x,2)*V1y*V2y*V1z + 4*P2y*Math.pow(V2x,2)*Math.pow(V1z,2)*V2z - 4*Math.pow(P1z,2)*Math.pow(V1x,2)*Math.pow(V2x,2)*Math.pow(V2y,2) + 8*Math.pow(P1z,2)*V1x*Math.pow(V2x,3)*V1y*V2y - 4*Math.pow(P1z,2)*Math.pow(V2x,4)*Math.pow(V1y,2) + 8*P1z*P2z*Math.pow(V1x,2)*Math.pow(V2x,2)*Math.pow(V2y,2) - 16*P1z*P2z*V1x*Math.pow(V2x,3)*V1y*V2y + 8*P1z*P2z*Math.pow(V2x,4)*Math.pow(V1y,2) + 4*P1z*Math.pow(V1x,2)*Math.pow(V2y,3) + 4*P1z*Math.pow(V1x,2)*V2y*Math.pow(V2z,2) - 8*P1z*V1x*V2x*V1y*Math.pow(V2y,2) - 4*P1z*V1x*V2x*V1y*Math.pow(V2z,2) - 4*P1z*V1x*V2x*V2y*V1z*V2z + 4*P1z*Math.pow(V2x,2)*Math.pow(V1y,2)*V2y + 4*P1z*Math.pow(V2x,2)*V1y*V1z*V2z - 4*Math.pow(P2z,2)*Math.pow(V1x,2)*Math.pow(V2x,2)*Math.pow(V2y,2) + 8*Math.pow(P2z,2)*V1x*Math.pow(V2x,3)*V1y*V2y - 4*Math.pow(P2z,2)*Math.pow(V2x,4)*Math.pow(V1y,2) - 4*P2z*Math.pow(V1x,2)*Math.pow(V2y,3) - 4*P2z*Math.pow(V1x,2)*V2y*Math.pow(V2z,2) + 8*P2z*V1x*V2x*V1y*Math.pow(V2y,2) + 4*P2z*V1x*V2x*V1y*Math.pow(V2z,2) + 4*P2z*V1x*V2x*V2y*V1z*V2z - 4*P2z*Math.pow(V2x,2)*Math.pow(V1y,2)*V2y - 4*P2z*Math.pow(V2x,2)*V1y*V1z*V2z + 4*Math.pow(V1x,2)*Math.pow(V2y,2)*Math.pow(r,2) + 4*Math.pow(V1x,2)*Math.pow(V2z,2)*Math.pow(r,2) - 8*V1x*V2x*V1y*V2y*Math.pow(r,2) - 8*V1x*V2x*V1z*V2z*Math.pow(r,2) + 4*Math.pow(V2x,2)*Math.pow(V1y,2)*Math.pow(r,2) + 4*Math.pow(V2x,2)*Math.pow(V1z,2)*Math.pow(r,2) + Math.pow(V1y,2)*Math.pow(V2z,2) - 2*V1y*V2y*V1z*V2z + Math.pow(V2y,2)*Math.pow(V1z,2)) - 2*P1x*V1x*Math.pow(V2y,2) + 2*P2x*V1x*Math.pow(V2y,2) - 2*P1x*V1x*Math.pow(V2z,2) - 2*P1y*Math.pow(V2x,2)*V1y + 2*P2x*V1x*Math.pow(V2z,2) + 2*P2y*Math.pow(V2x,2)*V1y - 2*P1z*Math.pow(V2x,2)*V1z + 2*P2z*Math.pow(V2x,2)*V1z + 2*P1x*V2x*V1y*V2y + 2*P1y*V1x*V2x*V2y - 2*P2x*V2x*V1y*V2y - 2*P2y*V1x*V2x*V2y + 2*P1x*V2x*V1z*V2z + 2*P1z*V1x*V2x*V2z - 2*P2x*V2x*V1z*V2z - 2*P2z*V1x*V2x*V2z)/(2*(Math.pow(V1x,2)*Math.pow(V2y,2) + Math.pow(V1x,2)*Math.pow(V2z,2) - 2*V1x*V2x*V1y*V2y - 2*V1x*V2x*V1z*V2z + Math.pow(V2x,2)*Math.pow(V1y,2) + Math.pow(V2x,2)*Math.pow(V1z,2)));
    return t;
}*/
