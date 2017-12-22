//implement your Animal base class here..
#include"Animal.h"
#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<math.h>

using namespace std;

list<string> Animal::Animal_list;
list<Creator> Animal::creator_list;

Animal::Animal()
{
	/*if (Animal::Animal_list == NULL)
	Animal::Animal_list = new list<string>;
	if (Animal::creator_list == NULL)
	Animal::creator_list = new list<Creator>;*/
}

Animal::~Animal()
{
	//don't delete here
}

Animal* Animal:: Create(const string& Method_Name)
{
	for (list<Creator> ::iterator i = Animal::creator_list.begin(); i != Animal::creator_list.end(); i++)
	{
		Animal* tmp = (*i)(Method_Name);
		if (tmp) return tmp;
		
	}
}

void Animal :: AddCreator(Creator c)     // static
{
	Animal::creator_list.push_back(c);
};

string Animal:: GetName()
{
	return this->name;
}

vector<double> Animal::GetVelocity()
{
	return this->v;
}

vector<double> Animal :: GetPosition()
{
	return this->P;
}

void Animal::SetPosition(const vector<double> p)
{
	this->P = p;

}

void Animal::SetVelocity(vector<double> u)
{
	this->v = u;
}

void Animal::SetEnergy(double e)
{
	this->E = e;
}

double Animal::GetEnergy()
{
	return this->E;
}

void Animal::SetMass(double m)
{
	this->M = m;
}

double Animal::GetMass()
{
	return this->M;
}


list<Animal*> Animal::Perceive(const list<Animal*>& a, double r)
{
	// find the animal nearby and get the neighbor animal
	list<Animal*> b;
	for (list<Animal*>::const_iterator i = a.begin(); i != a.end(); i++)
	{
		vector<double> pi = (*i)->GetPosition();
		vector<double> pj = this->GetPosition();
		double d = sqrt(pow((pi[0] - pj[0]), 2) + pow(pi[1] - pj[1], 2));
		if (d < r && this->GetName() != (*i)->GetName())
			b.push_back(*i);
	}
	return b;
}

void Animal::Update(const list<Animal*>& a)
{

}