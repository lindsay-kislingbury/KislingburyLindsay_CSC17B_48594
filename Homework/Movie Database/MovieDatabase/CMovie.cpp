/* 
 * File:   CMovie.h
 * Author: Lindsay Kislingbury
 * Purpose: CMovie Function Definitions
 * Created on September 15, 2021, 10:46 PM
 */
//System Libraries
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
//User Libraries
#include "CMovie.h"

//Constructor
CMovie::CMovie(){
    //Declare the Structure Array
    movies=new Movies; //Declare the Structure Array
    //Get size of database
    movies->nMovies=getSize();
    //Allocate memory for array of movies 
    movies->mveInfo=new MovieInfo[movies->nMovies];
    //Read in data from binary file
    readBin();
}
//Destructor
CMovie::~CMovie(){
    delete [] movies->mveInfo;
    delete movies;      
}
//Get Database Size
int CMovie::getSize(){
    MovieInfo temp; //Hold a temporary MovieInfo structure
    int num=0;      //Hold number of movies in database
    records.open("MovieData.dat", ios::in|ios::binary);
    while(!records.eof()){ //Loop until end of the file is reached
        if(records.read(reinterpret_cast<char*>(&temp),sizeof(temp)))
            num++;
        //If read is not successful, end loop
        else if(!records.read(reinterpret_cast<char*>(&temp),sizeof(temp)))
            break;  
    }
    records.close();
    return num;
}
//Display One Movie
void CMovie::display(int recNum){
    cout<<left<<endl;
    cout<<setw(11)<<"Title:"<<movies->mveInfo[recNum].movName<<endl;
    cout<<setw(11)<<"Director:"<<movies->mveInfo[recNum].dirName<<endl;
    cout<<setw(11)<<"Year:"<<movies->mveInfo[recNum].yrRlsd<<endl;
    cout<<setw(11)<<"Length:"<<movies->mveInfo[recNum].runTime<<endl;
}
//Display All Movies
void CMovie::displayAll(){
    for(int mvees=0; mvees<movies->nMovies; mvees++){
        cout<<left<<endl;
        cout<<setw(11)<<"Title:"<<movies->mveInfo[mvees].movName<<endl;
        cout<<setw(11)<<"Director:"<<movies->mveInfo[mvees].dirName<<endl;
        cout<<setw(11)<<"Year:"<<movies->mveInfo[mvees].yrRlsd<<endl;
        cout<<setw(11)<<"Length:"<<movies->mveInfo[mvees].runTime<<endl;
    }
}
//Read In Data From Binary File
void CMovie::readBin(){
    MovieInfo temp;   //Hold Movie record
    int num=0;        //Hold Record Number
    records.open("MovieData.dat", ios::in|ios::binary);//Open file 
    for(int i=0; i<movies->nMovies; i++){ //Loop until end of file is reached
        if(records.read(reinterpret_cast<char*>(&temp),sizeof(temp))){ 
            for(int m=0; m<50; m++){//Copy c string movie name
                movies->mveInfo[num].movName[m]=temp.movName[m];
            }
            for(int d=0; d<50; d++){//Copy c string director name
                movies->mveInfo[num].dirName[d]=temp.dirName[d];
            }
            movies->mveInfo[num].yrRlsd=temp.yrRlsd;//Copy year released
            movies->mveInfo[num].runTime=temp.runTime;//Copy run time
            num++;
        }
        //If read is not successful, end loop
        else if(!records.read(reinterpret_cast<char*>(&temp),sizeof(temp))){
            cout<<"Error reading file"<<endl;
            break;
        }
    }   
    records.close();//Close the file
}
//Add a movie
void CMovie::add(){
    MovieInfo temp; //Temporary MovieInfo structure
    string name;    //Hold movie and director name
    //Increase database size
    movies->nMovies++;
    //Get Move Info
    cout<<"Enter the Movie Name: ";
    cin.ignore();
    cin.clear();
    getline(cin, name);
    for(int i=0; i<name.length(); i++) temp.movName[i]=name[i];
    cout<<"Enter the Director's Name: ";
    getline(cin, name);
    for(int i=0; i<name.length(); i++) temp.dirName[i]=name[i];
    cout<<"Enter the Year Released: ";
    cin>>temp.yrRlsd;
    cout<<"Enter the Running Time in Minutes: ";
    cin>>temp.runTime;
    //Write the new structure to the binary file
    records.open("MovieData.dat", ios::in | ios::out | ios::binary | ios:: app);
    //Write new record 
    records.write(reinterpret_cast<char *>(&temp),sizeof(temp));
    records.close();
}
//Search for A Movie
void CMovie::search(){
    bool again=true;        //true=loop menu
    char choice;            //Hold menu choice
    int num;                //Hold numeric search term
    string name;            //Hold string search term
    char cName[50];         //Hold name as c string
    vector<int> results;    //Hold indexes of search results
    
    //Get Search Query
    cin.ignore();
    cin.clear();
    cout<<"How Would You Like To Search?"<<endl;
    cout<<left<<setw(20)<<"n: Movie Name"<<left<<setw(20)<<"d: Director Name   "<<endl;
    cout<<left<<setw(20)<<"y: Year Released"<<left<<setw(20)<<"t: Running Time"<<endl;
    cin>>choice;
    switch(choice){
        case 'n':
            cout<<"Enter the movie name to search for: ";
            cin.clear();
            cin.ignore();
            getline(cin, name);
            for(int i=0; i<name.length(); i++) cName[i]=name[i];
            for(int i=0; i<movies->nMovies; i++){ 
                if(movies->mveInfo[i].movName==name){ //If moive name matches
                    results.push_back(i);//Add the index to results
                    }
                }
            break;
        case 'd':
            cout<<"Enter the director name to search for: ";
            cin.clear();
            cin.ignore();
            getline(cin, name);
            for(int i=0; i<name.length(); i++) cName[i]=name[i];
            for(int i=0; i<movies->nMovies; i++){ //If director name matches
                if(movies->mveInfo[i].dirName==name){
                    results.push_back(i); //Add the index to results
                }
            }
            break;
        case 'y':
            cout<<"Enter the year to search for: ";
            cin>>num;
            for(int i=0; i<movies->nMovies; i++){ 
                if(movies->mveInfo[i].yrRlsd==num){//If year matches
                    results.push_back(i); //add index to results
                }
            }
            break;
        case 't':
            cout<<"Enter the time to search for: "<<endl;
            cin>>num;
            for(int i=0; i<movies->nMovies; i++){
                if(movies->mveInfo[i].runTime==num){ //if runtime matches
                 results.push_back(i); //add index to results
                }
            }
            break;
    }
    //Display Results
    if(results.size()<1) cout<<"No Results!"<<endl;
    else{
        for(int i=0; i<results.size(); i++){
            display(results[i]);
        }
    }
}
