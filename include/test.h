#ifndef ___CTHULTHU__TESTS_ACB___
#define ___CTHULTHU__TESTS_ACB___

#include <string>

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  A header for testing implementations that form CTHULTHU.
 *
 *  Implementation in:
 *  - test.cc (for all tests)
 *  - test_matrix.cc (for matrix tests)
 *  - test_var.cc (for test variables)
 *
 ******************************************************************/

void runAllTests();

void printIfDebug(unsigned int num, std::string desc);

// Matrix tests
bool matrixTestInputOutput();
bool matrixTestEquality();
bool matrixTestGetLength();
bool matrixTestTranspose();
bool matrixTestZeroFill();
bool matrixTestZeroFillWithCoordinates();
bool matrixTestUnit();
bool matrixTestAdd();
bool matrixTestSubtract();
bool matrixTestScalarMultiply();
bool matrixTestDotProduct();
bool matrixTestMultiply();
bool matrixTestIsHessenberg();
bool matrixTestIsTriangular();
bool matrixTestIsDiagonal();
bool matrixTestGenerateHessenberg();
bool matrixTestTriangularization();

/////////////////////////////////////////////

typedef bool (*testFunction) ();

// array of test functions
extern testFunction testArray[];

// test descriptions
extern std::string testNames[];

#endif
