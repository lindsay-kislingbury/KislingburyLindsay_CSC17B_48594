/* 
 * File:   StudentData.h
 * Author: Lindsay Kislingbury
 * Purpose: StudentData class specification
 * Created on September 25, 2021, 1:26 PM
 */

#ifndef STUDENTDATA_H
#define STUDENTDATA_H
#include "Student.h"

class StudentData{
private:
    Student *students;
    int numStudents;
public:
    StudentData(){//Constructor
        cout<<"How many students?: ";
        cin>>numStudents;
        //Allocate memory for array of students
        students=new Student[numStudents];
    } 
    ~StudentData(){
        for(int i=0; i<numStudents; i++){
           delete students[i].studentSections;
        }
        delete []students;
    }
    getNumStudents(){
        return numStudents;
    }
    
};


#endif /* STUDENTDATA_H */

