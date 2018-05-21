#include "matrix.h"
#include "math.h"
#include "err.h"

using namespace std;

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  Matrix multiplication implementation (Strassen's Algorithm). 
 *
 *  See matrix.h for documentation.
 *
 ******************************************************************/

// Strassen's algoithm
// Requires that all of A, B, and C are nxn matrices
// where n is a power of 2
// TODO: - MINIMIZE superfluous copy operations
//       - Verify that this really is more efficient in practice than the naive approach
//       - Parallelize
void multiplySecret(Matrix &A, Matrix &B, Matrix &C) {
        unsigned int n = A.width;
        unsigned int len2 = n/2;
        unsigned int mid = len2;

	// base case
	if(n == 1) {
		C.setEntry(0, 0, B.getEntry(0, 0)*A.getEntry(0, 0));
		return;
	}

	// TODO: add 2x2 base-case

        Matrix A11(len2, len2);
        Matrix A12(len2, len2);
        Matrix A21(len2, len2);
        Matrix A22(len2, len2);
        A.copyOrZeroFill(A11);
        A.copyOrZeroFill(A12, 0, mid);
        A.copyOrZeroFill(A21, mid, 0);
        A.copyOrZeroFill(A22, mid, mid);

        Matrix B11(len2, len2);
        Matrix B12(len2, len2);
        Matrix B21(len2, len2);
        Matrix B22(len2, len2);
        B.copyOrZeroFill(B11);
        B.copyOrZeroFill(B12, 0, mid);
        B.copyOrZeroFill(B21, mid, 0);
        B.copyOrZeroFill(B22, mid, mid);

        Matrix M1(len2, len2);
        Matrix M2(len2, len2);

        // Find M1 = (A11 + A22)(B11 + B22)
        A11.add(A22, M1);
        B11.add(B22, M2);
        multiplySecret(M1, M2, M1);

        // Find M2 = (A21 + A22)B11
        A21.add(A22, M2);
        multiplySecret(M2, B11, M2);

        // Find M3 = A11(B12 - B22)
        Matrix M3(len2, len2);
        B12.subtract(B22, M3);
        multiplySecret(A11, M3, M3);

        // Find M4 = A22(B21 - B11)
        Matrix M4(len2, len2);
        B21.subtract(B11, M4);
        multiplySecret(A22, M4, M4);

        // Find M5 = (A11 + A12)B22
        Matrix M5(len2, len2);
        A11.add(A12, M5);
        multiplySecret(M5, B22, M5);

        Matrix M6(len2, len2);
        Matrix M7(len2, len2);

        // Find M6 = (A21 - A11)(B11 + B12)
        A21.subtract(A11, M6);
        B11.add(B12, M7);
        multiplySecret(M6, M7, M6);

        // Find M7 = (A12 - A22)(B21 + B22)
        A12.subtract(A22, M7);
        B21.add(B22, A11); // reusing A11
        multiplySecret(M7, A11, M7);

        // Reusing A11...A22 as C11...C22

        // Find C11 (A11) = M1 + M4 - M5 + M7
        M1.add(M4, A11);
        A11.subtract(M5, A11);
        A11.add(M7, A11);

        // Find C12 (A12) = M3 + M5
        M3.add(M5, A12);

        // Find C21 (A21) = M2 + M4
        M2.add(M4, A21);

        // Find C22 (A22) = M1 - M2 + M3 + M6
        M1.subtract(M2, A22);
        A22.add(M3, A22);
        A22.add(M6, A22);

        // Place C11, C12, C21, and C22 in C
        for(unsigned int r=0; r < n; r++) {
                for(unsigned int c=0; c < n; c++) {
                        if(r < mid && c < mid) { // C11
                                C.setEntry(r, c, A11.getEntry(r, c));
                        } else if (r < mid) { // C12
                                C.setEntry(r, c, A12.getEntry(r, c));
                        } else if (c < mid) { // C21
                                C.setEntry(r, c, A21.getEntry(r, c));
                        } else { // C22
                                C.setEntry(r, c, A22.getEntry(r, c));
                        }
                }
        }
}

// TODO: - Deal with zero-filled matrices efficiently
void Matrix::multiply(const Matrix &M, Matrix &R) const {
	assertCanMultiply(*this, M , R);
        if(len_squared == 0 || M.len_squared == 0) {
                Matrix m(0,0);
                m.copyOrZeroFill(R);
		return;
        }

        // pick the largest dimension of R, round up to a power of 2
        // TODO: Is this Efficient? in # bit ops
        unsigned int n = pow(2, ceil(log2(max(max(width, height), M.width))));

        Matrix A(n, n);
        Matrix B(n, n);
        Matrix C(n, n);

        copyOrZeroFill(A);
        M.copyOrZeroFill(B);
        multiplySecret(A, B, C);

        R.clearCachedData();

        for(unsigned int r=0; r<R.height; r++){
                for(unsigned int c=0; c<R.width; c++){
                        R.setEntry(r, c, C.entries[r][c]);
                }
        }
}
