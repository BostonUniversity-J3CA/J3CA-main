﻿function calculateT(aircraft,obstacle){
   var pos1 = aircraft.getPosition();
   var vel1 = aircraft.getVelocity();
   var pos2 = obstacle.getPosition();
   var vel2 = obstacle.getVelocity();

   // Set up the variables                                                                                                                           
   var r    = aircraft.getRadius()+obstacle.getRadius();
   var v1_x = vel1.x;
   var v1_y = vel1.y;
   var v1_z = vel1.z;
   var vx   = vel2.x;
   var vy   = vel2.y;
   var vz   = vel2.z;
   var x2   = pos2.x;
   var y2   = pos2.y;
   var z2   = pos2.z;
   var x_0  = pos1.x;
   var y_0  = pos1.y;
   var z_0  = pos1.z;


    var t = (Math.sqrt(Math.pow(r,2)*Math.pow(v1_x,2)*Math.pow(vy,2) + Math.pow(r,2)*Math.pow(v1_x,2)*Math.pow(vz,2) - 2*Math.pow(r,2)*v1_x*v1_y*vx*vy - 2*Math.pow(r,2)*v1_x*v1_z*vx*vz + Math.pow(r,2)*Math.pow(v1_y,2)*Math.pow(vx,2) + Math.pow(r,2)*Math.pow(v1_y,2)*Math.pow(vz,2) - 2*Math.pow(r,2)*v1_y*v1_z*vy*vz + Math.pow(r,2)*Math.pow(v1_z,2)*Math.pow(vx,2) + Math.pow(r,2)*Math.pow(v1_z,2)*Math.pow(vy,2) - Math.pow(v1_x,2)*Math.pow(vx,2)*Math.pow(vy,2)*Math.pow(z2,2) + 2*Math.pow(v1_x,2)*Math.pow(vx,2)*Math.pow(vy,2)*z2*z_0 - Math.pow(v1_x,2)*Math.pow(vx,2)*Math.pow(vy,2)*Math.pow(z_0,2) + 2*Math.pow(v1_x,2)*Math.pow(vx,2)*vy*vz*y2*z2 - 2*Math.pow(v1_x,2)*Math.pow(vx,2)*vy*vz*y2*z_0 - 2*Math.pow(v1_x,2)*Math.pow(vx,2)*vy*vz*y_0*z2 + 2*Math.pow(v1_x,2)*Math.pow(vx,2)*vy*vz*y_0*z_0 - Math.pow(v1_x,2)*Math.pow(vx,2)*Math.pow(vz,2)*Math.pow(y2,2) + 2*Math.pow(v1_x,2)*Math.pow(vx,2)*Math.pow(vz,2)*y2*y_0 - Math.pow(v1_x,2)*Math.pow(vx,2)*Math.pow(vz,2)*Math.pow(y_0,2) - Math.pow(v1_x,2)*Math.pow(vy,4)*Math.pow(z2,2) + 2*Math.pow(v1_x,2)*Math.pow(vy,4)*z2*z_0 - Math.pow(v1_x,2)*Math.pow(vy,4)*Math.pow(z_0,2) + 2*Math.pow(v1_x,2)*Math.pow(vy,3)*vz*y2*z2 - 2*Math.pow(v1_x,2)*Math.pow(vy,3)*vz*y2*z_0 - 2*Math.pow(v1_x,2)*Math.pow(vy,3)*vz*y_0*z2 + 2*Math.pow(v1_x,2)*Math.pow(vy,3)*vz*y_0*z_0 - Math.pow(v1_x,2)*Math.pow(vy,2)*Math.pow(vz,2)*Math.pow(y2,2) + 2*Math.pow(v1_x,2)*Math.pow(vy,2)*Math.pow(vz,2)*y2*y_0 - Math.pow(v1_x,2)*Math.pow(vy,2)*Math.pow(vz,2)*Math.pow(y_0,2) - Math.pow(v1_x,2)*Math.pow(vy,2)*Math.pow(vz,2)*Math.pow(z2,2) + 2*Math.pow(v1_x,2)*Math.pow(vy,2)*Math.pow(vz,2)*z2*z_0 - Math.pow(v1_x,2)*Math.pow(vy,2)*Math.pow(vz,2)*Math.pow(z_0,2) + 2*Math.pow(v1_x,2)*vy*Math.pow(vz,3)*y2*z2 - 2*Math.pow(v1_x,2)*vy*Math.pow(vz,3)*y2*z_0 - 2*Math.pow(v1_x,2)*vy*Math.pow(vz,3)*y_0*z2 + 2*Math.pow(v1_x,2)*vy*Math.pow(vz,3)*y_0*z_0 - Math.pow(v1_x,2)*Math.pow(vz,4)*Math.pow(y2,2) + 2*Math.pow(v1_x,2)*Math.pow(vz,4)*y2*y_0 - Math.pow(v1_x,2)*Math.pow(vz,4)*Math.pow(y_0,2) + 2*v1_x*v1_y*Math.pow(vx,3)*vy*Math.pow(z2,2) - 4*v1_x*v1_y*Math.pow(vx,3)*vy*z2*z_0 + 2*v1_x*v1_y*Math.pow(vx,3)*vy*Math.pow(z_0,2) - 2*v1_x*v1_y*Math.pow(vx,3)*vz*y2*z2 + 2*v1_x*v1_y*Math.pow(vx,3)*vz*y2*z_0 + 2*v1_x*v1_y*Math.pow(vx,3)*vz*y_0*z2 - 2*v1_x*v1_y*Math.pow(vx,3)*vz*y_0*z_0 - 2*v1_x*v1_y*Math.pow(vx,2)*vy*vz*x2*z2 + 2*v1_x*v1_y*Math.pow(vx,2)*vy*vz*x2*z_0 + 2*v1_x*v1_y*Math.pow(vx,2)*vy*vz*x_0*z2 - 2*v1_x*v1_y*Math.pow(vx,2)*vy*vz*x_0*z_0 + 2*v1_x*v1_y*Math.pow(vx,2)*Math.pow(vz,2)*x2*y2 - 2*v1_x*v1_y*Math.pow(vx,2)*Math.pow(vz,2)*x2*y_0 - 2*v1_x*v1_y*Math.pow(vx,2)*Math.pow(vz,2)*x_0*y2 + 2*v1_x*v1_y*Math.pow(vx,2)*Math.pow(vz,2)*x_0*y_0 + 2*v1_x*v1_y*vx*Math.pow(vy,3)*Math.pow(z2,2) - 4*v1_x*v1_y*vx*Math.pow(vy,3)*z2*z_0 + 2*v1_x*v1_y*vx*Math.pow(vy,3)*Math.pow(z_0,2) - 2*v1_x*v1_y*vx*Math.pow(vy,2)*vz*y2*z2 + 2*v1_x*v1_y*vx*Math.pow(vy,2)*vz*y2*z_0 + 2*v1_x*v1_y*vx*Math.pow(vy,2)*vz*y_0*z2 - 2*v1_x*v1_y*vx*Math.pow(vy,2)*vz*y_0*z_0 + 2*v1_x*v1_y*vx*vy*Math.pow(vz,2)*Math.pow(z2,2) - 4*v1_x*v1_y*vx*vy*Math.pow(vz,2)*z2*z_0 + 2*v1_x*v1_y*vx*vy*Math.pow(vz,2)*Math.pow(z_0,2) - 2*v1_x*v1_y*vx*Math.pow(vz,3)*y2*z2 + 2*v1_x*v1_y*vx*Math.pow(vz,3)*y2*z_0 + 2*v1_x*v1_y*vx*Math.pow(vz,3)*y_0*z2 - 2*v1_x*v1_y*vx*Math.pow(vz,3)*y_0*z_0 - 2*v1_x*v1_y*Math.pow(vy,3)*vz*x2*z2 + 2*v1_x*v1_y*Math.pow(vy,3)*vz*x2*z_0 + 2*v1_x*v1_y*Math.pow(vy,3)*vz*x_0*z2 - 2*v1_x*v1_y*Math.pow(vy,3)*vz*x_0*z_0 + 2*v1_x*v1_y*Math.pow(vy,2)*Math.pow(vz,2)*x2*y2 - 2*v1_x*v1_y*Math.pow(vy,2)*Math.pow(vz,2)*x2*y_0 - 2*v1_x*v1_y*Math.pow(vy,2)*Math.pow(vz,2)*x_0*y2 + 2*v1_x*v1_y*Math.pow(vy,2)*Math.pow(vz,2)*x_0*y_0 - 2*v1_x*v1_y*vy*Math.pow(vz,3)*x2*z2 + 2*v1_x*v1_y*vy*Math.pow(vz,3)*x2*z_0 + 2*v1_x*v1_y*vy*Math.pow(vz,3)*x_0*z2 - 2*v1_x*v1_y*vy*Math.pow(vz,3)*x_0*z_0 + 2*v1_x*v1_y*Math.pow(vz,4)*x2*y2 - 2*v1_x*v1_y*Math.pow(vz,4)*x2*y_0 - 2*v1_x*v1_y*Math.pow(vz,4)*x_0*y2 + 2*v1_x*v1_y*Math.pow(vz,4)*x_0*y_0 - 2*v1_x*v1_z*Math.pow(vx,3)*vy*y2*z2 + 2*v1_x*v1_z*Math.pow(vx,3)*vy*y2*z_0 + 2*v1_x*v1_z*Math.pow(vx,3)*vy*y_0*z2 - 2*v1_x*v1_z*Math.pow(vx,3)*vy*y_0*z_0 + 2*v1_x*v1_z*Math.pow(vx,3)*vz*Math.pow(y2,2) - 4*v1_x*v1_z*Math.pow(vx,3)*vz*y2*y_0 + 2*v1_x*v1_z*Math.pow(vx,3)*vz*Math.pow(y_0,2) + 2*v1_x*v1_z*Math.pow(vx,2)*Math.pow(vy,2)*x2*z2 - 2*v1_x*v1_z*Math.pow(vx,2)*Math.pow(vy,2)*x2*z_0 - 2*v1_x*v1_z*Math.pow(vx,2)*Math.pow(vy,2)*x_0*z2 + 2*v1_x*v1_z*Math.pow(vx,2)*Math.pow(vy,2)*x_0*z_0 - 2*v1_x*v1_z*Math.pow(vx,2)*vy*vz*x2*y2 + 2*v1_x*v1_z*Math.pow(vx,2)*vy*vz*x2*y_0 + 2*v1_x*v1_z*Math.pow(vx,2)*vy*vz*x_0*y2 - 2*v1_x*v1_z*Math.pow(vx,2)*vy*vz*x_0*y_0 - 2*v1_x*v1_z*vx*Math.pow(vy,3)*y2*z2 + 2*v1_x*v1_z*vx*Math.pow(vy,3)*y2*z_0 + 2*v1_x*v1_z*vx*Math.pow(vy,3)*y_0*z2 - 2*v1_x*v1_z*vx*Math.pow(vy,3)*y_0*z_0 + 2*v1_x*v1_z*vx*Math.pow(vy,2)*vz*Math.pow(y2,2) - 4*v1_x*v1_z*vx*Math.pow(vy,2)*vz*y2*y_0 + 2*v1_x*v1_z*vx*Math.pow(vy,2)*vz*Math.pow(y_0,2) - 2*v1_x*v1_z*vx*vy*Math.pow(vz,2)*y2*z2 + 2*v1_x*v1_z*vx*vy*Math.pow(vz,2)*y2*z_0 + 2*v1_x*v1_z*vx*vy*Math.pow(vz,2)*y_0*z2 - 2*v1_x*v1_z*vx*vy*Math.pow(vz,2)*y_0*z_0 + 2*v1_x*v1_z*vx*Math.pow(vz,3)*Math.pow(y2,2) - 4*v1_x*v1_z*vx*Math.pow(vz,3)*y2*y_0 + 2*v1_x*v1_z*vx*Math.pow(vz,3)*Math.pow(y_0,2) + 2*v1_x*v1_z*Math.pow(vy,4)*x2*z2 - 2*v1_x*v1_z*Math.pow(vy,4)*x2*z_0 - 2*v1_x*v1_z*Math.pow(vy,4)*x_0*z2 + 2*v1_x*v1_z*Math.pow(vy,4)*x_0*z_0 - 2*v1_x*v1_z*Math.pow(vy,3)*vz*x2*y2 + 2*v1_x*v1_z*Math.pow(vy,3)*vz*x2*y_0 + 2*v1_x*v1_z*Math.pow(vy,3)*vz*x_0*y2 - 2*v1_x*v1_z*Math.pow(vy,3)*vz*x_0*y_0 + 2*v1_x*v1_z*Math.pow(vy,2)*Math.pow(vz,2)*x2*z2 - 2*v1_x*v1_z*Math.pow(vy,2)*Math.pow(vz,2)*x2*z_0 - 2*v1_x*v1_z*Math.pow(vy,2)*Math.pow(vz,2)*x_0*z2 + 2*v1_x*v1_z*Math.pow(vy,2)*Math.pow(vz,2)*x_0*z_0 - 2*v1_x*v1_z*vy*Math.pow(vz,3)*x2*y2 + 2*v1_x*v1_z*vy*Math.pow(vz,3)*x2*y_0 + 2*v1_x*v1_z*vy*Math.pow(vz,3)*x_0*y2 - 2*v1_x*v1_z*vy*Math.pow(vz,3)*x_0*y_0 - Math.pow(v1_y,2)*Math.pow(vx,4)*Math.pow(z2,2) + 2*Math.pow(v1_y,2)*Math.pow(vx,4)*z2*z_0 - Math.pow(v1_y,2)*Math.pow(vx,4)*Math.pow(z_0,2) + 2*Math.pow(v1_y,2)*Math.pow(vx,3)*vz*x2*z2 - 2*Math.pow(v1_y,2)*Math.pow(vx,3)*vz*x2*z_0 - 2*Math.pow(v1_y,2)*Math.pow(vx,3)*vz*x_0*z2 + 2*Math.pow(v1_y,2)*Math.pow(vx,3)*vz*x_0*z_0 - Math.pow(v1_y,2)*Math.pow(vx,2)*Math.pow(vy,2)*Math.pow(z2,2) + 2*Math.pow(v1_y,2)*Math.pow(vx,2)*Math.pow(vy,2)*z2*z_0 - Math.pow(v1_y,2)*Math.pow(vx,2)*Math.pow(vy,2)*Math.pow(z_0,2) - Math.pow(v1_y,2)*Math.pow(vx,2)*Math.pow(vz,2)*Math.pow(x2,2) + 2*Math.pow(v1_y,2)*Math.pow(vx,2)*Math.pow(vz,2)*x2*x_0 - Math.pow(v1_y,2)*Math.pow(vx,2)*Math.pow(vz,2)*Math.pow(x_0,2) - Math.pow(v1_y,2)*Math.pow(vx,2)*Math.pow(vz,2)*Math.pow(z2,2) + 2*Math.pow(v1_y,2)*Math.pow(vx,2)*Math.pow(vz,2)*z2*z_0 - Math.pow(v1_y,2)*Math.pow(vx,2)*Math.pow(vz,2)*Math.pow(z_0,2) + 2*Math.pow(v1_y,2)*vx*Math.pow(vy,2)*vz*x2*z2 - 2*Math.pow(v1_y,2)*vx*Math.pow(vy,2)*vz*x2*z_0 - 2*Math.pow(v1_y,2)*vx*Math.pow(vy,2)*vz*x_0*z2 + 2*Math.pow(v1_y,2)*vx*Math.pow(vy,2)*vz*x_0*z_0 + 2*Math.pow(v1_y,2)*vx*Math.pow(vz,3)*x2*z2 - 2*Math.pow(v1_y,2)*vx*Math.pow(vz,3)*x2*z_0 - 2*Math.pow(v1_y,2)*vx*Math.pow(vz,3)*x_0*z2 + 2*Math.pow(v1_y,2)*vx*Math.pow(vz,3)*x_0*z_0 - Math.pow(v1_y,2)*Math.pow(vy,2)*Math.pow(vz,2)*Math.pow(x2,2) + 2*Math.pow(v1_y,2)*Math.pow(vy,2)*Math.pow(vz,2)*x2*x_0 - Math.pow(v1_y,2)*Math.pow(vy,2)*Math.pow(vz,2)*Math.pow(x_0,2) - Math.pow(v1_y,2)*Math.pow(vz,4)*Math.pow(x2,2) + 2*Math.pow(v1_y,2)*Math.pow(vz,4)*x2*x_0 - Math.pow(v1_y,2)*Math.pow(vz,4)*Math.pow(x_0,2) + 2*v1_y*v1_z*Math.pow(vx,4)*y2*z2 - 2*v1_y*v1_z*Math.pow(vx,4)*y2*z_0 - 2*v1_y*v1_z*Math.pow(vx,4)*y_0*z2 + 2*v1_y*v1_z*Math.pow(vx,4)*y_0*z_0 - 2*v1_y*v1_z*Math.pow(vx,3)*vy*x2*z2 + 2*v1_y*v1_z*Math.pow(vx,3)*vy*x2*z_0 + 2*v1_y*v1_z*Math.pow(vx,3)*vy*x_0*z2 - 2*v1_y*v1_z*Math.pow(vx,3)*vy*x_0*z_0 - 2*v1_y*v1_z*Math.pow(vx,3)*vz*x2*y2 + 2*v1_y*v1_z*Math.pow(vx,3)*vz*x2*y_0 + 2*v1_y*v1_z*Math.pow(vx,3)*vz*x_0*y2 - 2*v1_y*v1_z*Math.pow(vx,3)*vz*x_0*y_0 + 2*v1_y*v1_z*Math.pow(vx,2)*Math.pow(vy,2)*y2*z2 - 2*v1_y*v1_z*Math.pow(vx,2)*Math.pow(vy,2)*y2*z_0 - 2*v1_y*v1_z*Math.pow(vx,2)*Math.pow(vy,2)*y_0*z2 + 2*v1_y*v1_z*Math.pow(vx,2)*Math.pow(vy,2)*y_0*z_0 + 2*v1_y*v1_z*Math.pow(vx,2)*vy*vz*Math.pow(x2,2) - 4*v1_y*v1_z*Math.pow(vx,2)*vy*vz*x2*x_0 + 2*v1_y*v1_z*Math.pow(vx,2)*vy*vz*Math.pow(x_0,2) + 2*v1_y*v1_z*Math.pow(vx,2)*Math.pow(vz,2)*y2*z2 - 2*v1_y*v1_z*Math.pow(vx,2)*Math.pow(vz,2)*y2*z_0 - 2*v1_y*v1_z*Math.pow(vx,2)*Math.pow(vz,2)*y_0*z2 + 2*v1_y*v1_z*Math.pow(vx,2)*Math.pow(vz,2)*y_0*z_0 - 2*v1_y*v1_z*vx*Math.pow(vy,3)*x2*z2 + 2*v1_y*v1_z*vx*Math.pow(vy,3)*x2*z_0 + 2*v1_y*v1_z*vx*Math.pow(vy,3)*x_0*z2 - 2*v1_y*v1_z*vx*Math.pow(vy,3)*x_0*z_0 - 2*v1_y*v1_z*vx*Math.pow(vy,2)*vz*x2*y2 + 2*v1_y*v1_z*vx*Math.pow(vy,2)*vz*x2*y_0 + 2*v1_y*v1_z*vx*Math.pow(vy,2)*vz*x_0*y2 - 2*v1_y*v1_z*vx*Math.pow(vy,2)*vz*x_0*y_0 - 2*v1_y*v1_z*vx*vy*Math.pow(vz,2)*x2*z2 + 2*v1_y*v1_z*vx*vy*Math.pow(vz,2)*x2*z_0 + 2*v1_y*v1_z*vx*vy*Math.pow(vz,2)*x_0*z2 - 2*v1_y*v1_z*vx*vy*Math.pow(vz,2)*x_0*z_0 - 2*v1_y*v1_z*vx*Math.pow(vz,3)*x2*y2 + 2*v1_y*v1_z*vx*Math.pow(vz,3)*x2*y_0 + 2*v1_y*v1_z*vx*Math.pow(vz,3)*x_0*y2 - 2*v1_y*v1_z*vx*Math.pow(vz,3)*x_0*y_0 + 2*v1_y*v1_z*Math.pow(vy,3)*vz*Math.pow(x2,2) - 4*v1_y*v1_z*Math.pow(vy,3)*vz*x2*x_0 + 2*v1_y*v1_z*Math.pow(vy,3)*vz*Math.pow(x_0,2) + 2*v1_y*v1_z*vy*Math.pow(vz,3)*Math.pow(x2,2) - 4*v1_y*v1_z*vy*Math.pow(vz,3)*x2*x_0 + 2*v1_y*v1_z*vy*Math.pow(vz,3)*Math.pow(x_0,2) - Math.pow(v1_z,2)*Math.pow(vx,4)*Math.pow(y2,2) + 2*Math.pow(v1_z,2)*Math.pow(vx,4)*y2*y_0 - Math.pow(v1_z,2)*Math.pow(vx,4)*Math.pow(y_0,2) + 2*Math.pow(v1_z,2)*Math.pow(vx,3)*vy*x2*y2 - 2*Math.pow(v1_z,2)*Math.pow(vx,3)*vy*x2*y_0 - 2*Math.pow(v1_z,2)*Math.pow(vx,3)*vy*x_0*y2 + 2*Math.pow(v1_z,2)*Math.pow(vx,3)*vy*x_0*y_0 - Math.pow(v1_z,2)*Math.pow(vx,2)*Math.pow(vy,2)*Math.pow(x2,2) + 2*Math.pow(v1_z,2)*Math.pow(vx,2)*Math.pow(vy,2)*x2*x_0 - Math.pow(v1_z,2)*Math.pow(vx,2)*Math.pow(vy,2)*Math.pow(x_0,2) - Math.pow(v1_z,2)*Math.pow(vx,2)*Math.pow(vy,2)*Math.pow(y2,2) + 2*Math.pow(v1_z,2)*Math.pow(vx,2)*Math.pow(vy,2)*y2*y_0 - Math.pow(v1_z,2)*Math.pow(vx,2)*Math.pow(vy,2)*Math.pow(y_0,2) - Math.pow(v1_z,2)*Math.pow(vx,2)*Math.pow(vz,2)*Math.pow(y2,2) + 2*Math.pow(v1_z,2)*Math.pow(vx,2)*Math.pow(vz,2)*y2*y_0 - Math.pow(v1_z,2)*Math.pow(vx,2)*Math.pow(vz,2)*Math.pow(y_0,2) + 2*Math.pow(v1_z,2)*vx*Math.pow(vy,3)*x2*y2 - 2*Math.pow(v1_z,2)*vx*Math.pow(vy,3)*x2*y_0 - 2*Math.pow(v1_z,2)*vx*Math.pow(vy,3)*x_0*y2 + 2*Math.pow(v1_z,2)*vx*Math.pow(vy,3)*x_0*y_0 + 2*Math.pow(v1_z,2)*vx*vy*Math.pow(vz,2)*x2*y2 - 2*Math.pow(v1_z,2)*vx*vy*Math.pow(vz,2)*x2*y_0 - 2*Math.pow(v1_z,2)*vx*vy*Math.pow(vz,2)*x_0*y2 + 2*Math.pow(v1_z,2)*vx*vy*Math.pow(vz,2)*x_0*y_0 - Math.pow(v1_z,2)*Math.pow(vy,4)*Math.pow(x2,2) + 2*Math.pow(v1_z,2)*Math.pow(vy,4)*x2*x_0 - Math.pow(v1_z,2)*Math.pow(vy,4)*Math.pow(x_0,2) - Math.pow(v1_z,2)*Math.pow(vy,2)*Math.pow(vz,2)*Math.pow(x2,2) + 2*Math.pow(v1_z,2)*Math.pow(vy,2)*Math.pow(vz,2)*x2*x_0 - Math.pow(v1_z,2)*Math.pow(vy,2)*Math.pow(vz,2)*Math.pow(x_0,2)) + v1_x*Math.pow(vy,2)*x2 + v1_x*Math.pow(vz,2)*x2 - v1_x*Math.pow(vy,2)*x_0 - v1_x*Math.pow(vz,2)*x_0 + v1_y*Math.pow(vx,2)*y2 + v1_y*Math.pow(vz,2)*y2 - v1_y*Math.pow(vx,2)*y_0 - v1_y*Math.pow(vz,2)*y_0 + v1_z*Math.pow(vx,2)*z2 + v1_z*Math.pow(vy,2)*z2 - v1_z*Math.pow(vx,2)*z_0 - v1_z*Math.pow(vy,2)*z_0 - v1_y*vx*vy*x2 - v1_z*vx*vz*x2 + v1_y*vx*vy*x_0 + v1_z*vx*vz*x_0 - v1_x*vx*vy*y2 - v1_z*vy*vz*y2 + v1_x*vx*vy*y_0 + v1_z*vy*vz*y_0 - v1_x*vx*vz*z2 - v1_y*vy*vz*z2 + v1_x*vx*vz*z_0 + v1_y*vy*vz*z_0)/(Math.pow(v1_x,2)*Math.pow(vy,2) + Math.pow(v1_x,2)*Math.pow(vz,2) - 2*v1_x*v1_y*vx*vy - 2*v1_x*v1_z*vx*vz + Math.pow(v1_y,2)*Math.pow(vx,2) + Math.pow(v1_y,2)*Math.pow(vz,2) - 2*v1_y*v1_z*vy*vz + Math.pow(v1_z,2)*Math.pow(vx,2) + Math.pow(v1_z,2)*Math.pow(vy,2));
    return t;
}
