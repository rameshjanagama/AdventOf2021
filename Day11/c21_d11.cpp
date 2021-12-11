// Advent of Code 2021 
// Day 11: Dumbo Octopus 
// Ramesh Janagama

#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int MAX=10;

int arr[MAX][MAX]={9};
int visit[MAX][MAX]={0};

struct cell{
    int i;
    int j;
};

int readInput()
{
    std::ifstream input{"C:\\Users\\oem\\Downloads\\RAMESH_IMP\\C++\\projects\\helloworld\\input_c21d11.txt"};
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
        for (int i=0;i<MAX;i++){
            char c= line[i];
            arr[lc][i]= int(c)-48;
        }
        lc++;
    }
    return 0;
}

void reset() {
    for ( int i=0;i<MAX;i++){
        for ( int j=0;j<MAX;j++){
            visit[i][j]=0;
        }
    }
}

void printInput(){
    for ( int i=0;i<MAX;i++){
        for ( int j=0;j<MAX;j++){
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
    std::cout << " " << "\n";
}

void increase(){
    for ( int i=0;i<MAX;i++){
        for ( int j=0;j<MAX;j++){           
             arr[i][j]++;
        }
    }
}

int lights(){
    int count; 
    for ( int i=0;i<MAX;i++){
        for ( int j=0;j<MAX;j++){
            if (arr[i][j] ==0) count++;
        }
    }
    return count;
}

void part2(){

    //printInput();
    int total=0;
    for ( int i=0;i<1000;i++){
        reset();
        increase();
        std::queue<struct cell> q;
        
        //push all lights to Q
        for ( int ii=0;ii<MAX;ii++){
            for ( int jj=0;jj<MAX;jj++){
                if( arr[ii][jj] == 10) {
                    struct cell val{ii,jj};
                    q.push(val);
                }
            }
        }         
    
        while(!q.empty())
        {
            struct cell c = q.front();
            q.pop();
            //std::cout << "popped" << c.i << "," << c.j << "(" << q.size() << ")" << endl; 
            if (c.i<0 || c.i>=MAX || c.j<0 || c.j>=MAX) continue;
            if (visit[c.i][c.j]==1 ) continue; 
            if (arr[c.i][c.j] <= 9 &&  arr[c.i][c.j] != 0) {
                arr[c.i][c.j]++;
                visit[c.i][c.j]=0;
            }
            
            if (arr[c.i][c.j] == 10) {
                arr[c.i][c.j] =0;
                visit[c.i][c.j]=1;
                struct cell x1{c.i-1,c.j-1}; q.push(x1);visit[c.i-1][c.j-1]=0;
                struct cell x2{c.i-1,c.j  }; q.push(x2);visit[c.i-1][c.j  ]=0;
                struct cell x3{c.i-1,c.j+1}; q.push(x3);visit[c.i-1][c.j+1]=0;
                struct cell x4{c.i  ,c.j-1}; q.push(x4);visit[c.i  ][c.j-1]=0;

                struct cell x5{c.i  ,c.j+1}; q.push(x5);visit[c.i  ][c.j+1]=0;
                struct cell x6{c.i+1,c.j-1}; q.push(x6);visit[c.i+1][c.j-1]=0;
                struct cell x7{c.i+1,c.j  }; q.push(x7);visit[c.i+1][c.j  ]=0;
                struct cell x8{c.i+1,c.j+1}; q.push(x8);visit[c.i+1][c.j+1]=0;
            }
        }        
        
        std::cout << "debug: after steps " << i+1 << endl;
        //printInput();
        int n=lights();
        total+=n;
        std::cout << "debug: zeros = " << lights() << "   ,n=" << n << ",total=" << total << endl;
        if( n == 100){
            std::cout << "Part2 Puzzle Ans " << i+1 << " iterations\n";
            break;
        }  
        /*if( i+1 == 100){
            std::cout << "Part1 Puzzle Ans " << total<< " iterations\n";
            //break;
        }*/
    }
    std::cout << "Part1 Puzzle Ans " << total << "\n";
}

int main() {  
   std::cout << "C21 DAY11\n";
   readInput();
   part2();
   return 0;
}