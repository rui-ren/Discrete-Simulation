#ifndef SIM_H_
#define SIM_H_

#include "Animal.h"
#include <list>
#include <vector>
using namespace std;

//--Constants used in the simulation-------------------
const double Delta_t=1.0; //time step 1 second
const long N=10000; //10000 steps
const double Collision_Distance=1; //collision distance
const double Space_X=10000; //space x
const double Space_Y=10000; //space y
const double Perceive_Distance=100;  //Perceivable distance
const double Max_Velocity=10; //maximum velocity allowed.
const double Max_Energy=500;
const double Max_Mass=10;
//-----------------------------------------------------
vector<double> GetSpace();
void UpdatePosition(list<Animal*>& a);
void CollisionDetection(list<Animal*>& a);
void PrintOut(list<Animal*>& a);
bool OutSpace(vector<double> u);////check if it is out of the space..
#endif
