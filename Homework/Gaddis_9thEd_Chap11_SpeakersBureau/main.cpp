/* 
 * File:   main.cpp
 * Author: Lindsay Kislingbury
 * Purpose: Gaddis Ch11 #9
 * Created on September 2, 2021, 9:08 PM
 */

//System Libraries
#include <cstdlib> //C Standard Library
#include <fstream> //File Stream
#include <iostream>//I/O Stream
#include <iomanip> //Formatting Library
#include <vector>
//Standard Namespace
using namespace std;
//User Libraries
#include "Speaker.h"//Speaker Structure Specification


//Function prototypes
Speaker *readTxt(int &);           //Read initial records from text file
void wrtBin(Speaker *, int);       //Write records to binary file  
void rdBin();                      //Read records from binary file
int recChc();                      //Get record number choice 
void showRec(int);                 //Display a single record
void recChng(int);                 //Menu To Input Record Changes
void editRec(Speaker, int);        //Edit a single record
Speaker copyRec(int);              //Read In A Single Record
void addRec(Speaker);              //Write a new record to the file
void makeRec();                    //Input new record info
void srchRec(int);                 //Search for a record by topic

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare variables
    fstream records;  //File stream
    Speaker *spkData; //Pointer to an array of speaker records
    int numRecs;      //Hold number of records
    char menu;        //Menu choice
    bool again=true;  //true = loop menu
    
    //***Initialize The Database From A Text File
    //Fill array of speaker records from initial text file
    //spkData=readTxt(numRecs);

    //Write records to binary file
    //wrtBin(spkData, numRecs);
    
    //Delete array of records
    //delete[] spkData;

    //Menu
    while(again){
        cout<<"Speaker's Bureau Database."<<endl;
        cout<<"Menu Options:"<<endl;
        cout<<"1. Display All Records"<<endl;
        cout<<"2. View a Record by Record number"<<endl;
        cout<<"3. Search For a Record by Topic"<<endl;
        cout<<"4. Edit a Record"<<endl;
        cout<<"5. Add a Record"<<endl;
        cout<<"6. Exit Program"<<endl;
        cin>>menu;
        switch(menu){
            case '1'://Display all the records in the binary file
                rdBin();
                break;
            case '2'://View a record by record number
                cout<<"View a Record."<<endl;
                showRec(recChc());
                break;
            case '3': //Search for a record by topic
                cout<<"Search For A Record By Topic."<<endl;
                srchRec(numRecs);
                break;
            case '4'://Edit a Record
                cout<<"Edit a Record."<<endl;
                recChng(recChc());
                break;
            case '5'://Add a Record
                makeRec();
                break;
            case '6'://End Program
                again=false;
                break;
        }
        //Clear Buffer
        cin.clear();
        cin.ignore();
    }
    //Exit
    return 0;
}

//Function Definitions
//Initialize Database From Text File
Speaker *readTxt(fstream in, int &numRecs){
    //Declare Variables
    Speaker *records;           //Pointer to an array of speaker records
    fstream in;                 //fstream object
    string fname, lname, topic; //hold name and topic 
    char   cName[40];           //hold name as c-string
    int phone, fee;             //hold phone number and fee
    int count=0;                //hold # of records in the file
    
    //Count the number of records
    in.open("speakersInfo.txt");
    while(in>>fname>>lname>>phone>>topic>>fee){
        count++;
    }
    in.close();
    
    //Allocate memory for array of speaker records
    records=new Speaker[count];
    
    //Store records
    in.open("speakersInfo.txt");
    numRecs=0; //Initialize number of records to zero
    while(in>>fname>>lname>>phone>>topic>>fee){
        //Combine first and last name
        string name=fname+" "+lname;
        //Convert name to cstring
        for(int i=0; i<40; i++) records[numRecs].name[i]=name[i];
        records[numRecs].phone=phone;
        //Convert topic to cstring
        for(int i=0; i<15; i++) records[numRecs].topic[i]=topic[i];
        records[numRecs].fee=fee;
        numRecs++;
    }
    in.close();
    //Return array of records
    return records;
}

//Write records to binary file
void wrtBin(Speaker *spkData, int numRecs){
    //Open file for binary output
    fstream out("speakersInfo.dat", ios::out | ios::binary);
    if(out.is_open()) cout<<"OPEN"<<endl;
    //Write records to binary file
    for(int r=0; r<numRecs; r++){
        out.write(reinterpret_cast<char *>(&spkData[r]),sizeof(spkData[r]));
    }
    //Close the file
    out.close();
}

