// Advent of Code 2021 
// Day 12: Dumbo Octopus 
// Ramesh Janagama

#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct cell{
    std::string s;
    std::string e;
};

std::vector<cell> v={};
std::queue<pair<std::string, std::vector<std::string>> > q;
std::map<std::string,int> visited;

void split(std::string& str, std::string delim)
{
    size_t start = 0, end = 0;
    int count=0;
    struct cell c;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start); // finds the 'first' occurance from the 'start'
        //std::cout << "[split]" << str.substr(start, end - start)<<","; // extract substring
        //v.emplace_back(std::stoi(str.substr(start, end - start)));
        if( count ==0) 
            c.s =str.substr(start, end - start);
        else 
            c.e =str.substr(start, end - start);
        count++;
    }
    v.emplace_back(c);
}

int readInput()
{
    std::ifstream input{"C:\\Users\\oem\\Downloads\\RAMESH_IMP\\C++\\projects\\helloworld\\input_c21d12.txt"};
    if (!input) {
        std::cout << "Could not open input file 'input_c21d11.txt'!\n";
        return 1;
    }

    int value;
    std::string line;
    int lc=0;
    while (input) {
        std::getline(input, line);
        if (line.empty()) continue;
        split(line,"-");
        lc++;
    }
    return 0;
}

void printInput(){
    for ( int i=0;i < v.size()-1;i++){
        std::cout << v[i].s  << " - " << v[i].e << "\n";
    }
}

bool isLower(std::string str){
    return std::any_of(str.begin(), str.end(), ::islower);
}

int LowerChars(std::vector<std::string> v_tmp )
{
    int count=0;
    for (int t=0;t<v_tmp.size();t++){
        if (isLower(v_tmp[t])){
            count++;
        }       
    }
    return count; 
}

void displaypath(std::vector<std::string> v_tmp )
{
    std::cout << "PATH:"; 
    for (int t=0;t<v_tmp.size();t++){
        std::cout << v_tmp[t] << " ";     
    }
    std::cout << " end\n"; 
}

bool isDuplicated(std::vector<std::string> v_tmp) {
    for (int t=0;t<v_tmp.size();t++){
        if (isLower(v_tmp[t])){
            int cnt = count(v_tmp.begin(), v_tmp.end(), v_tmp[t]);
            if ( cnt == 2) return true;       
        }             
    }
    return false; 
}

void DFS ( ) {
    int count=0;
    while (!q.empty()){
        pair<std::string, std::vector<std::string>> elt = q.front();
        std::string p = elt.first;
        std::vector<std::string> path = elt.second;
        //std::cout << "FRONT = " << p << endl;
        for ( int j=0;j<v.size()-1;j++){
            std::string otherend ="";
            if( v[j].s == p ) 
                otherend = v[j].e;
            else if  (v[j].e == p )
                otherend = v[j].s;
            else 
                continue; 
            
            if( otherend == p) {
                std::cout << "***cycle **** - skipped" << otherend << endl;
                continue;
            }               

            if( otherend == "start") {
                //std::cout << "***start again - skipped **** " << otherend << endl;
                 continue;
            }

            if( otherend == "end") {
                 count++;
                 //displaypath(path);
                 continue; 
            }
            //std::cout << "***pushed **** " << otherend << endl;

            if( isLower(otherend) && 
                isDuplicated(path) && 
                std::count(path.begin(), path.end(), otherend) >= 1
               )               
            {
                //std::cout << "***alredy visited skipped **** " << otherend << endl;
                continue;
            }
            
            std::vector tmp = path;
            tmp.emplace_back(otherend);            
            pair<std::string, std::vector<std::string>> tmpelt = { otherend, tmp };
            q.push(tmpelt) ;
        }   
        q.pop();
    }

    std::cout << "Part2 " <<count << endl;
}

void part1(){
    std::vector<std::string> path = { "start"};
    pair<std::string, std::vector<std::string>> elt = {"start", path };
    q.push(elt);
    DFS();
}

int main() {  
   std::cout << "C21 DAY12\n";
   readInput();
   printInput();
   part1();
   return 0;
}