function calculateT(bx,by,bz,aircraft,m,dx,dy,dz,R){
    var t = bx*dx + by*dy + bz*dz - bx*m - by*m - bz*m - dx*aircraft.prevLon - dy*aircraft.prevLat - dz*aircraft.prevAlt + m*aircraft.prevLon 
	+ m*aircraft.prevLat + m*aircraft.prevAlt + Math.sqrt(Math.pow(R,2)*Math.pow(dx,2) - 2*Math.pow(R,2)*dx*m + Math.pow(R,2)*Math.pow(dy,2) 
        - 2*Math.pow(R,2)*dy*m + Math.pow(R,2)*Math.pow(dz,2) - 2*Math.pow(R,2)*dz*m + Math.pow(R,2)*Math.pow(m,2) + Math.pow(R,2)*Math.pow(m,2) 
        + Math.pow(R,2)*Math.pow(m,2) - Math.pow(bx,2)*Math.pow(dy,2) + 2*Math.pow(bx,2)*dy*m - Math.pow(bx,2)*Math.pow(dz,2) 
        + 2*Math.pow(bx,2)*dz*m - Math.pow(bx,2)*Math.pow(m,2) - Math.pow(bx,2)*Math.pow(m,2) + 2*bx*by*dx*dy - 2*bx*by*dx*m - 2*bx*by*dy*m 
        + 2*bx*by*m*m + 2*bx*bz*dx*dz - 2*bx*bz*dx*m - 2*bx*bz*dz*m + 2*bx*bz*m*m - 2*bx*dx*dy*aircraft.prevLat - 2*bx*dx*dz*aircraft.prevAlt 
        + 2*bx*dx*m*aircraft.prevLat + 2*bx*dx*m*aircraft.prevAlt + 2*bx*Math.pow(dy,2)*aircraft.prevLon + 2*bx*dy*m*aircraft.prevLat 
        - 4*bx*dy*m*aircraft.prevLon + 2*bx*Math.pow(dz,2)*aircraft.prevLon + 2*bx*dz*m*aircraft.prevAlt - 4*bx*dz*m*aircraft.prevLon 
        - 2*bx*m*m*aircraft.prevLat - 2*bx*m*m*aircraft.prevAlt + 2*bx*Math.pow(m,2)*aircraft.prevLon + 2*bx*Math.pow(m,2)*aircraft.prevLon 
        - Math.pow(by,2)*Math.pow(dx,2) + 2*Math.pow(by,2)*dx*m - Math.pow(by,2)*Math.pow(dz,2) + 2*Math.pow(by,2)*dz*m 
        - Math.pow(by,2)*Math.pow(m,2) - Math.pow(by,2)*Math.pow(m,2) + 2*by*bz*dy*dz - 2*by*bz*dy*m - 2*by*bz*dz*m + 2*by*bz*m*m 
        + 2*by*Math.pow(dx,2)*aircraft.prevLat - 2*by*dx*dy*aircraft.prevLon - 4*by*dx*m*aircraft.prevLat + 2*by*dx*m*aircraft.prevLon 
        - 2*by*dy*dz*aircraft.prevAlt + 2*by*dy*m*aircraft.prevLon + 2*by*dy*m*aircraft.prevAlt + 2*by*Math.pow(dz,2)*aircraft.prevLat 
        + 2*by*dz*m*aircraft.prevAlt - 4*by*dz*m*aircraft.prevLat + 2*by*Math.pow(m,2)*aircraft.prevLat - 2*by*m*m*aircraft.prevLon 
        - 2*by*m*m*aircraft.prevAlt + 2*by*Math.pow(m,2)*aircraft.prevLat - Math.pow(bz,2)*Math.pow(dx,2) + 2*Math.pow(bz,2)*dx*m 
        - Math.pow(bz,2)*Math.pow(dy,2) + 2*Math.pow(bz,2)*dy*m - Math.pow(bz,2)*Math.pow(m,2) - Math.pow(bz,2)*Math.pow(m,2) 
        + 2*bz*Math.pow(dx,2)*aircraft.prevAlt - 2*bz*dx*dz*aircraft.prevLon - 4*bz*dx*m*aircraft.prevAlt + 2*bz*dx*m*aircraft.prevLon 
        + 2*bz*Math.pow(dy,2)*aircraft.prevAlt - 2*bz*dy*dz*aircraft.prevLat - 4*bz*dy*m*aircraft.prevAlt + 2*bz*dy*m*aircraft.prevLat 
        + 2*bz*dz*m*aircraft.prevLon + 2*bz*dz*m*aircraft.prevLat + 2*bz*Math.pow(m,2)*aircraft.prevAlt - 2*bz*m*m*aircraft.prevLon 
        + 2*bz*Math.pow(m,2)*aircraft.prevAlt - 2*bz*m*m*aircraft.prevLat - Math.pow(dx,2)*Math.pow(aircraft.prevLat,2) 
        - Math.pow(dx,2)*Math.pow(aircraft.prevAlt,2) + 2*dx*dy*aircraft.prevLon*aircraft.prevLat + 2*dx*dz*aircraft.prevLon*aircraft.prevAlt 
        + 2*dx*m*Math.pow(aircraft.prevLat,2) + 2*dx*m*Math.pow(aircraft.prevAlt,2) - 2*dx*m*aircraft.prevLon*aircraft.prevLat 
        - 2*dx*m*aircraft.prevLon*aircraft.prevAlt - Math.pow(dy,2)*Math.pow(aircraft.prevLon,2) - Math.pow(dy,2)*Math.pow(aircraft.prevAlt,2) 
        + 2*dy*dz*aircraft.prevLat*aircraft.prevAlt - 2*dy*m*aircraft.prevLon*aircraft.prevLat + 2*dy*m*Math.pow(aircraft.prevLon,2) 
        + 2*dy*m*Math.pow(aircraft.prevAlt,2) - 2*dy*m*aircraft.prevLat*aircraft.prevAlt - Math.pow(dz,2)*Math.pow(aircraft.prevLon,2) 
        - Math.pow(dz,2)*Math.pow(aircraft.prevLat,2) - 2*dz*m*aircraft.prevLon*aircraft.prevAlt - 2*dz*m*aircraft.prevLat*aircraft.prevAlt 
        + 2*dz*m*Math.pow(aircraft.prevLon,2) + 2*dz*m*Math.pow(aircraft.prevLat,2) - Math.pow(m,2)*Math.pow(aircraft.prevLat,2) 
        - Math.pow(m,2)*Math.pow(aircraft.prevAlt,2) + 2*m*m*aircraft.prevLon*aircraft.prevLat + 2*m*m*aircraft.prevLon*aircraft.prevAlt 
        - Math.pow(m,2)*Math.pow(aircraft.prevLon,2) - Math.pow(m,2)*Math.pow(aircraft.prevAlt,2) + 2*m*m*aircraft.prevLat*aircraft.prevAlt 
        - Math.pow(m,2)*Math.pow(aircraft.prevLon,2) - Math.pow(m,2)*Math.pow(aircraft.prevLat,2))) / (Math.pow(dx,2) 
        - 2*dx*m + Math.pow(dy,2) - 2*dy*m + Math.pow(dz,2) - 2*dz*m + Math.pow(m,2) + Math.pow(m,2) + Math.pow(m,2);
													     
        return t;
}
