// Advent of Code 2021 
// --- Day 13: Transparent Origami ---
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
#include <algorithm>

using namespace std;

const int MAX=2000;
int arr[MAX][MAX] ={0};

int MAXX=0;
int MAXY=0;

std::vector<int> folds = {};
std::vector<char> axis = {};

void split(std::string& str, std::string delim)
{
    size_t start = 0, end = 0;
    int count=0;
    int i=0,j=0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start); // finds the 'first' occurance from the 'start'
        if( count ==0) 
            i =std::stoi(str.substr(start, end - start));
        else 
            j =std::stoi(str.substr(start, end - start));
        count++;
    }
    arr[j][i]=1;

    if (j> MAXX)
         MAXX=j;
    if (i> MAXY)
         MAXY=i;         
}

void split2(std::string& str, std::string delim)
{
    size_t start = 0, end = 0;
    int count=0;
    int i=0,j=0;
    std::string tmpstr ="";
    int val =0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start); // finds the 'first' occurance from the 'start'
        if( count ==0) {
              tmpstr =str.substr(start, end - start);
        }
        else 
        {
            val =std::stoi(str.substr(start, end - start));
        }
        count++;
    }
    folds.emplace_back(val);
    axis.emplace_back(tmpstr[tmpstr.length()-1]);
}

int readInput()
{
    std::ifstream input{"C:\\Users\\oem\\Downloads\\RAMESH_IMP\\C++\\projects\\helloworld\\input_c21d13.txt"};
    if (!input) {
        std::cout << "Could not open input file 'input_c21d13.txt'!\n";
        return 1;
    }

    int value;
    std::string line;
    int lc=0;
    std::string needlex="fold along";
    std::string needley="fold along y=";
    while (input) {
        std::getline(input, line);
        if (line.empty()) continue;

        auto it = std::search(line.begin(), line.end(),
                    std::boyer_moore_searcher(
                        needlex.begin(), needlex.end()));
        if(it != line.end()) {
            split2(line, "=");
        }
        else
        {
            split(line,",");
        }
        lc++;
    }
    return 0;
}

void printInput(){
    std::cout << "MAXX=" << MAXX << ",MAXYY=" << MAXY << endl;
    for ( int i=0;i <= MAXX;i++){
        for ( int j=0;j <= MAXY;j++){
            if ( arr[i][j] ==1 )
                std::cout << "#" << "";
            else 
                std::cout << "." << "";
        }
        std::cout << "\n";
    }
    for (int t=0;t<folds.size()-1;t++){
        //std::cout << "fold " << axis[t] << "=" << folds[t] << endl;
    }
}

void countDots() {
    int count=0; 
    int countz=0;
    for ( int i=0;i <= MAXX;i++){
       for ( int j=0;j <= MAXY;j++){
            if ( arr[i][j] ==1 )  
            count++;
            else countz++;
        }
    }
    std::cout << "COUNT: #=" << count <<",.=" << countz <<endl;
}

void normalize(int step){
    if(axis[step] == 'y')
    {
        for(int d= (folds[step])+1,u= (folds[step])-1; d<=MAXX && u>=0; d++,u-- ){
            //std::cout << "  d=" << d << ",u=" << u << endl;
            for( int j=0; j<=MAXY;j++){
                if (arr[d][j] == 1 || arr[u][j] == 1){
                    arr[u][j] = 1;
                    arr[d][j] = 0;
                }
            }
        } 

        //clear yrows 
        for( int j=0; j<=MAXX;j++){
            arr[folds[step]][j]=0;
        }
        MAXX= folds[step] ;
    }
    else {
        //std::cout << "x axis" << ", " <<  folds[step] << endl;
        for(int r= (folds[step])+1,l= (folds[step])-1; r<=MAXY && l>=0; r++,l-- ){
            //std::cout << "  r=" << r << ",l=" << l << endl;
            for( int j=0; j<=MAXX;j++){
                if (arr[j][r] == 1 || arr[j][l] == 1){
                    arr[j][l] = 1;
                    arr[j][r] = 0;
                }
            }
        } 

        //clear yrows 
        for( int j=0; j<=MAXY;j++){
            arr[j][folds[step]]=0;
        }
        MAXY= folds[step];
    }
}

void part1(){
    for ( int f=0; f< folds.size()-1;f++){
        std::cout << "===>fold " << folds[f] << ",axis=" << axis[f] << endl;
        normalize(f);
        //std::cout << "DEBUG:" << endl;
        //printInput();
        countDots();
    }
}

int main() {  
   std::cout << "C21 DAY13\n";
   readInput();
   //printInput();
   part1();
   printInput();
   return 0;
}