//Display a Record
void showRec(int recNum){
    Speaker temp;   //Hold speaker info
    //Open binary file for input
    fstream in("speakersInfo.dat", ios::in| ios::binary);
    //Find the record
    in.seekg(recNum*sizeof(temp), ios::beg);
    //Read the record
    in.read(reinterpret_cast<char *>(&temp),sizeof(temp));
    //Display the record
    cout<<"+----- Record #"<<in.tellg()/(sizeof(temp)-1)-1<<" -----+"<<endl;
    cout<<"Name: "<<temp.name<<endl;
    cout<<"Phone: "<<temp.phone<<endl;
    cout<<"Topic: "<<temp.topic<<endl;
    cout<<"Fee: "<<temp.fee<<endl;
    cout<<endl;
    //Close the file
    in.close();
}

//Display all records in the binary file
void rdBin(){
    Speaker temp;   //Hold Speaker record
    int num=0;      //Hold Record Number
    //Open the binary file for output
    fstream in("speakersInfo.dat", ios::in |ios::binary);
    //Display each record
    while(!in.eof()){ //Loop until end of the file is reached
        if(in.read(reinterpret_cast<char*>(&temp),sizeof(temp))){ 
            cout<<right<<setw(10)<<"Record #"<<num<<": "<<endl;
            cout<<right<<setw(7)<<"Name: "<<left<<temp.name<<endl;
            cout<<right<<setw(7)<<"Phone: "<<left<<temp.phone<<endl;
            cout<<right<<setw(7)<<"Topic: "<<left<<temp.topic<<endl;
            cout<<right<<setw(7)<<"Fee: "<<left<<temp.fee<<endl;
            cout<<endl;
            num++;
        }
        //If read is not successful, end loop
        else if(!in.read(reinterpret_cast<char*>(&temp),sizeof(temp)))
            break;
    }   
    //Close the file
    in.close();
}

//Choose a record by number
int recChc(){
    int choice; //Hold record number
    //Get record number from user
    cout<<"Enter the Record Number: "<<endl;
    cin>>choice;
    return choice;
}


void recChng(int recNum){
    //Declare Variables
    Speaker updated;    //Hold updated speaker info
    bool cont=true;     //true = loop menu
    char choice;        //Menu choices
    string sName;       //Hold new name as string 
    string sTopic;      //Hold new topic as string
    char name[40];      //Hold new name as c-string
    char topic[15];     //Hold new topic
    int phone;          //Hold new phone number
    int fee;            //Hold new fee
    bool nm=false;      //true = name has been changed
    bool tp=false;      //true = topic has been changed
    bool pn=false;      //true = phone has been changed
    bool fe=false;      //true = fee has been changed
    
    //Initialize speaker with current info
    updated=copyRec(recNum);
    //Display Chosen Record
    showRec(recNum);
    //Menu
    while(cont){
        cout<<"Edit Record Menu"<<endl;
        cout<<"n: Edit Name"<<endl;
        cout<<"p: Edit Phone Number"<<endl;
        cout<<"t: Edit Topic"<<endl;
        cout<<"f: Edit Fee"<<endl;
        cout<<"v: View Changes"<<endl;
        cout<<"s: Save Changes and Exit"<<endl;
        cin>>choice;
        switch(choice){
            case 'n': //Edit Name
                do{
                    cout<<"Name Must Be 40 Characters or Less"<<endl;
                    cout<<"Enter The New Name: ";
                    //Get new name including whitespace
                    cin.ignore();
                    cin.clear();
                    getline(cin, sName); 
                }while(sName.length()<1||sName.length()>40);
                //Store new name as c-string
                for(int i=0; i<sName.length(); i++) name[i]=sName[i];
                nm=true; //Set changed status to true
                break;
            case 'p': //Edit Phone Number
                cout<<"Enter The New Phone Number: ";
                cin>>phone;
                pn=true; //Set changed status to true
                break;
            case 't': //Edit Topic
                do{
                    cout<<"Topic Must be 15 Characters or Less"<<endl;
                    cout<<"Enter The New Topic:";
                    cin.ignore();
                    cin.clear();
                    getline(cin, sTopic);
                }while(sTopic.length()<1||sTopic.length()>40);
                for(int i=0; i<sTopic.length(); i++) topic[i]=sTopic[i];
                tp=true; //Set changed status to true
                break;
            case 'f': //Edit Fee
                do{
                    cout<<"Fee Must Be Positive, Whole Dollar Amount"<<endl;
                    cout<<"Enter The New Fee: $";
                    cin>>fee;
                }while(fee<0);
                fe=true; //Set changed status to true
                break;       
            case 'v': //View Changes
                cout<<"CHANGES:"<<endl;
                if(nm) cout<<"Name: "<<name<<endl;
                if(pn) cout<<"Phone Number: "<<phone<<endl;
                if(tp) cout<<"Topic: "<<topic<<endl;
                if(fe) cout<<"Fee: $"<<fee<<endl;
                break;
            case 's': //Save Changes
                if(nm) 
                    for(int i=0; i<40; i++) updated.name[i]=name[i];
                if(tp)
                    for(int i=0; i<15; i++) updated.topic[i]=topic[i];
                if(pn) updated.phone=phone;
                if(fe) updated.fee=fee;
                editRec(updated, recNum);
                //Display updated Record
                showRec(recNum);
                cont=false; //Exit Program
                break;  
        }
    }
}

