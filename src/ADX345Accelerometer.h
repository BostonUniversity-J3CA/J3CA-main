

#ifndef ADX345ACCELEROMETER_H_
#define ADX345ACCELEROMETER_H_
#define ADX345_I2C_BUFFER 0xFF

class ADX345Accelerometer {

private:
	int I2CBus, I2CAddress;
	char dataBuffer[ADX345_I2C_BUFFER];

	int accelerationX;
	int accelerationY;
	int accelerationZ;

	uint8_t time_ff;
	uint8_t data_format;
	uint8_t power_ctl;
	uint8_t bw_rate;
	uint8_t mode_config;


	uint8_t bandwidth;
	uint8_t modeConfig;

	int  convertAcceleration(int msb_addr, int lsb_addr);
	int  writeI2CDeviceByte(char address, char value);

public:
	ADX345Accelerometer(int bus, int address);
	void displayMode(int iterations);

	int  readFullSensorState();
	// The following do physical reads and writes of the sensors
	int setTIME_FF(uint8_t desired);
	uint8_t getTIME_FF();
	int setDATA_FORMAT(uint8_t desired);
	uint8_t getDATA_FORMAT();
	int setPOWER_CTL(uint8_t desired);
	uint8_t getPOWER_CTL();
	int setBW_RATE(uint8_t desired);
    uint8_t getBW_RATE();

	int getAccelerationX() { return accelerationX; }
	int getAccelerationY() { return accelerationY; }
	int getAccelerationZ() { return accelerationZ; }

	virtual ~ADX345Accelerometer();
};

#endif /* ADX345ACCELEROMETER_H_ */
