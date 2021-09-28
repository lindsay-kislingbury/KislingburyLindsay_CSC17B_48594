/* 
 * Author: Lindsay Kislingbury (& Dr. Lehr)
 * Created on 09/15/2021 10:10PM
 * Purpose: Movie Data Structure
 */

//System Level Libraries
#include <iostream>   //I/O Library
#include <cstdlib>    //Random Number Generator, Setting seed, etc....
#include <iomanip>    //Formatting Library
#include <string>     //String Library
using namespace std;  //Libraries compiled under std

//User Level Libraries
#include "CMovie.h"

//Function Prototypes

//Execution Begins Here!
int main(int argc, char** argv) {
    //Variable Declarations
    CMovie cmovie;//Class
    cout<<"movie created"<<cmovie.display<<endl;
    
    /* COPY CONSTRUCTOR TEST
    CMovie bmovie(cmovie);//Copy Constructor Test
    CMovie amovie=bmovie;//Overloaded Equality Operator
    
    //Now you can loop on the data as many times as it takes!
    cmovie.display();//Look and see
    bmovie.display();//Look and see
    amovie.display();//Look and see
     * */

    //Exit stage right!
    return 0;
}