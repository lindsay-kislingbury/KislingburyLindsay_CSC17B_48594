/* 
 * File:   CMovie.h
 * Author: Lindsay Kislingbury
 * Purpose: CMovie Class Specification
 * Created on September 15, 2021, 10:46 PM
 */

#ifndef CMOVIE_H
#define CMOVIE_H

#include <fstream>
#include <vector>
#include "Movies.h"

class CMovie{
private:
    Movies *movies;
    fstream records;
public:
    CMovie();//Constructor
    ~CMovie();//Destructor
    void display(int);//Display a movie's info
    void displayAll();
    int getSize();
    void add();
    void readBin();//Read in data from binary file
    void search(); //Search for a movie
    void getMvs(char, int);
    void getMvs(char, char[]);
};



#endif /* CMOVIE_H */

