#ifndef __MANAGER_H__
#define __MANAGER_H__

class Manager
{
public:
	Manager() {}
	~Manager() {}

	virtual void Step() = 0;
	virtual bool Running() = 0;
};

#endif