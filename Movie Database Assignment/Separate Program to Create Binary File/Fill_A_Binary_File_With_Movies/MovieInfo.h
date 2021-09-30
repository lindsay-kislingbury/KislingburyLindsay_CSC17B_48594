/* 
 * File:   MovieInfo.h
 * Author: Lindsay Kislingbury
 * Purpose: MovieInfo Structure Specification
 * Created on September 15, 2021, 10:21 PM
 */

#ifndef MOVIEINFO_H
#define MOVIEINFO_H
using namespace std;

struct MovieInfo{
    char movName[50]=""; //Hold movie name
    char dirName[50]=""; //Hold director name
    unsigned short yrRlsd; //Hold year release
    unsigned short runTime;//Hold running time in minutes
};

#endif /* MOVIEINFO_H */

