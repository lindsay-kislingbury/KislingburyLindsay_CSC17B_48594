/* 
 * File:   CMovie.h
 * Author: Lindsay Kislingbury (& Dr. Lehr)
 * Created on 09/15/2021 10:10PM
 * Purpose: CMovie Class Specification
 */

#ifndef CMOVIE_H
#define CMOVIE_H

#include "MoviesStruct.h"

class CMovie{
    private:
        Movies *movies;//Pointer to the dynamic Movie structure.
    public:
        CMovie();//Constructor
        CMovie(const CMovie &);//Copy Constructor
        CMovie operator=(const CMovie &);//Chain Equality Operator
        ~CMovie();//Destructor
        void display();//Display
};

#endif /* CMOVIE_H */

