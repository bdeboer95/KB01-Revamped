#ifndef __DEVICE_H__
#define __DEVICE_H__

class Device
{
public:
	virtual ~Device(){};

	virtual bool InitDevice()	 = 0;
	virtual bool AcquireDevice() = 0;
	virtual void ReleaseDevice() = 0;

};

#endif