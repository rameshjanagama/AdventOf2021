// Advent of Code 2021 
//--- Day 25: Sea Cucumber ---
// Ramesh Janagama

#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <vector>
#include <string>

using namespace std;

std::vector<string> arr = {};

int readInput()
{
    //Open file
    std::ifstream input{"C:\\Users\\oem\\Downloads\\RAMESH_IMP\\C++\\projects\\helloworld\\input_c21d25.txt"};
    if (!input) {
        std::cout << "Could not open input file 'input_c21d25_p1.sample.txt'!\n";
        return 1;
    }

    int value;
    std::string line;
    int lc=0;
    while (input) {
        std::getline(input, line);
        if (line.empty()) continue;
        arr.emplace_back(line);
        lc++;
    }
    arr.pop_back();//due to bug duplicate was loading windows
    return 0;
}

void display(){
    for ( int i=0;i<arr.size();i++){
        for ( int j=0;j<arr[0].size();j++){
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
}

void part1(){
    //display();
    for (int steps=0;steps<10000;steps++) {
        int move=0;
        for (int facing=0;facing<2;facing++) {
            std::vector<std::string> tmparr=arr;          
            for ( int i=0;i<arr.size();i++){
                for ( int j=0;j<arr[0].size();j++){
                    if (facing==0) { 
                        if (arr[i][j] == '>')   
                            //east -> move right
                            if ( j+1<arr[0].size() ) {
                                if(arr[i][j+1]=='.') {
                                    tmparr[i][j+1]='>';
                                    tmparr[i][j]='.';
                                    move++;
                                }
                            } else {
                                if(arr[i][0]=='.') {
                                    tmparr[i][0]='>';
                                    tmparr[i][j]='.';
                                    move++;
                                }
                            }
                    }
                    else  { 
                        if (arr[i][j] == 'v')               
                            //south -> move down
                            if ( i+1<arr.size() ) {
                                if(arr[i+1][j]=='.') {
                                    tmparr[i+1][j]='v';
                                    tmparr[i][j]='.';
                                    move++;
                                }
                            } else {
                                if(arr[0][j]=='.') {
                                    tmparr[0][j]='v';
                                    tmparr[i][j]='.';
                                    move++;
                                }
                            }
                    }
                }    
            }  
            arr=tmparr;      
        }
        //std::cout << "after step " << steps+1 << endl;
        //display(); 
        if (move==0)   {
            std::cout << "part1 = " << steps+1 << endl; 
            return;
        }
        //std::cout << "moves = " <<  move << " after steps "  << steps+1 << endl;
    }

}

int main() {  
   std::cout << "C21 DAY25\n";
   readInput();
   part1();
   //part2();
   return 0;
}