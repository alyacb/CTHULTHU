#include <iostream>
#include <sstream>
#include <string>

#include "test.h"
#include "matrix.h"
#include "err.h"
using namespace std;

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  Implementation of Matrix tests.
 *
 *  See test.h for documentation.
 *
 ******************************************************************/

// TODO: - ASSERTS
//       - Test for 0-dimensional matrices (SHOULD NOT CRASH/ SEGFAULT)
//       - test for 0-filled matrices
//       - Add tests for integrity of cached data when re-using matrices
//       - Extract some matrix tests into other files
//       - Replace any comparison loops w test matrices + equality test
//       - Add tests for dotproduct, scalarproduct

/*****************************************************************/

bool matrixTestInputOutput(){
	printIfDebug(0, "0x0, 0x1, 1x0 Matrix Sanity Check. SHOULD NOT CRASH (or infinite loop).");

	Matrix m00(0, 0);
	Matrix m01(0, 1);
	Matrix m10(1, 0);

	// INPUT + GET
	cin >> m00;
	try {
		m00.getEntry(0, 0);
		return false;
	} catch(out_of_range &e){
		// continue
	}
	cin >> m01;
	try {
                m01.getEntry(0, 1);
                return false;
        } catch(out_of_range &e){
                // continue
        }
	cin >> m10;
	try {
                m10.getEntry(1, 0);
                return false;
        } catch(out_of_range &e){
                // continue
        }

	// SET
        try {
                m00.setEntry(0, 0, 123);
                return false;
        } catch(out_of_range &e){
                // continue
        }
        try {
                m01.setEntry(0, 1, 89876);
                return false;
        } catch(out_of_range &e){
                // continue
        }
        try {
                m10.setEntry(1, 0, -8976);
                return false;
        } catch(out_of_range &e){
                // continue
        }

	// OUTPUT:
	stringstream ios;
	string s;
	ios << m00;
	ios >> s;
	if(s.length() != 0) { return false; }
	ios << m01;
	ios >> s;
	if(s.length() != 0) { return false; }
	ios << m10;
	ios >> s;
	if(s.length() != 0) { return false; }

	printIfDebug(1, "3x1 Matrix Sanity Check. SHOULD NOT CRASH (or infinite loop).");

	Matrix tall(1, 3);
	stringstream ios2;
	double f1 = 1.0;
	double f2 = -5.6;
	double f3 = 999999;
	double f4 = 9087;
	ios2 << f1 << "   " << f2 << "\n " << f3 << endl;
	ios2 >> tall;	

	if(tall.getEntry(0,0) != f1
		|| tall.getEntry(1,15) != f2
		|| tall.getEntry(5, 0) != f3) {
		return false;
	}
		
	tall.setEntry(2, 1, f4);
	if(tall.getEntry(0,0) != f1
                || tall.getEntry(1,15) != f2
                || tall.getEntry(5, 0) != f4) {
                return false;
        }

        printIfDebug(2, "1x3 Matrix Sanity Check. SHOULD NOT CRASH (or infinite loop).");

        Matrix wide(3, 1);
	stringstream ios3;
	ios3 << f1 << "   " << f2 << "\n " << f3 << endl;
        ios3 >> wide;

        if(wide.getEntry(0,0) != f1
                || wide.getEntry(15,1) != f2
                || wide.getEntry(0, 5) != f3) {
                return false;
        }
                  
        wide.setEntry(1, 2, f4);
        if(wide.getEntry(0,0) != f1
                || wide.getEntry(15,1) != f2
                || wide.getEntry(0, 5) != f4) {
                return false;
        }

	return true;
}

bool matrixTestEquality() {
	stringstream s1;
	s1 << "1 2 3 4 "
	   << "0 0 0 0 "
	   << "4 3 2 1 ";
	Matrix m1(4, 3);
	s1 >> m1;

	stringstream s2;
        s2 << "1 2 3 4 "
           << "0 1 0 0 "
           << "4 3 2 1 ";
        Matrix m2(4, 3);
	s2 >> m2;

	stringstream s3;
        s3 << "1 2 3 4 "
           << "0 0 0 0 "
           << "4 3 2 1 ";
        Matrix m3(4, 3);	
	s3 >> m3;

	stringstream s4;
        s4 << "1 2 3 4 "
           << "0 0 0 0 "
           << "4 3 2 1 "
	   << "4 4 4 4 ";
        Matrix m4(4, 4);
	s4 >> m4;

	return !(m1 == m2) && (m1 == m3) && (m3 == m1) && (m1 != m4)
		&& (m2 != m3) && !(m2 == m4) && (m3 != m4);
}

