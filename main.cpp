#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Person.h"
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;


bool InitPopulation(vector<Person>& Persons, string filename);
bool InitConnections(string filename, vector<Person>& Persons);
float MaxAge(vector<Person>& Persons);
float diseaseProb(float age, vector<Person>& Persons);
void simulate(vector<Person>& Persons);
int infectRand(vector<Person> &Persons);


/* You can use this function to simulate
probabilities */
bool simulate_prob(float prob) {

    prob = prob * 1000;

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> random_number(1, 1000); // distribution in range [1, 1000]

    if (random_number(rng) <= prob)
        return true;

    return false;

}


int main() {
    
    /* The number of days simulation will run for */
    int days_to_simulate = 100;
    int days_to_simulate1 = 100;

    /* Ask the user for the population and
    connections files */
    cout << "Welcome to CoronaSim!" << endl;
    string pop_file, conn_file;
    cout << "Enter population file name: ";
    cin >> pop_file;
    cout << "Enter connections file name: ";
    cin >> conn_file;

    // TODO: Populate your graph data structure
    bool is_populated = false;
    vector<Person> Persons;
    bool pop = InitPopulation(Persons, pop_file);
    bool con = InitConnections(conn_file, Persons);
    
    
    if (pop && con) 
        is_populated = true;

    if (is_populated)
        cout << "File Loaded!" << endl;

    int infectedNotsick = 0;
    int sick = 0;
    int dead = 0;
    int recovered = 0;
    int infectNum = infectRand(Persons);
    
    

    while (is_populated) {

        int choice;

        /* Print menu of things that your application can do*/
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Print population" << endl;
        cout << "2. Simulate" << endl;
        cout << "3. Summarize population" << endl;
        cout << "4. Reset" << endl;
        cout << "5. Exit" << endl;
        cout << "*** *** *** *** *** *** *** *** *" << endl;
        cout << "Your selection: ";

        /* TODO: You should feel free to add other
        items to the menu above for your demo video */

        cin >> choice;

        /*Ideally inside the various cases of the switch
        statement below, you will call specific functions
        supported by your graph data structure and your
        simulation algorithm. You can design all these
        functions as you like.*/


        switch (choice) {

        case 1:
            /* TODO: Print your population. Use
            any format you like.*/
            //for (unsigned int i = 0; i < Persons.size(); i++) {
            //    Persons[i].printPerson();
            //    //cout << diseaseProb(Persons[i].getAge(), Persons) << endl;
            //}
            
            //Printing each person's connections

            for (unsigned int i = 0; i < Persons.size(); i++) {
                Persons[i].getConnections();
            }
            
            break;

        case 2:
            /* TODO: Run simulation as described
            in the handout.*/

            //Random person infection

            
            Persons[infectNum].increaseInfectedState();

            //Simulation
            while (days_to_simulate > 0) {
                simulate(Persons);
                days_to_simulate--;
            }
            
            for (unsigned int i = 0; i < Persons.size(); i++) {
                Persons[i].printPerson();
            }

            
            break;

        case 3:
            /* TODO: Print a summary of the population
            here. Design the summary as you like.
            Print at least the number of people
            infected, sick, recovered, dead etc.*/
            for (unsigned int i = 0; i < Persons.size(); i++) {
                if (Persons[i].getState() == State::INFECTED_BUT_NOT_SICK) {
                    infectedNotsick++;
                }
                if (Persons[i].getState() == State::INFECT_AND_SICK) {
                    sick++;
                }
                if (Persons[i].getState() == State::DEAD) {
                    dead++;
                }
                if (Persons[i].getRecovered() == true) {
                    recovered++;
                }
            }
            
            cout << "Population Size: " << Persons.size() <<
                "\nInfected people who are not sick: " << infectedNotsick <<
                "\nInfected people who are sick: " << sick <<
                "\nDead: " << dead <<
                "\nRecovered: " << recovered << endl;
            
            break;

        case 4:

            /* TODO: Implement your own policy and
            re-simulate.*/
            for (unsigned int i = 0; i < Persons.size(); i++) {
                Persons[i].restart();
            }
            
            infectedNotsick = 0;
            sick = 0;
            dead = 0;
            recovered = 0;
            /*
            Persons[infectNum].increaseInfectedState();
            for (unsigned int i = 0; i < Persons.size(); i++) {
                Persons[i].Policy();
            }
            while (days_to_simulate1 > 0) {
                simulate(Persons);
                days_to_simulate1--;
            }
            for (unsigned int i = 0; i < Persons.size(); i++) {
                Persons[i].printPerson();
            }
            break;*/

        case 5:

            /* TODO: Here de-allocate all dynamically
            allocated variables before exiting*/
            is_populated = false;
            return 0; // exiting
        }
    }
}

