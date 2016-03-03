#include "RegistrarSimulation.h"
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <algorithm>
using namespace std;

RegistrarSimulation::RegistrarSimulation(string fileName){
	findNumStudents(fileName);
}
void RegistrarSimulation::findNumStudents(string fileName){
	ifstream reader(fileName.c_str());
	numStudents = 0;
	string line;
	int line_num = 0;
	int counter = 1;
	int nextLine = 3;
	while(getline(reader,line)){
		line_num = atoi(line.c_str());

		if (counter == 1)
		{
			// sets how many windows there are
			numWindows = line_num;
			window_ary = new int[numWindows];
			window_wait = new int[numWindows];
			for (int i = 0; i < numWindows; ++i)
			{
				window_ary[i] = 0; //set all windows to 0 initially
				window_wait[i] = 0;

			}
		}
		else if(nextLine == counter){
			numStudents += line_num; //finds the lines in the file with the number of students 
			
			nextLine += (line_num+2); //increases that line to the next student in the file 
		}
		counter++;
	}
	reader.close();
	// Sets student array for how many students will show up 
	student_ary = new int[numStudents];
	for (int i = 0; i < numStudents; ++i)
	{
		student_ary[i] = 0;
	}
	// putting all numbers in file to an array
	file_numbers = new int[counter-1];
	counter = 0;
	ifstream reader2(fileName.c_str());
	while(getline(reader2,line)){
		line_num = atoi(line.c_str());
		file_numbers[counter] = line_num;
		counter++;
	}
	
	reader2.close();
}
void RegistrarSimulation::simulation(){
	bool condition = true;
	int num_arrived = 0;
	int counter = 1;
	int index = 1;
	int window_in_use = 0;
	int student_wait_index = 0;
	quee = new GenQueue<int>(); //instantiate quee
	while(num_arrived != numStudents || condition){
		
		if (num_arrived != numStudents)
		{	

			if (file_numbers[index]==counter) //go through the file and find how many students enter at what time 
			{
				index++; //increase index to get wait times 
				int loop = file_numbers[index]; //set a variable to run the for loop since you are incrementing index each time
				for (int i = 0; i <loop; ++i)
				{
					quee->insert(file_numbers[++index]); //insert how many students are supposed to arrive and insert their window time 
					
				}
				index++; //increase index to next number in the file 
			}
		}

		window_in_use = 0;
		for (int i = 0; i < numWindows; ++i)
		{
			if(window_ary[i] == 0){
				if (!quee->isEmpty()) //if there is an open window and a student waiting 
				{
					window_ary[i] = quee->remove(); //if there's someone waiting in line and there is a window open, send the data to the window
					num_arrived++;	//arrived students gets increased 
					student_wait_index++; //delete a student that is waiting and move the head of the line to the one behind 
				}else{

					window_wait[i]++; //if a window isnt filled, increase its wait time 
				}
			}else{
				window_in_use++; //if a window has a value increase the windows in use 
				
				window_ary[i]--; //decrease the use time of window by one each time "click"
			}
		}
		if (window_in_use == numWindows)
		{
			for (int i = 0; i < quee->size; ++i)
			{
				student_ary[student_wait_index+i]++; //increase the student wait times if all windows are full 
			}
		}
		if (num_arrived == numStudents) //if all of the students have arrived 
		{
			window_in_use = 0;
			for (int i = 0; i < numWindows; ++i) //go through each window 
			{
				if (window_ary[i] == 0) 
				{
					window_in_use++; //checks if all of the windows are free of student time 

				}
			}
			if (window_in_use == numWindows) //if all windows are done, it breaks out of the loop
			{
				condition = false;
			}
		}
		counter++; //increase the time click each time 
	}
	//sorts the arrays so we can find the max values 
	sort(student_ary, student_ary + numStudents);
	sort(window_wait, window_wait + numWindows);
	calculateStuff(); //calculate the statistics 

}

void RegistrarSimulation::calculateStuff(){
	//initialize all variables to 0
	mean_SWT = 0;
	meadian_SWT = 0;
	longest_SWT = 0;
	num_SOver10 = 0;
	mean_WIT = 0;
	longest_WIT = 0;
	num_WOver5 = 0;
	//find the statistics for the student wait times
	longest_SWT = student_ary[numStudents-1];
	if (!isdigit(numStudents/2))
		meadian_SWT = student_ary[numStudents/2];
	else {
		int medianA = numStudents/2;
		int medianB = (numStudents/2) + 1;
		meadian_SWT = (medianA + medianB)/2;
	}
	for (int i = 0; i < numStudents; ++i)
	{
		mean_SWT += student_ary[i];
		if (student_ary[i] > 10)
			num_SOver10++;
	}
	mean_SWT /= numStudents;
	//find the statistics for the window idle times
	longest_WIT = window_wait[numWindows-1];
	for (int i = 0; i < numWindows; ++i)
	{
		mean_WIT += window_wait[i];
		if (window_ary[i] > 5)
			num_WOver5++;
	}
	mean_WIT /= numWindows;
	//print out all statistics
	cout << endl;
	cout << "Mean student wait time: " << mean_SWT << endl;
	cout << "Median student wait time: " << meadian_SWT << endl;
	cout << "Longest student wait time: " << longest_SWT << endl;
	cout << "Number of students with a wait time over 10: " << num_SOver10 << endl;;
	cout << "Mean window idle time: " << mean_WIT << endl;
	cout << "Longest window idle time: " << longest_WIT << endl;
	cout << "Number of windows with an idle time over 5: " << num_WOver5 << endl;
	cout << endl;
	
}
//delete all the allocated memory in the destructor
RegistrarSimulation::~RegistrarSimulation(){
	delete [] student_ary;
	delete [] window_ary;
	delete [] file_numbers;
	delete [] window_wait;
	delete quee;
}






