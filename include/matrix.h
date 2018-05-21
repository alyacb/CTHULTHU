#ifndef ___CTHULTHU__MATRIX_ACB___
#define ___CTHULTHU__MATRIX_ACB___

#include <iostream>
#include <vector>

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  A class for matrices. Pretty self-explanatory.
 *
 *  Implementation in:
 *   - matrix_ops.h (overloaded operators, constructor, destructor)
 *   - marix_api.h (the bulk of callable methods)
 *   - matrix_mult.h (matrix multiplication implementation)
 *
 ******************************************************************/

// TODO: - Track if a matrix is Unitary, Unit, Hermissian, Hessenberg, Orthogonal...
//       - Eigenvectors- bases, eigenspaces... extend Matrix for Vector?
//       - use a ds more accurate than a double
//       - specify what errors are thrown by what

enum MatrixClassification {
	POSITIVE_DEFINITE,
	NEGATIVE_DEFINITE,
	POSITIVE_SEMI_DEFINITE,
	NEGATIVE_SEMI_DEFINITE,
	NON_ZERO_EIGENVALUES,
	ALL_ZERO_EIGENVALUES,
	MIXED_EIGENVALUES,
	UNKNOWN // eigenvalues not yet computed
};

class Matrix {

	double **entries;
	double *eigenvalues;
	unsigned int num_eigenvalues;
	MatrixClassification classy;
	unsigned int classification;
	double len_squared; // negative iff len not calculated
	double secret_max; // largest entry

	// does as name suggests, storing eigenvalues in this
	void classifyMatrixAndGenerateEigenvalues();

	// deletes eigenvalues:
	//    - to save space
	//    - because they are invalidated (matrix changed)
	// also sets len_squared to -1 to indicate it is invalid
	// and invalidates other cached data (e.g. classification)
	void clearCachedData();

	// helper methods to set a classification when it is known
	void setHessenberg(bool isHessenberg);
	void setTriangular(bool isTriangular);
	void setDiagonal(bool isDiagonal);

	void copyCachedData(Matrix &T) const;

	// performs a Hessenberg QR step on this matrix
	// and places Q and R in the provided matrices
	void doHessenbergQRStep(Matrix &Q, Matrix &R) const;

   public:

	const unsigned int width;
	const unsigned int height;

	Matrix(unsigned int width, unsigned int height);	

	// sets entry at row r % height, column c % width
	// throws std::out_of_range if width or height == 0
        void setEntry(unsigned int r, unsigned int c, double value);

	// returns entry at row r % height, column c % width
	// throws std::out_of_range if width or height == 0 
	double getEntry(unsigned int r, unsigned int c) const;

	// returns classification of the matrix
        // If classy == UNKNOWN is set, generates eigenvalues and classification.
        MatrixClassification getClassification();

        // stores eigenvalues in a vector
        std::vector<double> getEigenvalues();

	// returns the length of the matrix
	// - i.e. the square root of the 
	// - standard inner product of the matrix with itself
	double getLength();

	// returns the length squared
	double getLengthSquared();

	// places Hessenberg form of matrix in H
	// places orthogonal matrix in U
	void getHessenberg(Matrix &H, Matrix &U) const;

	// places upper-triangularized matrix in T
        void upperTriangularize(Matrix &T) const;

	// places transpose of matrix in T
        void transpose(Matrix &T) const;

	// places copy of this in T, then zero-fills any superfluous columns
	void copyOrZeroFill(Matrix &T) const;

	// TODO: REFACTOR THESE: ////////////////////////////////////////////

	// places copy of this in T, starting at entry (r0, c0) in this
	// any extra columns are filled with 0's
        void copyOrZeroFill(Matrix &T, unsigned int r0, unsigned int c0) const;

	// places copy of this in T at (r1, c1), starting at entry (r0, c0) in this
	// any extra columns are filled with 0's
	void copyOrZeroFill(Matrix &T, unsigned int r0, unsigned int c0, 
                                       unsigned int r1, unsigned int c1) const;

	// copies a matrix into another matrix from the specified coordinates
	void copy(Matrix &M, unsigned int r0, unsigned int c0) const;

	// copies a matrix into another matrix at (r1, c1) from (r0, c0)
	void copy(Matrix &M, unsigned int r0, unsigned int c0,
			     unsigned int r1, unsigned int c1) const;

	/////////////////////////////////////////////////////////////////////

	// places the unit version of this matrix in M
	void getUnit(Matrix &M);

	// places result of multiplying this by M in R
	void multiply(const Matrix &M, Matrix &R) const;

	// places result of adding this to M in R
	void add(const Matrix &M, Matrix &R) const;

	// places result of subtracting this from M in R
        void subtract(const Matrix &M, Matrix &R) const;

	// scalar multiplies this by a constant factor
	void scalarMultiply(double scalar);

	void dotProduct(const Matrix &M, double &result) const;

	// tests if a matrix is in LOWER Hessenberg form
	bool isHessenberg();

	// tests if a matrix is in LOWER Triangular form
	bool isTriangular();

	bool isDiagonal();

	// converts this matrix into the identity matrix
	// and places it in M
	static void getIdentity(Matrix &M);
	
	// Overloaded Operators:
	bool operator==(const Matrix &that) const;
	bool operator!=(const Matrix &that) const;
	friend std::ostream &operator<<(std::ostream &out, const Matrix &m);
	friend std::istream &operator>>(std::istream &in, Matrix &m);

	~Matrix();
};

std::ostream &operator<<(std::ostream &out, const Matrix &m);
std::istream &operator>>(std::istream &in, Matrix &m);

#endif
