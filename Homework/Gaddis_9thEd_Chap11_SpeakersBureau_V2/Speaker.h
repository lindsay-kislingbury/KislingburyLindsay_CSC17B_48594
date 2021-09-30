/* 
 * File:   Speakers.h
 * Author: Lindsay Kislingbury
 * Purpose: Speakers Structure Specification
 * Created on September 2, 2021, 9:34 PM
 */

#include <string>
#ifndef SPEAKER_H
#define SPEAKER_H


struct Speaker{
    char    name[40];   //Hold speaker name
    int     phone;      //Hold speaker phone number 7 digits
    char    topic[15];  //Hold Topic
    int     fee;        //Hold fee, whole dollar amount
};


#endif /* SPEAKERS_H */

