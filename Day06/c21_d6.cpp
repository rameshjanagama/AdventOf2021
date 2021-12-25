//Dec. 03 - Advent of Code 2021 
//--- Day 6: Lanternfish ---

#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <vector>

using namespace std;

struct fish 
{
    //int dob=-10;
    int age=0;
    bool teen = false;
} f;


std::vector<fish> v = {};

void split(std::string& str, std::string delim)
{
    size_t start = 0, end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start); // finds the 'first' occurance from the 'start'
        //std::cout << "[split]" << str.substr(start, end - start)<<","; // extract substring
        int val = std::stoi(str.substr(start, end - start));
        struct fish fi{ val,true};
        v.emplace_back(fi);
    }
}

int readInput()
{
    //Open file
    std::ifstream input{"C:\\Users\\oem\\Downloads\\RAMESH_IMP\\C++\\projects\\helloworld\\input_c21d6.txt"};
    if (!input) {
        std::cout << "Could not open input file 'input_c21d6.txt'!\n";
        return 1;
    }

    int value;
    std::string line;
    while (input) {
        std::getline(input, line);
        if (line.empty()) break;    
        split(line,",");  
        break;      
    }

    return 0;
}

void printOutput( int day = 0){
    std::cout << "DAY " << day << ":" ;
    for(int i=0;i<v.size();i++){
        std::cout << v[i].age << " ";
        //std::cout << "[" << v[i].age << ":" << v[i].dob << ":" << v[i].teen << "] ";
    }
    std::cout << "\n";

}

void part1(int days){
   for(int d=0;d<days;d++){
       long long nbrfishes=v.size();
       for(int i=0;i<nbrfishes;i++){
           //born in today only
           //if ( v[i].dob == d ){continue; }
           v[i].age--;
           if (v[i].teen){
                if (v[i].age<0){
                    struct fish newfish{8,true};
                    v.emplace_back(newfish);
                    v[i].teen=false;
                    v[i].age=6;
                    continue;
                }
           }
           if (!v[i].teen ) {
                if(v[i].age < 0) {
                    struct fish newfish{8,true};
                    v.emplace_back(newfish);
                    v[i].age=6;
                }
           }         
       }
       //printOutput(d+1);
       std::cout << "DAY " << d+1 << ": " << v.size() << "\n";
   }
   
}

int main() {  
   std::cout << "C21 DAY6\n";
   readInput();
   printOutput();
   part1(80);
   //part1(256);
   std::cout << "NUMBER OF FISHES: " << v.size();
   //part2();
   return 0;
}