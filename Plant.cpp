#include"Plant.h"
#include"Sim.h"
#include<math.h>
#include<iostream>
using namespace std;


int Plant::Counter = 0; 
//initialize to 0 so that it can be created.

Plant plant;
//this will force the Initializer to add this class to the factory. 
//later on the factor can be used to generate objects dynamically..

Animal* Plant::create(const string& s) //used when the "factory" want to generate an object.
{
	if (s == "Plant")
	{
		cout << "Creating Plant " << endl;
		return new Plant;	//will this lead to memory leaking? 
	}
	else
		return 0;//hmmm, Not this one.. return nothing
};

Plant::Plant()
{
	cout << "Adding Plant Method into the factory" << endl;
	Animal::name = "Plant";
	Animal::m = Max_Mass;
	Animal::E = Max_Energy;
	if (Counter == 0)
	{
		Animal::AddCreator(Plant::create); //only add once.
		Animal::Animal_list.push_back("Plant"); //add the name into the list
		Counter = 1; //flag
	}
};



Plant::~Plant()
{
	cout << "Removing Plant Method" << endl;
}

void Plant::Update(const list<Animal*>& a)
{
	double M;
	double e;
	M = this->GetMass();
	e = this->GetEnergy();
	// grow by 0.05% each step
	this->SetMass(1.0005 * M);
	this->SetEnergy(1.0005 * e);
	double Vx = 0;
	double Vy = 0;
	vector<double> u;
	u.push_back(Vx);
	u.push_back(Vy);
	SetVelocity(u);
}
