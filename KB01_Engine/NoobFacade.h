#ifndef __NOOBFACADE_H__
#define __NOOBFACADE_H__
#include  <string>
class NoobFacade
{
public:
					NoobFacade();					//Constructor
					~NoobFacade();					//Destructor
	void			LoadLevel(std::string fileName);//Load the level using a level file
};

#endif
