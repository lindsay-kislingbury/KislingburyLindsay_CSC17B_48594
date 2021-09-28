/* 
 * File:   Movies.h
 * Author: Lindsay Kislingbury
 * Purpose: Movies Structure Specification
 * Created on September 15, 2021, 10:22 PM
 */

#ifndef MOVIES_H
#define MOVIES_H

#include "MovieInfo.h"

struct Movies{
    int nMovies;        //Hold number of movies
    MovieInfo *mveInfo; //Pointer to array of movie info 
};

#endif /* MOVIES_H */

