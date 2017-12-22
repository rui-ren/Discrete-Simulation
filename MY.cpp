//MY.cpp

//

#include "MY.h"
#include "Sim.h"
#include <math.h>

int MY::Counter = 0; //initialize to 0 so that it can be created.
MY aa;//this will force the Initializer to add this class to the factory. 
			//later on the factor can be used to generate objects dynamically..


Animal* MY::create(const string& s) //used when the "factory" want to generate an object.
{
	if(s=="MY")
	  {
		cout<<"Creating MY "<<endl;
		return new MY; //will this lead to memory leaking? 
		
	  }
	else
		return 0;//hmmm, Not this one.. return nothing
};
MY::MY()
{
  cout<<"Adding MY Method into the factory"<<endl;
  Animal::name="MY";
  Animal::m=Max_Mass;
  Animal::E=Max_Energy;
  if(Counter== 0)
	{
		MY::AddCreator(create); //only add once.
		Animal::Animal_list.push_back("MY"); //add the name into the list
		Counter=1; //flag
	}
};

MY::~MY()
{
	cout<<"Removing MY Method"<<endl;
}

void MY::Update(const list<Animal*>& a)
{
        //cout<<"Find neighbors within radius r (=100)"<<endl;
	list<Animal*> neighbors=Perceive(a, Perceive_Distance);
	//cout<<"Neighbors: "<<neighbors.size()<<endl;

	//do my computation
	Animal* Target=NULL; //first one in the list as the target
	
  	for (list<Animal*>::const_iterator i=a.begin(); i!=a.end();i++)
	{
		if ( (*i)->GetName()!= "MY")
		{
			Target=(*i);
			break;
		}
	}
	vector<double> u;
	double Vx, Vy;
	if(Target)
	{
		//cout<<"Attack "<<Target->GetName()<<endl;
		vector<double> P1=Target->GetPosition();//get target position
		vector<double> P0=this->GetPosition();
		Vx=(P1[0]-P0[0])/10.0; //making it toward the target...
		Vy=(P1[1]-P0[1])/10.0;
	}
	else
	{
		Vx=(double (rand()%10000)/10000.0-0.5) * 4.0; //random, -0.5 ~ +0.5
		Vy=(double (rand()%10000)/10000.0-0.5) * 4.0; //random, 
	}
	//cout<<"velcoity: "<<Vx<<", "<<Vy;
	u.push_back(Vx);//Vx
	u.push_back(Vy);//Vy
	//Set Velocity
	SetVelocity(u);
}
