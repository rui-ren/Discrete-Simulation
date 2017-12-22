#include "Sim.h"
#include <math.h>
#include "Animal.h"
using namespace std;

vector<double> GetSpace()
{
	vector<double> s;
	s.push_back(Space_X);//X0
	s.push_back(Space_Y);//Y0
	return s;
}

void UpdatePosition(list<Animal*>& a)
{
	//update to the new position when velocity is set
	for (list<Animal*>::iterator i=a.begin(); i!=a.end();i++)
	{
		vector<double> p0=(*i)->GetPosition();
		vector<double> v=(*i)->GetVelocity();
		//cout<<"Position: [ "<<p0[0]<<" , "<<p0[1]<<" ]      Velocity: ( "<<v[0]<<" , "<<v[1]<<" )"<<endl;
		double x=p0[0]+ v[0]*Delta_t;    //new x
		double y=p0[1]+ v[1]*Delta_t;    //new y
		vector<double> p1;
		p1.push_back(x); p1.push_back(y);		
		(*i)->SetPosition(p1);//set the new position
	}
}

void CollisionDetection(list<Animal*>& a)
{
	//Please implement this function
	//Check collisions
	//remove them from the list

	auto It =a.begin();
	while (It != a.end())
	{
		if (OutSpace((*It)->GetPosition()))
		{
			delete *It;
			It = a.erase(It);

		}
		else
		{
			It++;
		}
	}

	for (list<Animal*> ::iterator i = a.begin(); i != a.end(); i++)
	{
		for (list<Animal*>::iterator j = a.begin(); j != a.end(); j++)
		{
			if (*i != *j)
			{
				vector<double> P_i = (*i)->GetPosition();		// find the position of i
				vector<double> P_j = (*j)->GetPosition();       // find th position of j
				double dx = P_i[0] - P_j[0];
				double dy = P_i[1] - P_j[1];
				double Distance = sqrt(pow(dx, 2) + pow(dy, 2));
				if (Distance <= Collision_Distance)
				{
					if ((*i)->GetName() != "Plant" && (*j)->GetName() != "Plant")
					{
						if ((*i)->GetEnergy() > (*j)->GetEnergy())
						{
							double temp = 0.8 * (*i)->GetEnergy() + 0.8 * (*j)->GetEnergy();
							(*i)->SetEnergy(temp);
							(*j)->SetEnergy(0);

						}
						if ((*i)->GetEnergy() < (*j)->GetEnergy())        // check the energy
						{
							double temp = 0.8 * (*i)->GetEnergy() + 0.8 * (*j)->GetEnergy();
							(*j)->SetEnergy(temp);
							(*i)->SetEnergy(0);
						}
						if ((*i)->GetEnergy() == (*j)->GetEnergy())        // if energy equals, both die

						{
							(*j)->SetEnergy(0);
							(*i)->SetEnergy(0);
						}
					}
					else
						{
						double temp = 0.8 * (*i)->GetEnergy() + 0.8 * (*j)->GetEnergy();
						if ((*i)->GetName() == "Plant")          // plant can not move . assum not collision!!
							{
								(*i)->SetEnergy(temp);
								(*j)->SetEnergy(0);
							}
						else if ((*j)->GetName() == "Plant")
							{
								(*j)->SetEnergy(temp);
								(*i)->SetEnergy(0);
							}
						else  // both are plants
							{
								(*i)->GetEnergy();
								(*j)->GetEnergy();     // do not set energy!!!
							}
						}
					}
				}	
			}
		}

	 It = a.begin();
		while (It != a.end())
		{
			if (abs((*It)->GetEnergy()) < 1.0e-3)
			{
				delete *It;
				It = a.erase(It);
			}
			else
			{
				It++;
			}
		}
}

void PrintOut(list<Animal*>& a)
{
	//Please implement this function
	//count animals still alive.
	cout << "list of animals:    " << endl;
	for (list<Animal*> ::iterator i = a.begin(); i != a.end(); i++)
	{
		vector<double> v = (*i)->GetPosition();
		cout << "Animals still alive:  " << (*i)->GetName() << endl;
		cout << (*i)->GetName() << ",Position @ (" << v[0] << "," << v[1] << ")." << endl;
	}
	cout << "The whole number of alive Animals:    " << a.size() << endl;
}

bool OutSpace(vector<double> u)
{
	vector<double> s=GetSpace();
	if (u[0]<0 ||u[1]<0) return true;
	if (u[0]>s[0] || u[1]>s[1]) return true;
	return false;
}
