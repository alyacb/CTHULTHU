#include <iostream>
#include "test.h"

using namespace std;

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  See test.h for documentation.
 *
 ******************************************************************/

void printIfDebug(string desc){
	#ifdef DEBUG
	cout << desc << endl;
	#endif
}

void printIfDebug(unsigned int num, string desc){
	#ifdef DEBUG
        cout << "      [" << (char)('a' + num) << "] -- " << desc << endl;
        #endif
}

void runAllTests(){
        unsigned int numPassed = 0;
	unsigned int i = 0;
        while(testArray[i] != NULL){
                cout << '[' << (i+1) << "]   -   Testing "
                     << testNames[i] << "...   ";
                try {
			#ifdef DEBUG
			cout << endl;
			#endif
                        bool passed = testArray[i]();
                        cout << (passed ? "passed" : "failed") << '.';
			if(passed) { numPassed++; }
                } catch(exception &e) {
                        cout << "failed with exception: " << e.what();
                }
                cout << endl;
		i++;
        }

	cout << numPassed << '/' << i << " tests passed." << endl;
}
