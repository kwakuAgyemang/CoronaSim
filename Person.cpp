#include "Person.h"

//Default constructor
Person::Person() {
	_name = "";
	_age = 0;
	_spreadProb = 0.0;
	_personState = State::UNINFECTED;
	_infectedDays = 0;
	_recovered = 0;
}

//Constructor for a person
Person::Person(string name, unsigned int age, float spreadProb) {
	_name = name;
	_age = age;
	_spreadProb = spreadProb;
	_personState = State::UNINFECTED;
	_infectedDays = 0;
	_recovered = 0;
}


//Returns the name of a person
string Person::getName() {
	return _name;
}

//Returns the age of a person
int Person::getAge() {
	return _age;
}

//Sets the name of a person
void Person::setName(string name) {
	_name = name;
}

//Sets the spread probability of a person
void Person::setspreadProb(float spreadProb) {
	_spreadProb = spreadProb;
}

//Sets the state of a person
void Person::setState(State state) {
	_personState = state;
}

//Sets all infection alterations to what it once was.
void Person::restart()
{
	_personState = State::UNINFECTED;
	_infectedDays = 0;
	_recovered = 0;
}

//Prints details on a person
void Person::printPerson() {
	string personState;
	if (_personState == State::UNINFECTED) {
		personState = "UNINFECTED";
	}
	if (_personState == State::INFECTED_BUT_NOT_SICK) {
		personState = "INFECTED BUT NOT SICK";
	}
	if (_personState == State::INFECT_AND_SICK) {
		personState = "INFECTED AND SICK";
	}
	if (_personState == State::DEAD) {
		personState = "DEAD";
	}
	cout << _name << " " << _age << " " << _spreadProb << " " << personState << endl;
}

//Adds a pointer to a person to a person's connections
void Person::next(Person *nextPerson) {
	_nextPerson.push_back(nextPerson);
}

//Returns a list of persons and the people they are connected to
void Person::getConnections() {
	cout << getName() << " --> ";
	for (unsigned int i = 0; i < _nextPerson.size(); i++) {
		if (_nextPerson[i]->getState() != State::DEAD) 
			cout << _nextPerson[i]->getName() << ", ";
	}
	cout << endl;
}


//Returns a vector containing pointers to persons representing their connections
vector<Person*> Person::connection() {
	return _nextPerson;
	
}

//Returns the spread probability of the person
float Person::getProb() {
	return _spreadProb;
}

//Increases the number of infected days
void Person::increaseInfectedDays() {
	_infectedDays++;
}

//Returns the number of infected days
int Person::infectedDays() {
	return _infectedDays;
}

//Increases the stage of sickness of the person
void Person::increaseInfectedState() {
	if (_personState == State::UNINFECTED) {
		setState(State::INFECTED_BUT_NOT_SICK);
		_recovered = 0;
	}
	else if (_personState == State::INFECTED_BUT_NOT_SICK) {
		setState(State::INFECT_AND_SICK); 
		_recovered = 0;
	}
	else if (_personState == State::INFECT_AND_SICK) {
		setState(State::DEAD);
		_recovered = 0;
	}
}

State Person::getState() {
	return _personState;
}


//Makes the person recover from the virus
void Person::Recover() {
	_recovered = 1;
	setState(State::UNINFECTED);
	_infectedDays = 0;
}

//Returns true if the person recoverd from the virus
bool Person::getRecovered() {
	if (_recovered == 1) {
		return true;
	}
	return false;
}


//The policy reduces each person's chance of spreading to 40% of its original value (stay at home)
//void Person::Policy() {
//	_spreadProb = _spreadProb * 0.4f;
//}
