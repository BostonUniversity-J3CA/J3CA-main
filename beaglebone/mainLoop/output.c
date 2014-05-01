/*
 * Output.c
 *
 *  Created on: Apr 30, 2014
 *      Author: John, L, Gillespie, John R. Aleman, Joseph E. Stone, Chirag Rathod, Ari J. Morse
 *      College of Engineering, Boston University
 *      Notes: Converts PID output into PWM signals
 *      Copyright G.R.A.M.S., College of Engineering, Boston University
 *      jaleman@bu.edu, chiragr314@gmail.com, johngillespie27@yahoo.com, jestone@bu.edu, amorse@bu.edu
 *
 * 		Redistribution and use in source and binary forms, with or without modification,
 * 		are permitted provided that the following conditions are met:
 * 			1. Redistributions of source code must retain the above copyright
 *    			notice, this list of conditions and the following disclaimer.
 * 			2. Redistributions in binary form must reproduce the above copyright
 *    			notice, this list of conditions and the following disclaimer in the
 *    			documentation and/or other materials provided with the distribution.
 *
 * 		THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * 		INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * 		AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL I
 * 		BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * 		CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * 		GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * 		HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * 		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * 		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */




int setElevator(float elevator)
{
//Set pwm for the elevator
int output = (int)(1.5e6+.3e6*elevator/20); //convert float (-20 to 20) to int (1 to 2e6)
if (output > (int)1.8e6) {
return (int)1.8e6;
}
if (output < (int)1.2e6) {
return (int)1.2e6;
}
return output;
}

int setRudder(float rudder)
{
//Set pwm for the rudder
int output = (int)(2000000*(rudder+1)/(2)); //convert float (-1 to 1) to int (0 to 2e6)
}

int setAileron(float aileron)
{
//Set pwm for the aileron
int output = (int)(2000000*(aileron+1)/(2)); //convert float (-1 to 1) to int (0 to 2e6)
}

int setThrottle(float throttle)
{
//Set pwm for the throttle
int output = (int)(2000000*(throttle+1)/(2)); //convert float (-1 to 1) to int (0 to 2e6)
}
