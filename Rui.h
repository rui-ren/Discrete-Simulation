//Example Animal
//

#ifndef RUI_H
#define RUI_H

#include "Animal.h"

#include <string>
#include <list>
using namespace std;

class Rui:public Animal
{
		static Animal* create(const string& s); //used when the "factory" want to generate an object.
	
		//	class Initializer;
		static int Counter;//used only for the first time to contruct the object.
	   //this will force the method "create" to be registered in the Failure List
	public:
		Rui();
		~Rui();
		void Update(const list<Animal*>& a);
};

#endif
