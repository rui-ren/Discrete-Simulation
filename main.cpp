
#include "Animal.h"
#include "Sim.h"
#include <list>
#include <string>
using namespace std;


int main(int argc, char* argv[])
{
	list<Animal*> List_of_Animals;
	//First show all "Animal" types
	cout<<"The following Animals can be created:"<<endl;
	for (list<string>::iterator i=Animal::Animal_list.begin(); i!=Animal::Animal_list.end();i++)
		{
			cout<<(*i)<<endl;
		}
	cout<<"Total Animal Types: "<<Animal::Animal_list.size()<<endl;

	//Step 1: Creating Animals
	int cc=0;
	for (list<string>::iterator i=Animal::Animal_list.begin(); i!=Animal::Animal_list.end();i++)
		{
			for (int j=0; j<20; j++)
				{
					cout<<"Creating Animal:  "<<(*i)<<endl;
					Animal* ptr=Animal::Create((*i));//create it
					if(ptr)
						{
							vector<double> S=GetSpace();
							vector<double> p;
							p.push_back(j*400+200); //x
							p.push_back(cc*100+100); //y
							ptr->SetPosition(p); //set the initial position
							List_of_Animals.push_back(ptr);//put it in the list
							//monitoring
							cout << "List_of_animals";
							for (list<Animal*>::iterator i = List_of_Animals.begin(); i != List_of_Animals.end(); i++)
							{
								cout << (*i)->GetName() << ",  ";
							}
							cout << "\b\b" << endl;
						}
				}
			cc++;
		}
	cout<<"List of all Animals...."<<endl;

	for (list<Animal*>::iterator i=List_of_Animals.begin(); i!=List_of_Animals.end();i++)
		{
			vector<double> u=(*i)->GetPosition();
			cout<<"Position: (x, y)"<< u[0]<<"   ,  "<<u[1]<<endl;
		}

	cout<<"========================================================================================================"<<endl;
	cout<<"Creating aniamls completed! Total animals created: "<<List_of_Animals.size()<<endl;
	cout<<"========================================================================================================"<<endl;

	//now start simulation, do N steps
	for (long k=0; k<N; k++)
	{
		double t=k*Delta_t; //current time;
		cout<<"Time: "<<t<<" seconds...."<<endl;
		//step 3: update animal and plant
		for (list<Animal*>::iterator i=List_of_Animals.begin(); i!=List_of_Animals.end();i++)
			{
				(*i)->Update(List_of_Animals);//update
			}
		//Step 4: Update Position
		UpdatePosition(List_of_Animals);
		auto It = List_of_Animals.begin();
		while (It != List_of_Animals.end())
		{
			if ((*It)->GetEnergy() <= 0)
			{
				delete *It;
				It = List_of_Animals.erase(It);

			}
			else
			{
				It++;
			}
		}

		//Step 5: Collision Detection
		CollisionDetection(List_of_Animals);


		//Step 6: Print Out the remaining animals:

		PrintOut(List_of_Animals);
	}

	//show where are the animals

	cout<<"List of all Animals...."<<endl;
	for (list<Animal*>::iterator i=List_of_Animals.begin(); i!=List_of_Animals.end();i++)
		{
			vector<double> u=(*i)->GetPosition();
			cout<<(*i)->GetName()<<" Position: (x, y)"<< u[0]<<"   ,  "<<u[1]<<endl;
		}

	system("pause");
	return 0;
}
