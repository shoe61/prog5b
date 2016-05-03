
/*
UNIT NAME : EnhDiGraph.cpp
PURPOSE   : Enhanced DiGraph Operations Specifications
WRITTEN FOR : CS 3013
WRITTEN BY : Scott Schumacher
DATE : 21 April 16
*/
#include"DIGRAPH.H"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "enhdig.h"
using namespace std;


void ReadDiGraph(DiGraph & G, ifstream & InFile, ofstream & OutFile)
// PreCondition : G is created.  The first line of InFile contains the
//                number of vertices in the graph,, the following lines
//                are the edges (vertex pairs) of the Graph
// PostCondition : Graph G is the DiGraph specified by InFile
// ErrorCondition : Error if the size is invalid, or if there are invalid edges
{
	int GSize;
	int X;
	int Y;

	// read size of digraph to be created from infile */
	InFile >> GSize;

	// invalid graph size */
	if (GSize == 0)
	{
		cout << "Invalid File.";
	}

	//valid graph size
	else
	{
		//dynamically allocate temp, a SortedList array of GSize elements 

		DiGraph temp(GSize);

		// while there are vertices listed in InFile 
		while (!InFile.eof())
		{
			// get a pair of vertices from InFile */
			InFile >> X;
			InFile >> Y;
			if ((X < 0) || (X >(GSize - 1)) || (X == Y)) // vertices not in digraph or vertices not distinct 
			{
				cout << "Invalid Vertices; please check the file.";
				system("pause");

			}
			else // valid edge; add to temp
			{
				temp.AddEdge(X, Y);
			}
		}
		//Now that temp is created with GSize vertices, swap G and temp:

		G.SwapDiGraphs(temp);
	}
}     // read digraph 


void PrintDiGraph(DiGraph & G, ofstream & OutFile, bool complement)
// PreCondition  : G is created
// PostCondition : outfile"s first line is the size of the graph, the
//                 succeeding lines contain a list of vertices and the
//                 vertices to which they are adjacent
// ErrorCondition : none
{
	OutFile << endl << endl;
	// headings for graph or complement:
	if (complement)
	{
		OutFile << "There are " << G.GetNumberOfVertices() << " vertices";
		OutFile << "in the Directed Graph's complement.";
		OutFile << " The edges are:" << endl << endl;
	}
	else
	{
		OutFile << "There are " << G.GetNumberOfVertices() << " vertices in the Directed Graph.";
		OutFile << " The edges are:" << endl << endl;
	}

	for (int i = 0; i < G.GetNumberOfVertices(); i++)
	{
		OutFile << "From vertex " << i << " to ";
		for (int j = 0; j < G.GetNumberOfVertices(); j++)
		{

			if (G.IsEdge(i, j)) OutFile << j << "   ";
		}
		OutFile << endl;
	}
}     // print digraph */


void Complement(DiGraph & G, DiGraph & GComp)
// PreCondition : G and GComp are created
// PostCondition : G = #G, GComp is the same size as G and has edges between
//                 exactly those pairs of vertices not directly
//                 connected in G
// ErrorCondition : none
{

	// create GComp by creating a temp graph of correct size and no edges and swapping
	int size = G.GetNumberOfVertices();


	// for (each pair of vertices (i,j) in GComp,if (there is no edge
	// between those vertices in G, add an edge (i,j) in GComp
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		if (!(G.IsEdge(i, j)) && (i != j))//if i == j  not try to complement! 
		{
			GComp.AddEdge(i, j);
		}
	}

}     // complement 

void DoLinearOrder(DiGraph & G, int Course, stack<int> & prerex, ControlData & Visited)
// requires : G is created, PreReq is created, Course is a valid course
// ensures : G is unchanged; PreReq contains the sequence of courses that
//           have to be taken before Course, with Course itself at the top
// checks : Course is a valid course
{
	int i;
	int size = G.GetNumberOfVertices();

	// start at vertex <course>, mark vertex <course> as visited
	Visited[Course] = 1;

	// for (each vertex in G which has not already been visited
	for (i = 0; i < size; i++)
	{
		if ((G.IsEdge(Course, i)) && (Visited[i] == 0))
		{
			//if (there is an edge between <course> and <i>, recursively
			// call  LinearOrder for (vertex <i>
			Visited[i] = 1;
			DoLinearOrder(G, i, prerex, Visited);
		}

	}
		// with each return (backtrack) from a call to  LinearOrder,
		// add the vertex (for (which that call was made) to PreReq *
		prerex.push(Course);

}      //  LinearOrder 

	void FindLinearOrder(DiGraph & G, int Course, stack <int> & prerex)
	{
		int size = G.GetNumberOfVertices();

		//create array to record nodes visited; initialize all values to "false"
		ControlData Visited;
		for (int i = 0; i < size; i++)
		{
			Visited[i] = 0;
		}


		// clear stack Prerequisites 
		while (!(prerex.empty()))
		{
			prerex.pop();
		}

		// check if (Course is valid course number --this has been done by the calling function
		//else do it
		DoLinearOrder(G, Course, prerex, Visited);



	}  // FindLinearOrder

	void PrintLinearOrder(ofstream & OutFile, stack<int> & prerex)
		// requires : OutFile has been opened for (output; PreReq is created,
		//            and its top item is the "target course" for (which the rest
		//            of the items on the stack are prerequisites
		// checks : none
	{
		stack<int> reverse;

		OutFile << "The sequence of courses to take before " << prerex.top() << " is: ";
		prerex.pop();
		OutFile << endl << "\t";

		while (!(prerex.empty()))
		{
			reverse.push(prerex.top());
			prerex.pop();
		}

		while (!(reverse.empty()))
		{
			OutFile << reverse.top() << "   ";
			reverse.pop();
		}
		OutFile << endl << "in that order.";
	}