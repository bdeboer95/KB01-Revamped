#ifndef __KERNELINTERFACE_H__
#define __KERNELINTERFACE_H__

class KernelInterface
{
public:
	KernelInterface() {}
	~KernelInterface() {}

	virtual void Init() = 0;
	virtual void Step() = 0;
	virtual bool Running() = 0;
	virtual void Reset() = 0;
};

#endif
