//Rui.cpp

#include "Rui.h"
#include "Sim.h"
#include <math.h>



int Rui::Counter = 0; //initialize to 0 so that it can be created.
Rui aa;//this will force the Initializer to add this class to the factory. 
			//later on the factor can be used to generate objects dynamically..


Animal* Rui::create(const string& s) //used when the "factory" want to generate an object.
{
	if(s=="Rui")
	  {
		cout<<"Creating Rui "<<endl;
		return new Rui; //will this lead to memory leaking?   Yes!!!
	  }
	else
		return 0;//hmmm, Not this one.. return nothing
};

Rui::Rui()
{
  cout<<"Adding Rui Method into the factory"<<endl;
  Animal::name = "Rui";
  Animal::m = Max_Mass;
  Animal::E = Max_Energy;
  if(Counter== 0)
	{
		Rui::AddCreator(create); //only add once.
		Animal::Animal_list.push_back("Rui"); //add the name into the list
		Counter=1; //flag
	}
};

Rui::~Rui()
{
	//cout<<"Removing Rui Method"<<endl;
}

void Rui::Update(const list<Animal*>& a)

// strategy:  1.Avoid the strong enemy and Eat easy meat
// strategy:  2.Stand still when everything is OK.

{
      //cout<<"Find neighbors within radius r (=100/2)"<<endl;
	list<Animal*> neighbors = Perceive(a, Perceive_Distance/2);
	cout<<"Neighbors: "<< neighbors.size() << endl;
	//do my computation
	list<Animal*> Target;  //first one in the list as the target.
	list<Animal*> Enemy;  // the most dangerous one in my neighbors.
	list<Animal*> Plant;
	
  	for (list<Animal*>::const_iterator i = a.begin(); i != a.end(); i++)
	{
		// figure out the easy meat in my neighbors list!
		if ((*i)->GetName() != "Rui" && ((*i)->GetEnergy() < this->GetEnergy()))    // this-> energy????   &&  energy less than myself
		{	
			for (list<Animal*>::iterator j = neighbors.begin(); j != neighbors.end(); j++)     // check in neighbor
			{
				if (*i == *j  && (- 0.2 * this->GetEnergy() + 0.8 * (*i)->GetEnergy())> 10 )      // animal belong to neighbors &&  get the benefit > 5
				Target.push_back(*i);
			}
		}


		// figure out the dangerous Animal, that I could be killed!
		if ((*i)->GetName() != "Rui" && ((*i)->GetEnergy() > this->GetEnergy()))
		{
			for (list<Animal*>::iterator j = neighbors.begin(); j != neighbors.end(); j++)     // check in neighbor
			{
				if (*i == *j )      // animal belong to neighbors &&  who are enemy of me!
					Enemy.push_back(*i);
			}
		}

		// figure out the nearby plants, and eat it

		if ((*i)->GetName() == "Plant" )
		{
				Plant.push_back(*i);
		}
	}

	// benefit must be bigger than 10, thun move to kill others, otherwise stay STILL!!!! 
	double benefit = 10;             // create the benefit of Target , find it, chase it,  then Kill it.
	Animal* Target1 = NULL;         //  define NO.1 easy meat!
	for (list<Animal*>::iterator i = Target.begin(); i != Target.end(); i++)              // iterator the Target list.
	{
		if (benefit < (-0.2 * this->GetEnergy() + 0.8 * (*i)->GetEnergy()))               // find the target can provide benefits that is bigger than 10 
		{
			double benefit = -0.2 * this->GetEnergy() + 0.8 * (*i)->GetEnergy();         // override the benefit
			Target1 = (*i);																// find the biggest benefit one.
		}
	}

	// Check the approaching enemy and runnnnnnn away!

	double danger_degree = 10000000;													 // define dangerous degree
	Animal* Enemy1 = NULL;
	for (list<Animal*>::iterator i = Enemy.begin(); i != Enemy.end(); i++)              // iterator the Target list.
	{
		vector<double> P_Enemy = (*i)->GetPosition();
		vector<double> P_Me = this->GetPosition();
		double dist = sqrt(pow((P_Enemy[0] - P_Me[0]), 2) + pow((P_Enemy[1] - P_Me[1]), 2));
		if (danger_degree > dist / 10)           // danger_degree define as the chance I CAN escape.
		{
			danger_degree = dist / 10;         // less chance to survive
			Enemy1 = (*i);		              // find the most dangerous enemy.
		}
	}

	// Check the nearest plant and eat it

	double D = 20;													 // define dangerous degree
	Animal* plant1 = NULL;
	for (list<Animal*>::iterator i = Plant.begin(); i != Plant.end(); i++)              // iterator the Target list.
	{
		vector<double> P_Plant = (*i)->GetPosition();
		vector<double> P_Me = this->GetPosition();
		double dist = sqrt(pow((P_Plant[0] - P_Me[0]), 2) + pow((P_Plant[1] - P_Me[1]), 2));
		if (D > dist)           // danger_degree define as the chance I CAN escape.
		{
			plant1 = (*i);		              // find the most dangerous enemy.
		}
	}

	// Initialization velocity!!!
	vector<double> u;

	if (Target1)									                 // if there is easy meat!  check outspace
	{
		cout << "Attack " << Target1->GetName() << endl;							// find the name of easy meat
		vector<double> P1 = Target1->GetPosition();
		vector<double> P0 = this->GetPosition();
		u.push_back((P1[0] - P0[0])/Delta_t);                                                        //making it toward the target...
		u.push_back((P1[1] - P0[1])/Delta_t);                                                       // maximum Velocity is 10 , theta is the tangential of two animal;
	}
	else if (Enemy1 && danger_degree < 2)                         // when the distance of Enemy is within 20, then run!!
	{
		cout << "Escape" << Enemy1->GetName() << endl;
		vector<double> P2 = Enemy1->GetPosition();
		vector<double> P0 = this->GetPosition();
		u.push_back((P2[0] - P0[0]) / Delta_t);													  // escape!!   different direction ! escape!
		u.push_back((P2[1] - P0[1]) / Delta_t);
	}
	else if (plant1)
	{
		cout << "Eat Plant" << plant1->GetName() << endl;
		vector<double> P3 = plant1->GetPosition();
		vector<double> P0 = this->GetPosition();
		u.push_back((P3[0] - P0[0]) / Delta_t);													  // escape!!   different direction ! escape!
		u.push_back((P3[1] - P0[1]) / Delta_t);
	}
	else
	{
		u.push_back(0.0); //random,            -0.001 ~ +0.001
		u.push_back(0.0); //random,            if there is no easy meat or enemy! stand STILL, Save energy!
	}

	double Mode = sqrt(pow(u[0], 2) + pow(u[1], 2));
	if (Mode > Max_Velocity)
	{
		u[0] = Max_Velocity * u[0] / Mode;
		u[1] = Max_Velocity * u[1] / Mode;
	}


	vector<double> p_ori = this->GetPosition();
	vector<double> p_nex;
	double x_new = p_ori[0] + u[0] * Delta_t;    //next position in the domain
	double y_new = p_ori[1] + u[1] * Delta_t;    //next position in the domain
	p_nex.push_back(x_new);
	p_nex.push_back(y_new);
	cout << "x_new " << x_new << "y_new" << y_new << endl;

	if (OutSpace(p_nex))	 //return bool, if out space will return turn!!!!   warning
	{
		// warning can not out of space, move another direction or stand still
		u.clear();
		u.push_back(0);
		u.push_back(0);
	}

	cout << "velcoity Vx: " << u[0] << "velocity Vy:  " << u[1];
	//u.push_back(u[0]);//Vx
	//u.push_back(u[1]);//Vy

	//Set Velocity
	SetVelocity(u);

	double Energy_consuming = 0.5 * (m)* (pow(u[0], 2) + pow(u[1], 2));     // 0.5*m*v^2
	// every step moving toward to easy meat will consume energy//
	SetEnergy((this->GetEnergy() - Energy_consuming));                 // set the new energy!
}