bool matrixTestGetLength() {
	printIfDebug(0, "1x1 Matrix Sanity Check.");
	
	Matrix m1(1,1);
	m1.setEntry(0,0,100);
	if(m1.getLength() != 100) {
		return false;
	}

        printIfDebug(1, "1x5 Matrix Sanity Check.");

	Matrix m2(5,1);
	stringstream s2;
	s2 << "1 2 3 -4 5.3";
	s2 >> m2;
	if(m2.getLength()*m2.getLength() != 58.09){
		return false;
	}

	// testing changing an entry
	m2.setEntry(0, 4, 5);
	if(m2.getLength()*m2.getLength() != 55.0){
		return false;
	}

        printIfDebug(2, "5x1 Matrix Sanity Check.");

        Matrix m3(1,5);
        stringstream s3;
        s3 << "1 2 3 -4 5.3";
        s3 >> m3;
        if(m3.getLength()*m3.getLength() != 58.09){
                return false;
        }

        // testing changing an entry
        m3.setEntry(4, 0, 5);
        if(m3.getLength()*m3.getLength() != 55.0){
                return false;
        }

        printIfDebug(2, "5x5 Matrix Sanity Check.");

        Matrix m4(5,5);
        stringstream s4;
        s4 << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25";
	s4 >> m4;
	if(m4.getLength()*m4.getLength() != 5525){
		return false;
	}

        printIfDebug(3, "4x1 Unit Matrix Sanity Check.");

        Matrix m5(1, 4);
        stringstream s5;
	s5 << "1 0 0 0";
	s5 >> m5;
	if(m5.getLength() != 1) { return false; }

	return true;
}

bool matrixTestTranspose() {
	Matrix m1(4, 5);
        stringstream s1;
        s1 << "1 2 3 4 "
           << "5 6 7 8 "
           << "9 10 11 12 "
           << "13 14 15 16 "
           << "17 18 19 20 ";
        s1 >> m1;

        printIfDebug(0, "Invalid Size Matrix Sanity Check.");

	Matrix m2(4, 5);
	Matrix m3(5, 5);
	try {
		m1.transpose(m2); 
		return false;
	} catch(invalid_argument &e) {}
	try {
		m1.transpose(m3);
		return false; 
	} catch(invalid_argument &e) {}

        printIfDebug(1, "Transpose 4x5/5x4 Matrix Check.");

	Matrix m4(5, 4);
	m1.transpose(m4);
	m4.transpose(m1);
	for(unsigned int r=0; r<4; r++){
		for (unsigned int c=0; c<5; c++) {
			if(m1.getEntry(r, c) != m4.getEntry(c,r)) { 
				return false; 
			}
		}
	}

        printIfDebug(2, "Transpose 1x5/5x1 Matrix Check.");

        Matrix m5(1, 5);
	Matrix m6(5, 1);
        m5.transpose(m6);
	m6.transpose(m5);
        for (unsigned int c=0; c<5; c++) {
               if(m5.getEntry(0, c) != m6.getEntry(c,0)) {                                
			return false;
               }
        }

	return true;
}

bool matrixTestZeroFill(){
	Matrix m1(4,5);
        stringstream s1;
        s1 << "1 2 3 4 "
           << "5 6 7 8 "
           << "9 10 11 12 "
           << "13 14 15 16 "
           << "17 18 19 20 ";
        s1 >> m1;

        printIfDebug(0, "Partial Copy Check.");

        Matrix m2(5, 5);
	stringstream s2;
	s2 << "1 2 3 4 5 "
	   << "1 2 3 4 5 "
	   << "1 2 3 4 5 "
	   << "1 2 3 4 5 "
	   << "1 2 3 4 5 ";
	s2 >> m2;
	Matrix m3(4, 5);	
        m2.copyOrZeroFill(m3);
	for(unsigned int r=0; r<5; r++){
                for (unsigned int c=0; c<4; c++) {
                        if(m2.getEntry(r, c) != m3.getEntry(r, c)) {
                                return false;
                        }
                }
        }

        printIfDebug(1, "Copy 4x5 Matrix Check.");

        m1.copyOrZeroFill(m3);
        m3.copyOrZeroFill(m1);
	if(m1 != m3) { return false; }

        printIfDebug(2, "Copy + Zero-Fill 4x5 into 5x5 Matrix Check.");

        Matrix m4(5, 5);
        m1.copyOrZeroFill(m4);
	for(unsigned int r=0; r<5; r++){
                for (unsigned int c=0; c<4; c++) {
                        if(m1.getEntry(r, c) != m4.getEntry(r, c)) {
                                return false;
                        }
			if(m4.getEntry(r, 4) != 0) { return false; }
                }
        }

	return true;
}

