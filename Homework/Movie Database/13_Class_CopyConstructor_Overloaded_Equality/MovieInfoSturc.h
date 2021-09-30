/* 
 * File:   MovieInfoSturc.h
 * Author: Lindsay Kislingbury (& Dr. Lehr)
 * Created on 09/15/2021 10:10PM
 * Purpose: MovieInfo Structure Specification
 */

#ifndef MOVIEINFOSTURC_H
#define MOVIEINFOSTURC_H

#include <string>
using namespace std;

struct MovieInfo{
    string movName;//Strings are good
    string dirName;//You should know how to deal with dynamic character arrays
    unsigned short yrRlsd; //Don't need a larger data size and always > 0
    unsigned short runTime;//Don't need a larger data size and always > 0
};


#endif /* MOVIEINFOSTURC_H */

