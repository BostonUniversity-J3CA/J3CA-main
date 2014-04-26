int setElevator(float elevator)
{
//Set pwm for the elevator
int output = (int)(2000000*(elevator+1)/(2)); //convert float (-1 to 1) to int (0 to 2e6)
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