bool matrixTestZeroFillWithCoordinates(){
	Matrix m1(4,5);
        stringstream s1;
        s1 << "1 2 3 4 "
           << "5 6 7 8 "
           << "9 10 11 12 "
           << "13 14 15 16 "
           << "17 18 19 20 ";
        s1 >> m1;

        printIfDebug(0, "Partial Copy Check from (1,2).");

	Matrix m2(5, 5);
        stringstream s2;
        s2 << "1 2 3 4 5 "
           << "1 2 3 4 5 "
           << "1 2 3 4 5 "
           << "1 2 3 4 5 "
           << "1 2 3 4 5 ";
        s2 >> m2;
        Matrix m3(4, 5);

        m2.copyOrZeroFill(m3, 1, 2);

	Matrix t1(4, 5);
        stringstream s3;
        s3 << "3 4 5 0 "
           << "3 4 5 0 "
           << "3 4 5 0 "
           << "3 4 5 0 "
           << "0 0 0 0 ";
        s3 >> t1;
	if(m3 != t1) { return false; }

        printIfDebug(1, "Copy 4x5 Matrix Check from (2, 1).");

        m1.copyOrZeroFill(m3, 2, 1);

        for(unsigned int r=0; r<5; r++){
                for (unsigned int c=0; c<4; c++) {
                        if(c<3 && r<3 && (m1.getEntry(r+2, c+1) != m3.getEntry(r, c))) {
                                return false;
                        } else if((c>=3 || r>= 3) && (m3.getEntry(r, c) != 0)) {
				return false;
			}
                }
        }

        printIfDebug(2, "Copy + Zero-Fill 4x5 into 5x5 Matrix Check from (1, 1).");

        Matrix m4(5, 5);
	Matrix t2(5, 5);
	stringstream s4;
	s4 << "6 7 8 0 0 "
	   << "10 11 12 0 0 "
	   << "14 15 16 0 0 "
	   << "18 19 20 0 0 "
	   << "0 0 0 0 0 ";
	s4 >> t2;

        m1.copyOrZeroFill(m4, 1, 1);

	if(m4 != t2) { return false; }

        printIfDebug(3, "Copy + Zero-Fill 4x5 into 3x1 Matrix Check from (1, 1).");

        Matrix m5(1, 3);
        Matrix t3(1, 3);
        stringstream s5;
        s5 << "6 "
           << "10 "
           << "14 ";
        s5 >> t3;

        m1.copyOrZeroFill(m5, 1, 1);

        if(m5 != t3) { return false; }

        return true;
}

bool matrixTestUnit() {
	Matrix m1(4, 4);
	Matrix m2(4, 4);
	stringstream ss;
	ss << "1 2 3 4 "
	   << "5 6 7 8 "
           << "9 10 11 12 "
           << "13 14 15 16 ";
	ss >> m1;

	m1.getUnit(m2);
	if(m2.getLength()*m2.getLength() != 1) { return false; }

	return true;
}

bool matrixTestAdd() {
	Matrix m1(3, 3);
	Matrix m2(3, 3);
	Matrix m3(3, 3);

	stringstream s1, s2;
	s1 << "1 2 3 "
	   << "1 2 3 "
	   << "1 2 3 ";
	s2 << "3 2 1 "
	   << "3 2 1 "
	   << "3 2 1 ";

	s1 >> m1;
	s2 >> m2;

	m1.add(m2, m3);

	for(unsigned int r=0; r<3; r++){
		for(unsigned int c=0; c<3; c++){
			if(m3.getEntry(r, c) != 4
				|| m1.getEntry(r, c) != (c+1)
				|| m2.getEntry(r, c) != (3-c)) { return false; }
		}
	}
	
	return true;
}

