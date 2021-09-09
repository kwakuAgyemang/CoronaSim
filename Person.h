#pragma once
#include <string>
#include <iostream>
#include <vector>


using namespace std;

enum class State { UNINFECTED, INFECTED_BUT_NOT_SICK, INFECT_AND_SICK, DEAD };

class Person
{
public:
	Person();
	Person(string name, unsigned int age, float spreadProb);
	void printPerson();


	//Getters
	string getName();
	int getAge();
	float getProb();

	//Setters
	void setName( string name );
	void setspreadProb( float spreadProb );
	
	void restart();

	void next(Person *nextPerson);
	void getConnections();
	vector<Person*> connection();
	
	void increaseInfectedDays();
	int infectedDays();
	void increaseInfectedState();
	State getState();
	void Recover();
	//void Policy();

	bool getRecovered();

private:
	string _name;
	unsigned int _age;
	float _spreadProb;
	vector<Person*> _nextPerson;
	State _personState;
	int _infectedDays = 0;
	int _recovered;

	void setState(State something);
};

