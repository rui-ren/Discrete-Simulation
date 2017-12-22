#ifndef ANIMAL_H
#define ANIMAL_H
#include "general.h"
#include <string>
#include <list>
#include <vector>
using namespace std;


class Animal;

typedef Animal*  (*Creator)(const string&);	//type-definition: "Creator" can be now used as a type
						//defines a function type
						//it takes a string as argument
						//and returns an Animal* pointer
						//any function that takes a string as argument and returns an Animal*
						//can be declared by Creator. For example, the create function in the derived survey methods.

class Animal
{
	protected:
		Animal();//  
	public:
		virtual ~Animal();
		static Animal* Create(const string& Method_Name);
		static list<Creator> creator_list;       //a list to hold all creators
		static list<string> Animal_list;		//list of the animal names
		static void AddCreator(Creator c);	   //add a Creator in the list. 
							//a Creator is a function that can be invoked to "manufacture" the survey method
		virtual string GetName();
		vector<double> GetVelocity();   //Get Velocity
		vector<double> GetPosition();  //Get Position
		void SetPosition(const vector<double> p); //set Position
		double GetEnergy();						//Set Energy
		void SetEnergy( double e);			// GetEnergy
		void Animal::SetMass(double m);
		double Animal::GetMass();
	protected:
		void SetVelocity(vector<double> u);//Set Velocity, not public!
		list<Animal*> Perceive(const list<Animal*>& a, double r); //find the neighbors and put them in a list.

	public:
		virtual void Update(const list<Animal*>& a)=0;   //pure virtual function, you implement it in your subclass

	protected:
		double m; //mass of the object
		vector<double> P;	//Position of the object
		vector<double> v; //velocity of the object
		double E; //Energy of the object
		double M;
		string name;

};
#endif

