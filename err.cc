#include "matrix.h"
#include "err.h"
#include "util.h"

#include <exception>
#include <string>
#include <sstream>

using namespace std;

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  See err.h for documentation.
 *
 ******************************************************************/

void report(const string *message) {
	throw invalid_argument(*message);
}

// MATRIX
const string SQUARE_MATRIX = "Input matrix must be square.";
const string SAME_DIM_MATRIX = "Input matrices must have the same dimensions.";
const string MULT_DIM_MATRIX = "Input matrices do not have dimensions compatible for multiplication.";
const string HESS_MATRIX = "Input matrix must be Hessenberg.";

void assertSquare(const Matrix &M) {
	if(M.width != M.height) {
		report(&SQUARE_MATRIX);
	}
}

void assertEqualDims(const Matrix &M1, const Matrix &M2) {
	if(M1.width != M2.width || M1.height != M2.height) {
		report(&SAME_DIM_MATRIX);
	}
}

void assertTransposeDims(const Matrix &M1, const Matrix &M2) {
        if(M1.width != M2.height || M1.height != M2.width) {
                report(&SAME_DIM_MATRIX);
        }
}

void assertEqualDims(const Matrix &M1, const Matrix &M2, const Matrix &M3) {
	assertEqualDims(M1, M2);
	assertEqualDims(M2, M3);
}

void assertCanMultiply(const Matrix &M1, const Matrix &M2, const Matrix &M3) {
	if(M1.width != M2.height || M1.height != M3.height || M2.width != M3.width) {
		report(&MULT_DIM_MATRIX);
	}
}

void assertHessenberg(Matrix &M) {
	if(!M.isHessenberg()) {
		report(&HESS_MATRIX);
	}
}

// DOUBLE

const string EXPECTED = "expected: ";
const string ACTUAL = "actual: ";
const string EQUAL_DOUBLES = "Should be equal- ";
const string UNEQUAL_DOUBLES = "Should not be equal- ";

void doubleReport(const string *message, double expected, double actual) {
//	string s = *message + EXPECTED + to_string(expected) + " , " + ACTUAL + to_string(actual);

//	report(&s);
}

void assertDoubleEquals(double expected, double actual) {
	if(!doubleEquals(expected, actual)) {
		doubleReport(&EQUAL_DOUBLES, expected, actual);
	}
}

void assertDoubleNotEquals(double expected, double actual) {
        if(doubleEquals(expected, actual)) {
                doubleReport(&UNEQUAL_DOUBLES, expected, actual);
        }
}

void assertDoubleEquals(double expected, double actual, double cutoff) {
        if(!doubleEquals(expected, actual, cutoff)) {
                doubleReport(&EQUAL_DOUBLES, expected, actual);
        }
}

void assertDoubleNotEquals(double expected, double actual, double cutoff) {
        if(doubleEquals(expected, actual, cutoff)) {
                doubleReport(&UNEQUAL_DOUBLES, expected, actual);
        }
}
