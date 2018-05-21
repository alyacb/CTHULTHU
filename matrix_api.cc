#include <math.h>

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

/////////////////////////// HELPERS ///////////////////////////////////////////////////

// TODO: - replace w library function
void copyDoubleArray(const double *source, double *dest, int dim){
	if(source == NULL || dest == NULL) { return; }
	for(unsigned int i=0; i<dim; i++){
		dest[i] = source[i];
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void Matrix::clearCachedData() {
        if(classy != UNKNOWN){
                classy = UNKNOWN;
                delete[] eigenvalues;
        }
	len_squared = -1; 
	secret_max = -1;
	classification = 0;
}

void Matrix::copyCachedData(Matrix &T) const {
	if(classy != UNKNOWN) {
                T.eigenvalues = new double(num_eigenvalues);
                copyDoubleArray(eigenvalues, T.eigenvalues, num_eigenvalues);
                T.classy = classy;
        } else {
                T.clearCachedData();
        }

        T.secret_max = secret_max;
        T.len_squared = len_squared;
}

// TODO: - Overload [] operator
double Matrix::getEntry(unsigned int r, unsigned int c) const {
	if(width == 0 || height == 0) { 
		throw out_of_range("A matrix with one dimension size equaling 0 has no entries."); 
	}
	return entries[r % height][c % width];
}

// TODO: - Incrementally modify cached values (as far as possible)
void Matrix::setEntry(unsigned int r, unsigned int c, double value){
	if(getEntry(r, c) != value) {
		double temp = -1;
		if(secret_max > 0) { temp = secret_max;}
		clearCachedData();
		secret_max = temp;
		entries[r % height][c % width] = value;
		double pos_value = abs(value);
		if(pos_value >= secret_max) { secret_max = pos_value; }
	}
}

// this is the standard inner product of matrices
double Matrix::getLengthSquared(){
	if(len_squared < 0) {
		len_squared = 0;
		if(secret_max == 0) {
			return 0; 
		}
		for(unsigned int r=0; r<height; r++){
			for(unsigned int c=0; c<width; c++){
				len_squared += entries[r][c]*entries[r][c]/secret_max;
			}
		}
		len_squared *= secret_max; 
	}

	return len_squared;
}

// returns sqrt of length
double Matrix::getLength(){
	return sqrt(getLengthSquared());
}

// TODO: - Ensure enough memory is available/ nullcheck @ new
void Matrix::transpose(Matrix &T) const {
	assertTransposeDims(*this, T);

	for(unsigned int r=0; r<height; r++){
		for(unsigned int c=0; c<width; c++){
			T.entries[c][r] = entries[r][c];
		}
	}

	copyCachedData(T);
}

// TODO: - Persist cached data if possible
void Matrix::copyOrZeroFill(Matrix &M, unsigned int r0, unsigned int c0, 
				       unsigned int r1, unsigned int c1) const {
        M.clearCachedData();
        unsigned int r2, c2;
        for(unsigned int r=r1; r<M.height; r++){
                for(unsigned int c=c1; c<M.width; c++){
                        r2 = r0 + r - r1;
                        c2 = c0 + c - c1;
                        if(r2 < height && c2 < width) {
                                M.setEntry(r, c, entries[r2][c2]);
                        } else {
                                M.setEntry(r, c, 0);
                        }
                }
        }
}

// TODO: - Persist cached data if possible
void Matrix::copyOrZeroFill(Matrix &M, unsigned int r0, unsigned int c0) const {
	copyOrZeroFill(M, r0, c0, 0, 0);
}

void Matrix::copyOrZeroFill(Matrix &M) const {
	copyOrZeroFill(M, 0, 0);
}

void Matrix::copy(Matrix &M, unsigned int r0, unsigned int c0,
	                     unsigned int r1, unsigned int c1) const {
	M.clearCachedData();
        unsigned int r2, c2;
        for(unsigned int r=r1; r<M.height; r++){
                for(unsigned int c=c1; c<M.width; c++){
                        r2 = r0 + r - r1;
                        c2 = c0 + c - c1;
                        if(r2 < height && c2 < width) {
                                M.setEntry(r, c, entries[r2][c2]);
                        }
                }
        }

}

void Matrix::copy(Matrix &M, unsigned int r0, unsigned int c0) const {
	copyOrZeroFill(M, r0, c0, 0, 0);
}

void Matrix::getUnit(Matrix &M) {
	assertEqualDims(*this, M);
	assertDoubleNotEquals(getLength(), 0);

	M.clearCachedData();

	double length = getLength();
	for(unsigned int r=0; r<height; r++){
		for(unsigned int c=0; c<width; c++){
			M.setEntry(r, c, entries[r][c]/length);
		}
	}	
}

// TODO: - Overload addition operator
void Matrix::add(const Matrix &M, Matrix &R) const {
	assertEqualDims(M, R, *this);

	R.clearCachedData();

	for(unsigned int r = 0; r<height; r++){
		for(unsigned int c = 0; c<width; c++){
			R.setEntry(r, c, entries[r][c] + M.entries[r][c]);
		}
	}
}

// TODO: - Overload subtraction operator
//       - Deduplicate shared logic w. addition
void Matrix::subtract(const Matrix &M, Matrix &R) const {
	assertEqualDims(M, R, *this);

        R.clearCachedData();

        for(unsigned int r = 0; r<height; r++){
                for(unsigned int c = 0; c<width; c++){
                        R.setEntry(r, c, entries[r][c] - M.entries[r][c]);
                }
        }
}

// TODO: - preserve as many cached values as possible
//       - generalize
void Matrix::scalarMultiply(double scalar){
	clearCachedData();
	for(unsigned int r = 0; r<height; r++){
		for(unsigned int c = 0; c<width; c++){
			entries[r][c] *= scalar;
		}
	}
}

void Matrix::dotProduct(const Matrix &M, double &result) const {
	assertEqualDims(*this, M);
	result = 0;
        for(unsigned int r = 0; r<height; r++){
                for(unsigned int c = 0; c<width; c++){
                        result += getEntry(r,c) * M.getEntry(r,c);
                }
        }
}

vector<double> Matrix::getEigenvalues(){
        classifyMatrixAndGenerateEigenvalues();
	vector<double> eigencopy;
	for(unsigned int i=0; i<num_eigenvalues; i++){
		eigencopy.push_back(eigenvalues[i]);
	}
        return eigencopy;
}

// TODO: what if cannot allocate?
void Matrix::getIdentity(Matrix &M){
	M.clearCachedData();

	for(unsigned int r=0; r<M.height; r++){
		for(unsigned int c=0; c<M.width; c++){
			M.setEntry(r, c, (r == c) ? 1 : 0);
		}
	}

	M.len_squared = 1;
	M.eigenvalues = new double[1];
	M.eigenvalues[0] = 1;
	M.num_eigenvalues = 1;
	M.setDiagonal(true);
}
