//Dec. 03 - Advent of Code 2021 
//--- Day 4: Giant Squid ---
// Ramesh Jangama

#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <vector>

using namespace std;

std::vector<int> v = {};
std::vector<int> bo[100]={};
int NB=0;

void split(std::string& str, std::string delim)
{
    size_t start = 0, end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start); // finds the 'first' occurance from the 'start'
        //std::cout << "[split]" << str.substr(start, end - start)<<","; // extract substring
        v.emplace_back(std::stoi(str.substr(start, end - start)));
    }
}

void split2(std::string& str, std::string delim,int idx)
{
    size_t start = 0, end = 0;
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start); // finds the 'first' occurance from the 'start'
        //std::cout << "[split2]:" << idx <<":" << str.substr(start, end - start)<<std::endl; // extract substring
        bo[idx].emplace_back(std::stoi(str.substr(start, end - start)));
    }
}

int readInput()
{
    //Open file
    std::ifstream input{"C:\\Users\\oem\\Downloads\\RAMESH_IMP\\C++\\projects\\helloworld\\input_c21d4_p1.sample.txt"};
    if (!input) {
        std::cout << "Could not open input file 'input_c21d4_p1.sample.txt'!\n";
        return 1;
    }

    int value;
    std::string line;
    int lc=0,b=0,arr=0;
    while (input) {
        std::getline(input, line);
        if (line.empty()) continue;
        lc++;
        if (lc==1) {
          split(line,",");
        }
        else 
        {
            if ( arr!=0 && arr%5==0) {  b++;}
            arr++;
            split2(line," ",b);
        }      
    }
    std::cout<< "***number of borads " <<  b << "\n";
    NB=b;
    return 0;
}

void part1(){
    //std::cout << "part1" << "\n";
    //print b
    //std::cout << "\n print bo:\n";
    for ( int b=0;b<NB;b++){
      for (int r=0;r<bo[0].size();r++) {
          //std::cout << bo[b][r] <<",";
      }
      //std::cout << "\n";
    }
    //std::cout << "\n";

    int br[NB][5]={0};
    int bc[NB][5]={0};
    
     for ( int b=0;b<NB;b++){
         for (int i=0;i<bo[0].size();i++) {
            for ( int idx=0;idx<v.size();idx++){
                if ( bo[b][i] == v[idx]) {
                    bo[b][i] = idx; 
                    break;
                }
            }
        }
    }

    //print again
    //print b
    //std::cout << "\n print bo:\n";
    for ( int b=0;b<NB;b++){
      for (int r=0;r<bo[0].size();r++) {
          //std::cout << bo[b][r] <<",";
      }
      //std::cout << "\n";
    }
    //std::cout << "\n";

    //rows
    int max=-1;
    for ( int b=0;b<NB;b++){
        for (int r=0;r<5;r++) {
            max=-1;
            for (int i=r*5;i<r*5+5;i++){
                if ( bo[b][i]>max) max = bo[b][i];
            }
            br[b][r]=max;
            //std::cout << "row:"<< b <<":"<< r << ":" << max <<  "\n";
        }
    }

    //column
    max=-1;
    for ( int b=0;b<NB;b++){
        for (int c=0;c<5;c++) {
            max=-1;
            for (int i=c;i<=bo[0].size();i=i+5){
                if  ( b==2 && c==4) { 
                    //std::cout <<"[" << bo[b][i] << "],";
                }
                if ( bo[b][i]>max) max = bo[b][i];
            }
            bc[b][c]=max;
            //std::cout << "col:" << b <<":"<< c << ":" << max <<  "\n";
        }
    }

    //find min
    int min=99999,minbo=-1,minrow=1,mincol=-1;
    int localmax=0;
    int maxbo=0;
    int win[NB]={0};
    for ( int b=0;b<NB;b++){
        //rows 
        for ( int r=0;r<5;r++){
            if(br[b][r] < min ) {
                min=br[b][r];
                minbo=b;
                minrow=r;
            }
        }
        for ( int r=0;r<5;r++){
            if(bc[b][r] < min ) {
                min=bc[b][r];
                minbo=b;
                mincol=r;
            }
        }
        win[b]=min;
    }

    //std::cout << "minbo=" << minbo << ",minrow=" << minrow << ",mincol=" << mincol << "\n";
    //std::cout << "min row " << br[minbo][minrow] << "\n";
    //std::cout << "min col " << bc[minbo][mincol] << "\n";
    //std::cout << "local max " << localmax<< "\n";
    //std::cout << "maxb" << maxbo << "\n";    
    
    if ( br[minbo][minrow]  < bc[minbo][mincol]){
        int sum=0;
        for (int i=0;i<bo[minbo].size();i++){
            if( bo[minbo][i] > br[minbo][minrow] )
                 sum+=v[bo[minbo][i]];
        }
        //std::cout << "ALL SUM:" << sum <<"\n";
        //std::cout << "LAST VALUE " << v[br[minbo][minrow]]<<"\n";
        std::cout << "Part1 :" << sum*v[br[minbo][minrow]] << "\n";
    }
    else 
    {
        int sum=0;
        for (int i=0;i<bo[minbo].size();i++){
            if( bo[minbo][i] > bc[minbo][mincol] )
                 sum+=v[bo[minbo][i]];
        }
        //std::cout << "ALL SUM:" << sum <<"\n";
        //std::cout << "LAST VALUE " << v[bc[minbo][mincol]]<<"\n";
        std::cout<< "Part1 :"  << sum*v[bc[minbo][mincol]] << "\n";
    }

    // part 2
    // each board wins after 
    min=99999,minbo=-1,minrow=1,mincol=-1;
    localmax=0;
    maxbo=0;
    for ( int b=0;b<NB;b++){
        //rows 
        min=99999;
        for ( int r=0;r<5;r++){
            if(br[b][r] < min ) {
                min=br[b][r];
                minbo=b;
                minrow=r;
            }
        }
        for ( int r=0;r<5;r++){
            if(bc[b][r] < min ) {
                min=bc[b][r];
                minbo=b;
                mincol=r;
            }
        }
        //std::cout << "board " << b << " winds after " << min << "steps\n";
        win[b]=min;
    }

    max=-1;
    maxbo=-1;
    for ( int b=0;b<NB;b++){
        if (win[b] > max ) {
            max=win[b];
            maxbo=b;
        }
    }
    //std::cout << " max win " << max << ",maxbo=" << maxbo <<"\n";    
    int sum=0;
    for (int i=0;i<bo[maxbo].size();i++){
        if( bo[maxbo][i] > max )
                sum+=v[bo[maxbo][i]];
    }
    //std::cout << "ALL SUM:" << sum <<"\n";
    //std::cout << "LAST VALUE " << v[max]<<"\n";
    std::cout << "Part2 :" << sum*v[max] << "\n";
}

int main() {  
   std::cout << "C21 DAY4\n";
   readInput();
   part1();
   return 0;
}