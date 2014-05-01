/*
 * Constants.h
 *
 *  Created on: Apr 30, 2014
 *      Author: John, L. Gillespie, John R. Aleman, Joseph E. Stone, Chirag Rathod, Ari J. Morse
 *      College of Engineering, Boston University
 *      Notes: Contains the PID gains for ease of tunning
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

//throttle
#define kthrottle -10000
//elevator
#define kpitch (40*3.141592653/180)
#define kdpitch (.573*3.141592653/180)
#define kheight 0
#define kheightchange 0
#define pitch0 3
#define ipitch 0
#define iheight 0
//rudder
#define ky 0
#define kyaw 0
//ailerons
#define kroll 0
