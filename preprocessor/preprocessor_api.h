
/*
 * Pre-process data read from sensor modules
 * buffer: pointer to I2S stereo data
 * bufferSize: number of samples in buffer
 *
 * return: size of processed data in buffer
 */
uint16_t process(int16_t* buffer, uint16_t bufferSize);