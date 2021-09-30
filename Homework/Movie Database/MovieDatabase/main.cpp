/* 
 * File:   main.cpp
 * Author: Lindsay Kislingbury
 * Purpose: Movie Database
 * Created on September 15, 2021, 9:50 PM
 */

//System Libraries
#include <cstdlib>
#include <iostream>
//User Libraries
#include "CMovie.h"
using namespace std;

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare Variables
    char choice;        //Hold Menu Choice
    bool again=true;    //true=loop menu
    CMovie movieData;   //Movie Database
    
    //Get Inputs
    cout<<"Welcome To The Top 100 Sci-Fi Movies Database!"<<endl;
    do{
        cout<<"\t\tMENU"<<endl;
        cout<<"v: View All Movies   s: Search For A Movie   a: Add a Movie"<<endl;
        cout<<"Enter Your Choice: ";
        cin>>choice;
        switch(choice){
            case 'v': //View All Movies
                movieData.displayAll();
                break;
            case 's': //Search For A Movie
                movieData.search();
                break;
            case 'a': //Add a Movie
                movieData.add();
                break;
        }
    }while(again);
    //Exit
    return 0;
}