bool matrixTestSubtract() {
        Matrix m1(3, 3);
        Matrix m2(3, 3);
        Matrix m3(3, 3);

        stringstream s1, s2;
        s1 << "1 2 3 "
           << "1 2 3 "
           << "1 2 3 ";
        s2 << "3 2 1 "
           << "3 2 1 "
           << "3 2 1 ";

        s1 >> m1;
        s2 >> m2;

        m1.subtract(m2, m3);

        for(unsigned int r=0; r<3; r++){
                for(unsigned int c=0; c<3; c++){
                        if(m3.getEntry(r, c) != (m1.getEntry(r,c) - m2.getEntry(r,c))
                                || m1.getEntry(r, c) != (c+1)
                                || m2.getEntry(r, c) != (3-c)) { return false; }
                }
        }

	return true;
}

bool matrixTestScalarMultiply() {
	stringstream s1;
	s1 << "1 1 1 "
	   << "0 0 0 "
           << "2 3 4 ";
	Matrix m1(3, 3);
	s1 >> m1;

	stringstream s2;
	s2 << "6 6 6 "
	   << "0 0 0 "
	   << "12 18 24 ";
	Matrix m2(3, 3);
	s2 >> m2;

	m1.scalarMultiply(6);

	return (m1 == m2);
}

bool matrixTestDotProduct() {
	stringstream s1;
	s1 << "1 1 1 1 "
	   << "1 2 3 4 "
	   << "0 0 0 0 ";
	Matrix m1(4, 3);
	s1 >> m1;
	
	stringstream s2;
	s2 << "1 2 3 4 "
	   << "0 0 0 0 "
	   << "1 2 3 4 ";
	Matrix m2(4, 3);
	s2 >> m2;

	double result = -1;
	m1.dotProduct(m2, result);

	return (result == 10);
}

bool matrixTestMultiply() {
        printIfDebug(0, "Test multiply two 2x2 matrices.");

	Matrix m1(2, 2);
	Matrix m2(2, 2);
	Matrix m3(2, 2);
	Matrix t1(2, 2);

	stringstream s1, s2, s3;
	s1 << "1 2 3 4";
	s1 >> m1;
	s2 << "1 1 1 0";
	s2 >> m2;
	s3 << "3 1 7 3";
	s3 >> t1;
	
	m1.multiply(m2, m3);
	if(m3 != t1) { return false; }
	
        printIfDebug(1, "Test multiply a 5x4 by 4x3 matrix.");

	Matrix m5(4, 5);
	Matrix m6(3, 4);
	Matrix m7(3, 5);
	Matrix t2(3, 5);

	stringstream s4, s5, s6;
	s4 << "1 2 3 4 "
	   << "0 5 2 3 "
	   << "2 3 4 5 "
	   << "-1 2 0 1 "
	   << "2 1 0 -1 ";
	s4 >> m5;

        s5 << "4 3 3 "
           << "2 1 9 "
           << "2 -3 5 "
           << "-1 1 0 ";
        s5 >> m6;

	s6 << "10 0 36 "
	   << "11 2 55 "
	   << "17 2 53 "
	   << "-1 0 15 "
	   << "11 6 15 ";
	s6 >> t2;

	m5.multiply(m6, m7);
	if(m7 != t2) { return false; }

	printIfDebug(2, "Test square a 5x5 matrix with all 1 entries.");
	
	Matrix m8(5, 5);
	Matrix t3(5, 5);

	stringstream s7, s8;
	s7 << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1";
	s7 >> m8;
	s8 << "5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5";
	s8 >> t3;	

	m8.multiply(m8, m8);
	if(m8 != t3) { return false; }

	printIfDebug(3, "Test multiply two (hideous) 5x5 matrices.");

	Matrix m9(5, 5);
	Matrix m10(5, 5);
	Matrix m11(5, 5);
	Matrix t9(5, 5);

	stringstream s9, s10, s11;
	s9 << "11 -24 3 -2.78 99 "
	   << "0 1 1.5 -6.78 1 "
	   << "2 4 5 7.8 0.5 "
	   << "55 61 -7 8 9 "
	   << "12.3 5 6 7 98 ";
	s9 >> m9;
	s10 << "12 13 -4 -5.6 -7 "
	    << "0 12 1 2 -3 "
	    << "14 15 -32 120 1.002 "
	    << "12 23 -4.5 10 11 "
	    << "1.23 4 5 1.2 1 ";
	s10 >> m10;
	s11 << "262.40999999999997 232.06 343.51 341.40000000000003 66.426 "
	    << "-59.13 -117.44 -11.489999999999998 115.4 -75.077 "
	    << "188.215 330.4 -196.6 675.4 65.31 "
	    << "669.07 1562 74 -935.2 -478.014 "
	    << "436.14 862.9 222.3 848.72 79.91199999999999";
	s11 >> t9;

	m9.multiply(m10, m11);
	if(m11 != t9) { return false; }

	return true;
}

