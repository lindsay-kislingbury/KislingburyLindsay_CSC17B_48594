/* 
 * File:   StudentSections.h
 * Author: Lindsay Kislingbury
 * Purpose: StudentSections struct specification
 * Created on September 25, 2021, 1:45 PM
 */

#ifndef STUDENTSECTIONS_H
#define STUDENTSECTIONS_H
#include "Section.h"
#include "Student.h"

struct StudentSections{
    int numSections;
    Section *sections;
};


#endif /* STUDENTSECTIONS_H */