//Intitializes the Population
bool InitPopulation(vector<Person>& Persons, string filename) {
    ifstream File(filename);                    //Opens the file
    if (File.fail()) {                          //Checks for any errors in opening the file
        perror(filename.c_str());
        return false;
        system("PAUSE");
    }
    string line;
    string name;
    float age;
    float spreadProb;
    while (File >> name >> age >> spreadProb) { //Creates a new Person using data from the file
        Person newPerson(name, age, spreadProb);
        Persons.push_back(newPerson);
    }
    File.close();
    return true;

}

//Intitalizes the connections of the population
bool InitConnections(string filename, vector<Person>& Persons) {
    ifstream File(filename);
    if (File.fail()) {
        perror(filename.c_str());
        return false;
        system("PAUSE");
    }
    Person* name1;
    Person* name2;
    string nam1;
    string nam2;

    while (File >> nam1 >> nam2) {
        for (unsigned int i = 0; i < Persons.size(); i++) {
            if (nam1 == Persons[i].getName()) {
                for (unsigned int j = 0; j < Persons.size(); j++) {     //Adds a pointer to a person to the current person's connections
                    if (Persons[j].getName() == nam2) {
                        name2 = &Persons[j];
                        Persons[i].next(name2);
                    }
                }
            }
            if (nam2 == Persons[i].getName()) {
                for (unsigned int j = 0; j < Persons.size(); j++) {     //Adds a pointer to a person to the current person's connections
                    if (Persons[j].getName() == nam1) {
                        name1 = &Persons[j];
                        Persons[i].next(name1);
                    }
                }
            }
        }
    }
    File.close();
    return true;
}

int infectRand(vector<Person> &Persons) {
    srand(time(0));
    int infectNum = 1 + rand() % (Persons.size() - 1);
    return infectNum;
    
}

//Finds the maximum age of the people
float MaxAge(vector<Person>& Persons) {
    float maxAge = Persons[0].getAge();
    for (unsigned int i = 0; i < Persons.size(); i++) {
        if (maxAge < Persons[i].getAge()) {
            maxAge = Persons[i].getAge();
        }
    }
    return maxAge;
}

//Calculates the disease Probability based on the maximum age of the vector
float diseaseProb(float age, vector<Person>& Persons) {
    float dProb = age / MaxAge(Persons);
    return dProb;
}


//Does the simulation
void simulate(vector<Person>& Persons) {
    // j Person vector
    //i pointer vector

    //Infection
    for (unsigned int j = 0; j < Persons.size(); j++) {
        if (Persons[j].getState() == State::INFECTED_BUT_NOT_SICK || Persons[j].getState() == State::INFECT_AND_SICK) {
            for (unsigned int i = 0; i < Persons[j].connection().size(); i++) {
                if (Persons[j].connection()[i]->getState() == State::UNINFECTED) {      //If the person has not already been infected or has recovered
                    if (simulate_prob(Persons[j].getProb())) {
                        Persons[j].connection()[i]->increaseInfectedState();        //Infect the person
                    }
                }
            }
        }
    }

    //Getting sick
    for (unsigned int j = 0; j < Persons.size(); j++) {
        if (Persons[j].getState() == State::INFECTED_BUT_NOT_SICK) {                // If the person is infected but not sick
            if (simulate_prob(diseaseProb(Persons[j].getAge(), Persons))) {         //Simulate the probability of the person falling sick based on their disease probability
                Persons[j].increaseInfectedState();
            }
        }
    }

    //Recovery
    float dProb;
    for (unsigned int j = 0; j < Persons.size(); j++) {
        dProb = diseaseProb(Persons[j].getAge(), Persons);
        if (simulate_prob(1 - dProb) == true && (Persons[j].getState() == State::INFECTED_BUT_NOT_SICK || Persons[j].getState() == State::INFECT_AND_SICK)) { 
            Persons[j].Recover();
        }
    }

    //Increase the infected days or declare the person as dead
    for (unsigned int i = 0; i < Persons.size(); i++) {
        if ((Persons[i].infectedDays() == 7 && Persons[i].getState() == State::INFECT_AND_SICK)) { //If the person has been sick for seven days
            Persons[i].increaseInfectedState();
        }
        if (Persons[i].getState() == State::INFECT_AND_SICK) {
            Persons[i].increaseInfectedDays();
        }
    }
    
}