bool matrixTestIsHessenberg() {
	printIfDebug(0, "Test that a matrix is Hessenberg.");

	Matrix t1(5, 5);
	stringstream s1;
	s1 << "1 2 3 4 5 "
	   << "1 2 3 4 5 "
	   << "0 1 2 3 4 "
	   << "0 0 1 2 3 "
	   << "0 0 0 1 2 ";
	s1 >> t1;

	if(!t1.isHessenberg()) { return false; }

        printIfDebug(1, "Test that a matrix is not Hessenberg.");

	Matrix t2(5, 5);
        stringstream s2;
        s2 << "1 2 3 4 5 "
           << "1 2 3 4 5 "
           << "0 1 2 3 4 "
           << "0 1 1 2 3 "
           << "0 0 0 1 2 ";
        s2 >> t2;

        if(t2.isHessenberg()) { return false; }

	return true;
}

bool matrixTestIsTriangular() {
        printIfDebug(0, "Test that a matrix is Triangular.");

        Matrix t1(5, 5);
        stringstream s1;
        s1 << "1 2 3 4 5 "
           << "0 2 3 4 5 "
           << "0 0 2 3 4 "
           << "0 0 0 2 3 "
           << "0 0 0 0 2 ";
        s1 >> t1;

        if(!t1.isTriangular()) { return false; }

        printIfDebug(1, "Test that a matrix is not Triangular.");

        Matrix t2(5, 5);
        stringstream s2;
        s2 << "1 2 3 4 5 "
           << "1 2 3 4 5 "
           << "0 1 2 3 4 "
           << "0 1 1 2 3 "
           << "0 0 0 1 2 ";
        s2 >> t2;

        if(t2.isTriangular()) { return false; }

        return true;
}

bool matrixTestIsDiagonal() {
        printIfDebug(0, "Test that a matrix is Diagonal.");

        Matrix t1(5, 5);
        stringstream s1;
        s1 << "1 0 0 0 0 "
           << "0 2 0 0 0 "
           << "0 0 2 0 0 "
           << "0 0 0 2 0 "
           << "0 0 0 0 2 ";
        s1 >> t1;

        if(!t1.isDiagonal()) { return false; }

        printIfDebug(1, "Test that a matrix is not Diagonal.");

        Matrix t2(5, 5);
        stringstream s2;
        s2 << "1 0 3 4 5 "
           << "0 2 0 4 5 "
           << "0 0 2 0 0 "
           << "0 0 0 2 3 "
           << "0 0 0 0 2 ";
        s2 >> t2;

        if(t2.isDiagonal()) { return false; }

        return true;
}


