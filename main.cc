#include <iostream>
#include <vector>
#include "matrix.h"
#include "test.h"
using namespace std;

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  Main commandline entry-point to executing CTHULTHU
 *
 ******************************************************************/

// TODO: Modularization

int main(){
	cout << "Welcome to CTHULTHU. Enter a command to start, e.g. h for help." << endl;
	char command;
	vector<Matrix*> matrices;
	Matrix *m;
	while(cin >> command){
		switch(command) {
		   case 'a':
			unsigned int width, height;
			cin >> width;
			cin >> height;
			m = new Matrix(width, height);
			cin >> *m;
			cout << *m;
			matrices.emplace_back(m);
			break;
		   case 'h':
			cout << "Here is a list of commands:" << endl;
			cout << "[a] w h    Creates a new matrix with width w, and height h." << endl
			     << "           You must then input the entries of the matrix." << endl;
			cout << "[h]        Prints out a list of commands." << endl;
			cout << "[t]        Runs test suite." << endl;
			cout << "[q]        Quit." << endl;
			break;
		   case 't':
			cout << "Running tests..." << endl;
			runAllTests();
			break;
		   case 'q':
			return 0;
			break;
		   default:
			cout << "Unknown command. Type h for help." << endl;
		}		
	}
}
