

#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;

#define MAX_NODE 5

/// My Graph

int Graph[MAX_NODE][MAX_NODE]={{0,1,1,1,0},
                               {1,0,0,0,0},
                               {1,0,0,0,1},
                               {1,0,0,0,0},
                               {0,0,1,0,0}
                               };
int mark[MAX_NODE];

int DegreeEachNode[MAX_NODE];  /// initially zeros

///############################################################
/// FUNCTION DECLATION
void printGraph(){

   for(int i =0; i<MAX_NODE; i++){
    for(int j =0;j<MAX_NODE; j++){
        printf("%d ",Graph[i][j]);
    }
    printf("\n");
   }
}
void CalDegree(){

     for(int i =0; i<MAX_NODE; i++){
    for(int j =0;j<MAX_NODE; j++){
        if(Graph[i][j] == 1){
            DegreeEachNode[i]++; /// Heare i'th each node value increase
            }
    }

   }
}

void printDegree(){
  printf("NODE          DEGREE\n");
  printf("---------------------\n" );
  for(int node = 0; node<MAX_NODE; ++node){

    printf("%d              %d\n",node,DegreeEachNode[node]);
  }
}
///#############################################################

///BFS part

int HiericalValue[MAX_NODE]={0};  /// intialize HiericlcalValue is 0's.
void BFS(){

queue<int> Q;  /// Queue for node store

        for(int eachnode =0; eachnode<MAX_NODE; eachnode++){
            Q.push(eachnode);   /// Indivisual Source node store in queue
            int root = eachnode;
            for(int i=0;i<MAX_NODE;i++)
                mark[i] = 0;
            while(!Q.empty()){

                int FrontNode = Q.front();


                for(int node=0; node<MAX_NODE;++node){
                    /// Main logic
                    if(mark[node] ==0 &&root!=node && Graph[FrontNode][node]== 1 && DegreeEachNode[FrontNode]<=DegreeEachNode[node]){
                        printf("%d -> %d\n",FrontNode,node);  /// Debugging checking
                        HiericalValue[root] = HiericalValue[root]+1;   /// Here is each node Hiericalpatch value increase.
                        printf("Hier%d= %d\n",root,HiericalValue[root]);  ///Debugging checking
                        Q.push(node);  /// child node store in queue
                        mark[node] = 1;
                    }
                }
                Q.pop();/// Erase front node from Queue

             }

        }

//        while(!Q.empty()){
//
//            cout<<Q.front()<<" ";
//            Q.pop();
//
//
//        }

}


void printHiericalValue(){

    printf("NODE          HireclaPath\n");
    printf("---------------------------\n");

    for(int node = 0; node<MAX_NODE; ++node){

        printf("%d                  %d\n",node,HiericalValue[node]);
    }

}




int main(){

printGraph();
CalDegree();
printDegree();
BFS();
printHiericalValue();

return 0;
}
