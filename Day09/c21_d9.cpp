//Dec. 03 - Advent of Code 2021 

#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <vector>
#include <string>

using namespace std;

std::vector<string> v = {};
std::vector<int> bo[100]={};
int NB=0;

const int MAX=100;
const int MAXJ=100;
int arr[MAX][MAXJ]={9};
int visit[MAX][MAXJ]={9};

int readInput()
{
    //Open file
    std::ifstream input{"C:\\Users\\oem\\Downloads\\RAMESH_IMP\\C++\\projects\\helloworld\\input_c21d9.txt"};
    if (!input) {
        std::cout << "Could not open input file 'input_c21d4_p1.sample.txt'!\n";
        return 1;
    }

    int value;
    std::string line;
    int lc=0,b=0;
    while (input) {
        std::getline(input, line);
        if (line.empty()) continue;
        for (int i=0;i<MAXJ;i++){
            char c= line[i];
            arr[lc][i]= int(c)-48;
        }
        lc++;
    }
    return 0;
}

void reset() {
    for ( int i=0;i<MAX;i++){
        for ( int j=0;j<MAXJ;j++){
            visit[i][j]=0;
        }
        //std::cout << "\n";
    }
}

void set() {
    for ( int i=0;i<MAX;i++){
        for ( int j=0;j<MAXJ;j++){
            visit[i][j]=1;
        }
        //std::cout << "\n";
    }
}

int visitcount() {
    int count=0;
    for ( int i=0;i<MAX;i++){
        for ( int j=0;j<MAXJ;j++){
            if ( visit[i][j]==1)
               count++;
        }
        //std::cout << "\n";
    }
    return count;
}

void part1(){
    //std::cout << "part1" << "\n";
    int lowi[MAX]={9};
    int lowj[MAXJ]={9};

    /*for ( int i=0;i<MAX;i++){
        for ( int j=0;j<MAXJ;j++){
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }*/

    //return;
    //std::cout << " " << "\n";
    int sum=0;
    for ( int i=0;i<MAX;i++){
      for ( int j=0;j<MAXJ;j++){
          //std::cout << arr[i][j] ;
          bool up=false;
          bool down=false;
          bool right=false;
          bool left=false;

          if ( i-1>=0 )  {
              if(arr[i][j] < arr[i-1][j]) left=true;
          } else {
              left=true;
          }
          if ( i+1<MAX) {
              if(arr[i][j] < arr[i+1][j]) right=true;
         } else {
              right=true;
         }

          if (j-1>=0)  {   
              if(arr[i][j] < arr[i][j-1]) up=true;
          } else {
             up=true;
          }

          if (j+1<MAXJ ) {
             if(arr[i][j] < arr[i][j+1]) down=true;
          } else {
             down=true;
          }

          if (up && down && left && right) {
              //std::cout << "["<< arr[i][j] << "] ";
              sum+= (arr[i][j])+1;
          }        
      }
      //std::cout << "\n";
    }
    std::cout << "Part1 " << sum << "\n";
}

int basin(int li,int lj){
    int sum=0;
    for ( int i=li;i<MAX;i++){
      for ( int j=lj;j<MAXJ;j++){
          //std::cout << arr[i][j] ;
          if (i<0 || i>=MAX || j<0 || j>=MAXJ)
                  return 0;
          if (visit[i][j]==1)
              return 0;
          if ( arr[i][j]==9 ) 
               return 0;
          visit[i][j]=1;
          return 1+ basin( i-1,j)+ basin(i+1,j)+basin(i,j-1)+basin(i,j+1);              
      }
    }
    //std::cout << "control should not come here" <<endl;
    return sum;
}

void part2(){
    //std::cout << "part2" << "\n";
    int lowi[MAX]={9};
    int lowj[MAXJ]={9};
    std::vector<int> b{};

    for ( int i=0;i<MAX;i++){
        for ( int j=0;j<MAXJ;j++){
            //std::cout << arr[i][j];
        }
        //std::cout << "\n";
    }
    
    //return;
    //std::cout << " " << "\n";
    int sum=0;
    for ( int i=0;i<MAX;i++){
      for ( int j=0;j<MAXJ;j++){
          //std::cout << arr[i][j] ;
          bool up=false;
          bool down=false;
          bool right=false;
          bool left=false;

          if ( i-1>=0 )  {
              if(arr[i][j] < arr[i-1][j]) left=true;
          } else {
              left=true;
          }
          if ( i+1<MAX) {
              if(arr[i][j] < arr[i+1][j]) right=true;
          } else {
              right=true;
          }

          if (j-1>=0)  {   
              if(arr[i][j] < arr[i][j-1]) up=true;
          } else {
             up=true;
          }

          if (j+1<MAXJ ) {
             if(arr[i][j] < arr[i][j+1]) down=true;
          } else {
             down=true;
          }

          if (up && down && left && right) {
              //std::cout << "["<< arr[i][j] << "] ";
              //lowest point found 
              sum+= (arr[i][j])+1;
              reset();
              b.emplace_back(basin(i,j));
              //std::cout << " basin size " << visitcount() << endl;
              reset();
          }        
      }
        //std::cout << "\n";
    }
    std::cout << "Part1 : " << sum << "\n";
    //std::cout << "size of basin " << b.size() << "\n";
    sort(b.begin(), b.end(),greater<int>());
    std::cout << "Part2 : " << b[0]*b[1]*b[2] <<endl;
}

int main() {  
   std::cout << "C21 DAY9\n";
   readInput();
   //part1();
   part2();
   //int part1_res = part2();
   //std::cout << "part1_res: " << part1_res << "\n";
   return 0;

}         