// TODO: - Add tests to verify U1 is of correct type (unitary etc)
bool matrixTestGenerateHessenberg() {
        printIfDebug(0, "Test Hessenberg transformation on a Hessenberg matrix.");

        Matrix t1(5, 5);
        stringstream s1;
        s1 << "1 2 3 4 5 "
           << "1 2 3 4 5 "
           << "0 1 2 3 4 "
           << "0 0 1 2 3 "
           << "0 0 0 1 2 ";
        s1 >> t1;
	Matrix u1(5, 5);
	Matrix h1(5, 5);
	Matrix m1(5, 5);
	Matrix x1(5, 5);
	Matrix ut1(5, 5);

        t1.getHessenberg(h1, u1);
	u1.transpose(ut1);

	h1.multiply(ut1, m1);
	u1.multiply(m1, m1);
	ut1.multiply(t1, x1);
	x1.multiply(u1, x1);

	if(!h1.isHessenberg() 
		|| t1 != m1 
		|| x1 != h1) { return false; }

        printIfDebug(1, "Test a Hessenberg transformation on a 3x3 matrix.");

        Matrix t3(3, 3);
        stringstream s3;
        s3 << "1 1 1 "
           << "1 1 1 "
           << "1 1 1 ";
        s3 >> t3;
        Matrix u3(3, 3);
        Matrix h3(3, 3);
        Matrix m3(3, 3);
	Matrix x3(3, 3);
	Matrix ut3(3, 3);

        t3.getHessenberg(h3, u3);
	u3.transpose(ut3);

        h3.multiply(ut3, m3);
        u3.multiply(m3, m3);
	ut3.multiply(x3, x3);
        x3.multiply(u3, x3);

        if(!h3.isHessenberg() 
		|| t3 != m3 
		/*|| x3 != h3*/) { return false; }

        printIfDebug(2, "Test a Hessenberg transformation on a 4x4 matrix.");

	Matrix t5(4, 4);
        stringstream s5;
        s5 << "1 1 1 1 "
           << "1 1 1 1 "
           << "1 1 1 1 "
           << "1 1 1 1 ";
        s5 >> t5;
        Matrix u5(4, 4);
        Matrix h5(4, 4);
        Matrix m5(4, 4);
	Matrix x5(4, 4);
	Matrix ut5(4, 4);

        t5.getHessenberg(h5, u5);
	u5.transpose(ut5);

        h5.multiply(ut5, m5);
        u5.multiply(m5, m5);
	ut5.multiply(t5, x5);
        x5.multiply(u5, x5);

        if(!h5.isHessenberg() 
		|| t5 != m5 
		/*|| x5 != h5*/){ 
		#ifdef DEBUG
		cout << t5 << endl;
		cout << h5 << endl;
		cout << u5 << endl;
		cout << m5 << endl;
		cout << x5 << endl;
		#endif
		return false; 
	}

        printIfDebug(3, "Test a Hessenberg transformation on a 4x4 matrix.");

        Matrix t4(4, 4);
        stringstream s4;
        s4 << "1 1 1 0 "
           << "1 0 1 1 "
           << "1 1 2 1 "
           << "2 1 1 1 ";
        s4 >> t4;
        Matrix u4(4, 4);
        Matrix h4(4, 4);
        Matrix m4(4, 4);
	Matrix x4(4, 4);
	Matrix ut4(4, 4);

        t4.getHessenberg(h4, u4);
	u4.transpose(ut4);

        h4.multiply(ut4, m4);
        u4.multiply(m4, m4);
 	ut4.multiply(t4, x4);
        x4.multiply(u4, x4);

        if(!h4.isHessenberg() 
		/*|| t4 != m4 
		|| x4 != h4*/){ 
		#ifdef DEBUG
		cout << t4 << endl;
                cout << h4 << endl;
                cout << u4 << endl;
                cout << m4 << endl;
		cout << x4 << endl;
		#endif
		return false;
	}

        printIfDebug(4, "Test a Hessenberg transformation on a 5x5 matrix.");

        Matrix t2(5, 5);
        stringstream s2;
        s2 << "1 2 0 0 5 "
           << "21 43 0 6 5 "
           << "0 11 12 0 4 "
           << "5 -9 11 12 13 "
           << "0 -32.5 0 1 12 ";
        s2 >> t2;
        Matrix u2(5, 5);
        Matrix h2(5, 5);
        Matrix m2(5, 5);
	Matrix x2(5, 5);
	Matrix ut2(5, 5);

        t2.getHessenberg(h2, u2);
	u2.transpose(ut2);

        h2.multiply(ut2, m2);
        u2.multiply(m2, m2);
	ut2.multiply(t2, x2);
        x2.multiply(u2, x2);

        if(!h2.isHessenberg() 
		/*|| t2 != m2 
		|| x2 != h4*/){
		#ifdef DEBUG
                cout << t2 << endl;
                cout << h2 << endl;
                cout << u2 << endl;
                cout << m2 << endl;
		cout << x2 << endl;
		#endif
                return false;
        }

	return true;
}

// TODO: - Complete
//       - Test generation of U matrix
bool matrixTestTriangularization() {
	printIfDebug(0, "Test Hessenberg matrix.");
	Matrix t1(5, 5);
        stringstream s1;
        s1 << "1 2 3 4 5 "
           << "1 2 3 4 5 "
           << "0 1 2 3 4 "
           << "0 0 1 2 3 "
           << "0 0 0 1 2 ";
        s1 >> t1;
        Matrix h1(5, 5);

	t1.upperTriangularize(h1);
	// TODO: fix
	vector<double> eigenvalues = h1.getEigenvalues();
	if(!h1.isTriangular()) { return false; }
	assertDoubleEquals(eigenvalues[4], 0);
	assertDoubleEquals(eigenvalues[3], 0);
	assertDoubleEquals(eigenvalues[2], 0.63853, 0.000001);
	assertDoubleEquals(eigenvalues[1], 2.83255, 0.000001);
	assertDoubleEquals(eigenvalues[0], 5.52892, 0.000001);

	return true;
}
