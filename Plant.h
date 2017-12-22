//Example Animal
//

#ifndef PLANT_H
#define PLANT_H

#include "Animal.h"
#include "Sim.h"
#include <string>
#include <list>
using namespace std;

class Plant: public Animal
{
	static Animal* create(const string& s); //used when the "factory" want to generate an object.
	//	class Initializer;
	static int Counter;//used only for the first time to contruct the object.
	//this will force the method "create" to be registered in the Failure List
public:
	Plant();
	~Plant();
	void Update(const list<Animal*>& a);
};

#endif

