/* 
 * File:   Student.h
 * Author: Lindsay Kislingbury
 * Purpose: Student Struct Specification
 * Created on September 25, 2021, 1:13 PM
 */

#ifndef STUDENT_H
#define STUDENT_H
#include "Section.h"

struct Student{
    int studentID;
    Section *studentSections;
    char studentName[45];
};



#endif /* STUDENT_H */

