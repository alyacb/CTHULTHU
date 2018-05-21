#ifndef ___CTHULTHU__ERR_ACB___
#define ___CTHULTHU__ERR_ACB___

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  A header for assert implementations.
 *
 *  Implementation in:
 *  - err.cc
 *
 ******************************************************************/

// matrix asserts
void assertSquare(const Matrix &M);
void assertCanMultiply(const Matrix &M1, const Matrix &M2, const Matrix &M3);
void assertTransposeDims(const Matrix &M1, const Matrix &M2);
void assertEqualDims(const Matrix &M1, const Matrix &M2);
void assertEqualDims(const Matrix &M1, const Matrix &M2, const Matrix &M3);
void assertHessenberg(Matrix &M);

// double asserts
void assertDoubleEquals(double expected, double actual);
void assertDoubleNotEquals(double expected, double actual);
void assertDoubleEquals(double expected, double actual, double cutoff);
void assertDoubleNotEquals(double expected, double actual, double cutoff);

#endif
