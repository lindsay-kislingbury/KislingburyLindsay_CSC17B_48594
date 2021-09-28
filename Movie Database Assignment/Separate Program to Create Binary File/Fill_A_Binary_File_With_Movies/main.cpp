/* 
 * File:   main.cpp
 * Author: Lindsay Kislingbury
 * Purpose: Fill a Binary File with data from a text file
 * Created on September 15, 2021, 11:17 PM
 */

//System Libraries
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//User Libraries
#include "MovieInfo.h" //Movie Info Structure

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare variables
    const int numRecs=100;         //Number of movies to read in from file
    MovieInfo movieData[numRecs];  //Array of movies
    fstream records;               //File stream
    string mName, dName;           //hold movie name and director as string
    
    //Read records from text file
    records.open("MovieData.txt");//Open text file 
    for(int i=0; i<numRecs; i++){
        getline(records, mName, '\t');//Read in movie name
        //Convert movie name to c string, skip newline character
        for(int m=0; m<mName.length(); m++) movieData[i].movName[m]=mName[m+2];
        getline(records, dName, '\t');//Read in director name
        //Convert director name to c string
        for(int d=0; d<dName.length(); d++) movieData[i].dirName[d]=dName[d];
        records>>movieData[i].yrRlsd;//Read in year released
        records>>movieData[i].runTime;//Read in run time
    }
    records.close();//Close the file
    
    //Write records to binary file
    records.open("MovieData.dat", ios::out | ios::binary);//Open file for output
    if(records.is_open()) cout<<"OPEN"<<endl;
    for(int r=0; r<numRecs; r++){//Write records
        records.write(reinterpret_cast<char *>(&movieData[r]),sizeof(movieData[r]));
    }
    records.close();//Close the file
    
    //Display all records in the binary file
    MovieInfo temp;   //Hold Movie record
    int num=0;        //Hold Record Number
    records.open("MovieData.dat", ios::in |ios::binary);//Open file for output
    while(!records.eof()){ //Loop until end of the file is reached
        if(records.read(reinterpret_cast<char*>(&temp),sizeof(temp))){ 
            cout<<right<<setw(10)<<"Movie #"<<num<<": "<<endl;
            cout<<right<<setw(7)<<"Name: "<<left<<temp.movName<<endl;
            cout<<right<<setw(7)<<"Director: "<<left<<temp.dirName<<endl;
            cout<<right<<setw(7)<<"Year Released: "<<left<<temp.yrRlsd<<endl;
            cout<<right<<setw(7)<<"Running Time: "<<left<<temp.runTime<<endl;
            cout<<endl;
            num++;
        }
        //If read is not successful, end loop
        else if(!records.read(reinterpret_cast<char*>(&temp),sizeof(temp)))
            break;
    }   
    records.close();//Close the file
    
    return 0;
}
