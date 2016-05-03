//              FILE NAME : prog5b.cpp	
//              PURPOSE   : determines order in which to take prerequisite courses
//              WRITTEN FOR : CS 3013, Dr. Stringfellow	 
//              WRITTEN BY : Scott Schumacher
//              DATE : 1 May 2016

//#include <ctype>
#include <iostream>
#include <fstream>
#include "DiGraph.h"
#include "EnhDiG.h"
#include "SortedList.h"
#include <stack>
using namespace std;

void openFileRead(ifstream & infile, ofstream & outfile);
void exitMessage();
void processCourse(DiGraph &, stack <int> &, ofstream & outfile);

int main()
// PreCondition : none
// PosrCondition : The prerequisites for the courses in a program of study  
//                 are read from an input file, and the prerequisites for  
//                 each course selected by the user are found and sent to  
//                 the output file.  The process is repeated  until the user  
//                 decides to stop looking for prerequisites  
// ErrorCondition : none  
{
	// open input & output files
	ifstream infile;
	ofstream outfile;
	openFileRead(infile, outfile);

	//create a graph (precondition reading data file)

	DiGraph graph;

	// read data file into G
	ReadDiGraph(graph, infile, outfile);

	// 5B find, and print to outfile, prerequisites for selected courses

	// create stack to hold prerequisites
	stack <int> prerex;
		
	processCourse(graph, prerex, outfile);
	
	//5B close files
	outfile.close();
	infile.close();
	
	return 0;
}

void openFileRead(ifstream & infile, ofstream & outfile)
{
	char inFileName[40];
	cout << "Welcome to Scott's directed graph/ courses program. It reads a a list of \n";
	cout << "prerequisite courses and, for any given course, lists the order in which the \n";
	cout << "prerequisites must be taken.\n\n";
	cout << "Please enter the input file name: ";
	cin >> inFileName;
	infile.open(inFileName);

	//Display error message if file fails to open.
	if (infile.fail())
	{
		cout << "Couldn't open the file.\n";
		cout << "Check the file name and location\n";
		system("pause");
		exit(0);
	}
	char outFileName[40];
	cout << "Please enter the name of the output file: ";
	cin >> outFileName;
	outfile.open(outFileName);
	//heading for output files:
	outfile << "Scott Schumacher\n";
	outfile << "File Name: " << outFileName << endl;
	outfile << "Description: Output file: target course and prerequisites; input file was- ";
	outfile << inFileName << "."<<endl<<endl<<endl;
}

void exitMessage()
{
	cout << endl << endl;
	cout << "Thanks for using Scott's course planning program. ";
	cout << "Valid outputs have been sent to the file you specified.";
}

void processCourse(DiGraph& G, stack<int> & prerex, ofstream & outfile)
{
	//get valid course:

	int crsNo;
	cout << "Please enter the course number: ";
	cin >> crsNo;

	//check if course number is within valid range:
	if (!(crsNo >= 0) || (crsNo >= G.GetNumberOfVertices()))
	{
		cout << "This is not a valid course number.";
	}
	//check that the course has prerequisites...if outDegree is not greater than 0.
	if (!(G.GetOutDegree(crsNo) > 0))
	{
		cout << "This course has no prerequisites. No output was produced.";
		char again;
		cout << endl << endl << "Would you like to check another course?\n";
		cout << "If yes, please type 'Y' followed by the ENTER key;\n";
		cout << "otherwise type 'n' followed by the ENTER key.      ";
		cin >> again;
		if ((again == 'Y') || (again == 'y'))
		{
			processCourse(G, prerex, outfile);
		}
		else exitMessage();
	}
	else
	{
		//find linear order
		FindLinearOrder(G, crsNo, prerex);
		//print linear order
		PrintLinearOrder(outfile, prerex);
		outfile << endl << endl;
	}
	//do you want to go again?
	char again;
	cout << endl << endl << "Would you like to check another course?\n";
	cout << "If yes, please type 'Y' followed by the ENTER key;\n";
	cout << "otherwise type 'n' followed by the ENTER key.      ";
	cin >> again;
	if ((again == 'Y') || (again == 'y'))
	{
		processCourse(G, prerex, outfile);
	}
	else exitMessage();
}
