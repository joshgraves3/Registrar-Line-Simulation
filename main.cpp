#include "RegistrarSimulation.h"
#include "GenQueue.h"
#include <iostream>
using namespace std;

int main (int argc, char** argv) {

	RegistrarSimulation* one = new RegistrarSimulation(argv[1]); //make an instance of the simulation class
	one->simulation(); //run the simulation

	delete one; //delete allocated memory
	return 0;
}