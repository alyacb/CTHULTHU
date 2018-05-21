#include <math.h>
#include <iostream>
#include "matrix.h"
#include "err.h"

using namespace std;

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  Matrix methods implementation. 
 *  
 *  See matrix.h for documentation.
 *
 ******************************************************************/

// Algorithm: Reduction to Hessenberg Form
// TODO: - INPUT MUST BE SQUARE
// 	 - Improve efficiency/ memory reuse
void Matrix::getHessenberg(Matrix &H, Matrix &U) const {
	assertEqualDims(*this, H, U);

	unsigned int n = width;
        copyOrZeroFill(H);
	getIdentity(U);

        for(unsigned int k=0; k<n-2; k++){
                Matrix u(1, n - k - 1);

                H.copyOrZeroFill(u, k + 1, k);

                double magnitude = u.getLength();

                if(magnitude == 0){ continue; }
                double alpha = signbit(u.getEntry(0,0)) ? magnitude : -magnitude;
                u.setEntry(0, 0, u.getEntry(0,0) - alpha);
		magnitude = u.getLengthSquared(); // squared length of u, for use later		

		Matrix u_t(n - k - 1, 1);
		u.transpose(u_t);

		// Finding the hessenberg matrix H
		Matrix A(n - k, n - k - 1); // H(k+1, k) -> (n, n)
		H.copyOrZeroFill(A, k + 1, k);

		Matrix B(n - k, 1); // u_t * A
		u_t.multiply(A, B);

		// C = 2(u * B)
		Matrix C(n - k, n - k - 1);
		u.multiply(B, C);
		// instead of making u unit, we divide by |u|^2 here
		C.scalarMultiply(2.0/magnitude);

		// C = A - C
		A.subtract(C, C);

		// H(k+1, k) -> (n, n)
		C.copyOrZeroFill(H, 0, 0, k + 1, k);

		// D = H(1, k+1) -> (n, n)
		Matrix D(n - k - 1, n);
		H.copyOrZeroFill(D, 0, k + 1);

		Matrix s(1, n); // s = D * u
		D.multiply(u, s);

		Matrix E(n - k - 1, n); // E = 2 * s * u_t 
		s.multiply(u_t, E);
		// instead of making u unit, we divide by |u|^2 here
		E.scalarMultiply(2.0/magnitude);

		// D = D - E
		D.subtract(E, D);

		D.copyOrZeroFill(H, 0, 0, 0, k + 1);

		// TODO: FIX... (or remove?)
		// Finding the unitary matrix U
		// F = 2 u * u_t
		Matrix F(n - k - 1, n - k - 1);
		u.multiply(u_t, F);
		// instead of making u unit, we divide by |u|^2 here
		F.scalarMultiply(2.0/magnitude);

		// F = I - F
                Matrix G(n - k - 1, n - k - 1);	
		getIdentity(G);
		G.subtract(F, F);

		// J = U(k+1, k+1) -> (n, n)
                Matrix J(n - k - 1, n - k -1);
                U.copyOrZeroFill(J, k+1, k+1);

		// J = J * F
		J.multiply(F, J);

		J.copyOrZeroFill(U, 0, 0, k + 1, k + 1);
        }

	H.setHessenberg(true);
}

// TODO: find Q
void Matrix::doHessenbergQRStep(Matrix &Q, Matrix &R) const {
	assertEqualDims(Q, R, *this);
	assertSquare(*this);

	unsigned int n=width;
	if(n == 0) { return; }

	double *c = new double[n-1];
	double *s = new double[n-1];
	double *r = new double[n-1];

	Matrix twoRows(n, 2);
	Matrix twoColumns(2, n);
	Matrix S(2,2);

	copyOrZeroFill(R);

	assertHessenberg(R);

	for(unsigned int i=0; i<n-1; i++) {
		R.copy(twoRows, i, 0);

		c[i] = R.getEntry(i, i);
		s[i] = R.getEntry(i+1, i);
		cout << c[i] << " " << s[i] << endl;
		r[i] = sqrt(c[i]*c[i] + s[i]*s[i]);

		if(r[i] != 0) {
			c[i] /= r[i];
			s[i] /= r[i];
		}

		S.setEntry(0, 0, c[i]);
		S.setEntry(0, 1, s[i]);
		S.setEntry(1, 0, -s[i]);
		S.setEntry(1, 1, c[i]);

		cout << twoRows << endl;
		cout << S << endl;

		S.multiply(twoRows, twoRows);

		cout << twoRows << endl;

		twoRows.copy(R, 0, 0, i, 0);

		cout << R << endl;
	}

	cout << "row done" << endl;

	for(unsigned int i=0; i<n-1; i++){
		R.copy(twoColumns, 0, i);

		S.setEntry(0, 0, c[i]);
                S.setEntry(0, 1, -s[i]);
                S.setEntry(1, 0, s[i]);
                S.setEntry(1, 1, c[i]);

		cout << twoColumns << endl;
		cout << S << endl;

                twoColumns.multiply(S, twoColumns);

		cout << twoColumns << endl;

                twoColumns.copy(R, 0, 0, 0, i);

		cout << R << endl;
	}

	cout << "col done" << endl;

	delete[] c;
	delete[] s;
	delete[] r;
}

// TODO: - Implement QR-Algorithm
//       - Find matrix orthogonal multiplicand (Q)
void Matrix::upperTriangularize(Matrix &T) const {
	assertEqualDims(T, *this);
	assertSquare(T);

	unsigned int n=width;
	if(n == 0) { return; }

	Matrix uselessForNow(n, n);   
	copyOrZeroFill(T);

	if(T.isTriangular()) { return; }

	if(!T.isHessenberg()) {
		T.getHessenberg(T, uselessForNow);	
	}

	// NTS: this will yield RIDICULOUS runtimes.
	// Thus, adding ARBITRARY upper bound on iterations.
	unsigned int count = 0;
	while(!T.isTriangular() && count < 100){
		for(unsigned int i=0; i<n-1; i++){
			cout << T << endl;
			T.doHessenbergQRStep(uselessForNow, T);
		}
		count++;
	}

	#ifdef DEBUG // TODO: better way of logging #iterations taken
	cout << "Square matrix of side " << n  << " took "<< count << " iterations to triangularize." << endl;
	#endif

	T.setTriangular(true);
}

// TODO: - Store eigenvectors as basis for eigenspace
//       - better way of storing eigenvalues
//       - nullcheck @ new
//       - REMOVE
void Matrix::classifyMatrixAndGenerateEigenvalues() {
        if(classy != UNKNOWN) { return; }

        num_eigenvalues = (width < height) ? width : height;
        eigenvalues = new double[num_eigenvalues];
        Matrix R(num_eigenvalues, num_eigenvalues);

        copyOrZeroFill(R);
        upperTriangularize(R);

        for(unsigned int k=0; k<num_eigenvalues; k++){
                eigenvalues[k] = R.entries[k][k];
        }
}

MatrixClassification Matrix::getClassification(){
        classifyMatrixAndGenerateEigenvalues();
        return classy;
}