//Edit a Record
void editRec(Speaker updated, int recNum){
    //Open binary file for input and output
    fstream records("speakersInfo.dat", ios::in | ios::out | ios::binary);
    //Move to the record to be changed
    records.seekp(recNum*sizeof(updated), ios::beg);
    //Write new record over the current record
    cout<<"RE-WRITING RECORD #"<<recNum<<"..."<<endl;
    records.write(reinterpret_cast<char *>(&updated),sizeof(updated));
    //Close File
    records.close();
}

//Store a speaker record 
Speaker copyRec(int recNum){
    Speaker temp; //Hold record to store
    fstream records("speakersInfo.dat", ios::in | ios::out | ios::binary);
    //Move to the record 
    records.seekp(recNum*sizeof(temp), ios::beg);
    //Read the record
    records.read(reinterpret_cast<char *>(&temp),sizeof(temp));
    //Close File
    records.close();
    //Return record
    return temp;
}

//Create New Record
void makeRec(){
    //Declare Variables
    Speaker temp;   //Hold new speaker record info
    string  name;   //Hold name input
    int fee;        //Hold fee input
    //Get Speaker Info
    cout<<"Enter New Record Info."<<endl;
    cout<<"Speaker Name: ";
    cin.ignore();
    cin.clear();
    getline(cin, name);
    for(int i=0; i<40; i++) temp.name[i]=name[i];
    cout<<"Speaker Phone Number: ";
    cin>>temp.phone;
    cout<<"Speaker Topic: ";
    cin>>temp.topic;
    cout<<"Speaker Fee: $";
    cin>>fee;
    if(fee<0){ //Error Checking
        while(fee<0){
            cout<<"Must Enter Positive Value!"<<endl;
            cout<<"Enter The New Fee: $";
            cin>>fee;
        }
    }
    temp.fee=fee;
    //Write Record to the end of the file
    addRec(temp);
}

//Add A New Record To End Of File
void addRec(Speaker temp){
    //Open binary file for input and output
    fstream records("speakersInfo.dat", ios::in | ios::out | ios::binary | ios:: app);
    //Write new record 
    records.write(reinterpret_cast<char *>(&temp),sizeof(temp));
    records.close();
}

//Find A Record By Topic
void srchRec(int numRecs){
    //Declare Variables
    string search;      //Hold topic to search for
    string recTopic;    //Hold the record topic as string for comparison
    Speaker temp;       //Hold each record read for comparison
    vector<int> results;//Hold matching record numbers
    int num=0;
    //Get search term
    cout<<"Enter the Topic: ";
    cin>>search;
    //Open file for input
    fstream in("speakersInfo.dat", ios::in |ios::binary);
    //Find matching records
    while(!in.eof()){ //Loop until end of the file is reached
        if(in.read(reinterpret_cast<char*>(&temp),sizeof(temp))){ 
            recTopic=temp.topic;
            if(recTopic==search){
                results.push_back(num);
            }
        }
        //If read is not successful, end loop
        else if(!in.read(reinterpret_cast<char*>(&temp),sizeof(temp)))
            break;
        num++;
    }   
    //Close the file
    in.close();
    //Display Matching Records
    if(results.size()>0){
        cout<<"There Are "<<results.size()<<" Matching Records:"<<endl;
        for(int i=0; i<results.size(); i++){
            showRec(results[i]);
        }
    }
    else cout<<"No Matches For \""<<search<<"\""<<endl;
}





