#include "matrix.h"
#include "util.h"

using namespace std;

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *  Matrix classification methods implementation. 
 *  
 *  See matrix.h for documentation.
 *
 ******************************************************************/

#define HESSENBERG 	0x1000
#define NOT_HESSENBERG	0x2000
#define TRIANGULAR 	0x4000 // HESSENBERG IS TRIANGULAR
#define NOT_TRIANGULAR	0x8000
#define DIAGONAL   	0Xc000 // DIAGONAL IS TRIANGULAR AND HESSENBERG AND SYMMETRIC
#define NOT_DIAGONAL	0xf000
// TODO (etc...)
#define UNITARY		0x0100
#define NOT_UNITARY	0x0200
#define SYMMETRIC	0x0400
#define NOT_SYMMETRIC	0x0800

bool wasClassified(unsigned int classy, unsigned int positive, unsigned int negative){
	return false; // TEMP: TODO
	//return (classy & positive & negative) != 0;
}

void Matrix::setHessenberg(bool isHessenberg) {
	classification |= (isHessenberg) ? HESSENBERG : NOT_HESSENBERG;
}

void Matrix::setTriangular(bool isTriangular) {
	if(isTriangular) {
                setHessenberg(true);
                classification |= TRIANGULAR;
        } else {
                classification |= NOT_TRIANGULAR;
        }
}

void Matrix::setDiagonal(bool isDiagonal) {
	if(isDiagonal) {
		setTriangular(true);
        	classification |= DIAGONAL;
	} else {
		classification |= NOT_DIAGONAL;
	}
}

bool Matrix::isHessenberg(){
	if(wasClassified(classification, HESSENBERG, NOT_HESSENBERG)) {
		return (classification | HESSENBERG) != 0;
	}

        // NTS: necessary to use int here
        for(int r=0; r<height; r++){
                for(int c=0; c<(r-1) && c < width; c++){
                        if(!doubleEquals(getEntry(r, c), 0)) { 
				classification |= NOT_HESSENBERG;
				return false; 
			}
                }
        }

	classification |= HESSENBERG;
        return true;
}

bool Matrix::isTriangular(){
	if(wasClassified(classification, TRIANGULAR, NOT_TRIANGULAR)) {
                return (classification | TRIANGULAR) != 0;
        }

        for(unsigned int r=0; r<height; r++){
                for(unsigned int c=0; c<r && c < width; c++){
                        if(!doubleEquals(getEntry(r, c), 0)) {
				classification |= NOT_TRIANGULAR;
				return false; 
			}
                }
        }

	classification |= TRIANGULAR;
	classification |= HESSENBERG;
        return true;
}

bool Matrix::isDiagonal(){
        if(wasClassified(classification, DIAGONAL, NOT_DIAGONAL)) {
                return (classification | DIAGONAL) != 0;
        }

        for(unsigned int r=0; r<height; r++){
                for(unsigned int c=0; c < width; c++){
                        if(r != c && !doubleEquals(getEntry(r, c), 0)) {
                                classification |= NOT_DIAGONAL;
                                return false;
                        }
                }
        }

	classification |= DIAGONAL;
        classification |= TRIANGULAR;
	classification |= HESSENBERG;
	classification |= SYMMETRIC;
        return true;
}
