#include "preprocessor_api.h"
#include "preprocessor.h"

/*
 * Pre-process data read from sensor modules
 * buffer: pointer to I2S stereo data
 * bufferSize: number of samples in buffer
 *
 * return: size of processed data in buffer
 */
uint16_t process(int16_t* buffer, uint16_t bufferSize)
{
    uint16_t numOutputBytes;

    filterNoise(buffer, bufferSize);

    numOutputBytes = downsample(buffer, bufferSize);

    return numOutputBytes;
}


/*
 * Filter noise by subtracting right channel from left channel
 * buffer: pointer to I2S stereo data
 * bufferSize: number of samples in buffer
 */
void filterNoise(int16_t* buffer, uint16_t bufferSize)
{
    uint16_t i;

    // Go through all samples and subtract right channel values from left channel values
    for(i=0; i<bufferSize; i+=2)
    {
        buffer[i] -= buffer[i+1];
    }
}


/*
 * Downsample by a factor of 10
 * buffer: pointer to I2S stereo data
 * bufferSize: number of samples in buffer
 *
 * return: size of processed data in buffer
 */
uint16_t downsample(int16_t* buffer, uint16_t bufferSize)
{
    // Run low-pass filter to avoid aliasing
    filter(buffer, bufferSize);

    return decimate(buffer, bufferSize);
}

/*
 * Decimate by keeping only every 10th sample
 * buffer: pointer to I2S stereo data
 * bufferSize: number of samples in buffer
 *
 * return: size of processed data in buffer
 */
uint16_t decimate(int16_t* buffer, uint16_t bufferSize)
{
    uint16_t i;
    uint16_t outBufferSize;

    outBufferSize = bufferSize / 10;

    for(i=0; i<outBufferSize; i++)
    {
        buffer[i] = buffer[i*10];
    }

    return outBufferSize;
}