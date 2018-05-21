#include "test.h"

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  File containing test varibale definitions.
 *
 *  See test.h for documentation.
 *
 ******************************************************************/

testFunction testArray[] = {
        matrixTestInputOutput,
        matrixTestEquality,
        matrixTestGetLength,
        matrixTestTranspose,
        matrixTestZeroFill,
        matrixTestZeroFillWithCoordinates,
        matrixTestUnit,
        matrixTestAdd,
        matrixTestSubtract,
        matrixTestScalarMultiply,
        matrixTestDotProduct,
        matrixTestMultiply,
        matrixTestIsHessenberg,
        matrixTestIsTriangular,
        matrixTestIsDiagonal,
        matrixTestGenerateHessenberg,
        matrixTestTriangularization,
        NULL
};

std::string testNames[] = {
        "matrix: input and output operators, getting entry, setting entry, and constructor",
        "matrix: equality and inequality operators",
        "matrix: get length",
        "matrix: get transpose",
        "matrix: get zero-filled matrix copy",
        "matrix: get zero-filled matrix copy from coordinates",
        "matrix: get unit",
        "matrix: addition",
        "matrix: subtraction",
        "matrix: scalar multiplication",
        "matrix: test dot product",
        "matrix: multiplication",
        "matrix: verify if Hessenberg",
        "matrix: verify if triangular",
        "matrix: verify if diagonal",
        "matrix: verify if can generate Hessenberg form",
        "matrix: verify if can generate triangular form"
};
