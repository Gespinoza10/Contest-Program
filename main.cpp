/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
//Gerardo Espinoza
//Assignment #3 part 2
//April 8, 2022

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//function prototypes
void ReadInputRecord(ifstream &, int &, int &, int &, int &, int &, int &, string &);
int CalculateScore(int, int, int, int, int, int, int &);
void WriteOutputRecord(ofstream &,const string &, int, int);

//defining variables
int firstSecOne, firstSecTwo, firstSecThree, firstTriesOne, firstTriesTwo, firstTriesThree;
string firstTeamName;
int totalSec=0, probSolved=0;

int main()
{
    ifstream file;
    ofstream outfile;
    
    //opening the file where we will write our output
    outfile.open("ComputedScore.txt");
    
    //opening the file to read data
    file.open("RawScore.txt", ios::in);
    
    //making sure both of our file have been opened successfully 
    if(!outfile){
        cout<< "File open failure!";
        return 0;
    }
    
    if (!file){
        cout << "File open failure!";
        return 0; 
    }   
    
    //doing a while loop to read records, calculate score, then write the output record until the end of the file
    while(!file.eof()){
         
        //calling the function to read the file records
        ReadInputRecord(file, firstSecOne, firstSecTwo, firstSecThree, firstTriesOne, firstTriesTwo, firstTriesThree, firstTeamName);
        
        //calling the function that will gather our total problems solves and total records
        probSolved = CalculateScore(firstSecOne, firstSecTwo, firstSecThree, firstTriesOne, firstTriesTwo, firstTriesThree, totalSec);
         
        //calling function to write out output to a file    
        WriteOutputRecord(outfile, firstTeamName, probSolved, totalSec);
    }
    //closing our files
    outfile.close();
    file.close();
}

//defining function to read the raw records per team 
void ReadInputRecord(ifstream &fileInput, int &secOne, int &secTwo, int &secThree, int &triesOne, int &triesTwo, int &triesThree, string &teamName){
    fileInput>>secOne>>secTwo>>secThree>>triesOne>>triesTwo>>triesThree>>teamName;
}

//defining the function that will calculate the score record of each team
int CalculateScore(int secOne, int secTwo, int secThree, int triesOne, int triesTwo, int triesThree, int &totalSec){
    
    int probSolved=0;
    int penalty = 1200;
    int penaltyTimeOne = 0, penaltyTimeTwo=0, penaltyTimeThree=0;
    
    if(secOne > 0 && triesOne >= 1){
        probSolved++;
        
        penaltyTimeOne = penalty * triesOne - penalty;
        totalSec = secOne + penaltyTimeOne;
    }
        if (secTwo > 0 && triesTwo >=1){
            probSolved++;
                
            penaltyTimeTwo = penalty * triesTwo - penalty;    
            totalSec = secOne + secTwo + penaltyTimeOne + penaltyTimeTwo;
        }
            if(secThree>0 && triesThree){
                probSolved++;
                
                penaltyTimeThree = penalty * triesThree - penalty;
                totalSec = secOne + secTwo + secThree + penaltyTimeOne + penaltyTimeTwo + penaltyTimeThree;
            }
            return probSolved;
}

//defining the function that will write our output to a file per team 
void WriteOutputRecord(ofstream &fileOutput, const string &teamName, int probSolved, int totalSec){

    static int lineNum=1;
    int spaceOne= 3, spaceTwo=40, spacethree=2, spaceFour=7;
    
    string space= " ";
    
    fileOutput<<right<<setw(spaceOne)<<lineNum<<":"<<space<<left<<setw(spaceTwo)<<teamName<<space<<right<<setw(spacethree)<<probSolved<<space
    <<setw(spaceFour)<<totalSec<<endl;
    
    lineNum++;
}


