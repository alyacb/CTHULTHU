#include <iostream>
#include <iomanip>

#include "matrix.h"
#include "util.h"

using namespace std;

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  Matrix operatiors implementation. 
 *
 *  See matrix.h for documentation.
 *
 ******************************************************************/

/************************ CONSTRUCTOR/DESTRUCTOR ******************/

// TODO: - Not safe for large height/width; may not have enough memory to store. 
//       - Not safe for width/height == 0
//       - Switch order of width & height
Matrix::Matrix(unsigned int width, unsigned int height) : width{width}, height{height}{
        entries = (height == 0) ? NULL : new double*[height];
        for (unsigned int r=0; r<height; r++){
                entries[r] = new double[width];
        }
	classification = 0;
        classy = UNKNOWN;
        len_squared = -1;
        secret_max = -1;
}

Matrix::~Matrix(){
        for(unsigned int r=0; r<height; r++){
                delete[] entries[r];
        }
        delete[] entries;
        clearCachedData();
}

/************************* EQUALITY/INEQUALITY *********************/

bool Matrix::operator==(const Matrix &that) const {
	if(this->width != that.width || this->height != that.height) { 
		return false;
	}

	for(unsigned int r=0; r < this->height; r++){
                for (unsigned int c=0; c < this->width; c++) {
                        if((this->getEntry(r, c) != that.getEntry(r, c))) {
				if (doubleEquals(getEntry(r,c), that.getEntry(r, c))) {
					continue; 
				}
                                return false;
                        }
                }
        }

	return true;
}

bool Matrix::operator!=(const Matrix &that) const {
	return !(*this == that);
}

/*************************** INPUT/OUTPUT *************************/

ostream &operator<<(ostream &out, const Matrix &m){
        if(m.width == 0) { return out; }
        for(unsigned int r=0; r<m.height; r++){
                out << left << setw(m.width) << "\t|";
                for(unsigned int c=0; c<m.width; c++){
                        out << left 
			    << setw(m.width) 
			    << (doubleEquals(m.entries[r][c], 0) ? 0 : m.entries[r][c])
			    << ' ';
                }
                out << left << setw(m.width) << "\t|";
                out << endl;
        }
        return out;
}

// TODO: - Error-handling
istream &operator>>(istream &in, Matrix &m){
        if(m.width == 0) { return in; }
        double temp;
        unsigned int r = 0;
        unsigned int c = 0;
	m.clearCachedData();
        while(r<m.height && in >> temp){
                m.setEntry(r, c, temp);
                c++;
                c %= m.width;
                if(c == 0) {
                        r++;
                }
        }
        return in;
}
