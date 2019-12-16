#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<queue>
#include <time.h>
#include <algorithm>
using namespace std;

#define Tnode 500

int NetworkD[Tnode][Tnode];
int Network_hierarchy[Tnode][Tnode];
int arrRandChoosing[Tnode];
int Degree_NetworkD[Tnode];
int Degree_Network_H[Tnode];
int HiericalValue[Tnode]={0};
int Hierarchy_NetworkD[Tnode];
//double arr_sortHierarchy[Tnode];

void NetworkGrow_networkD(double arr[Tnode][3], int size);
void show_NetworkD();
void show_Network_hierarchy();
void show_Degree_NetworkD();
void show_Hierarchy_NetworkD();
void show_Graph(int countNode);
void show_all_info(int countNode);
double BFS(int Graph[][Tnode],int DegreeEachNode[]);
///zihad edit
void graph_vector(int NetworkD[][Tnode]);
void bfs_D(int src);
void vector_claer();
double Network_Diameter(int NetworkD[][Tnode]);
///zihad edit
vector<int>G[Tnode];
double DM_sum=0;



int Network_C[Tnode][Tnode]={{0,1,1,0,0,0,0,0},
                               {1,0,0,1,0,0,0,0},
                               {1,0,0,0,0,1,1,1},
                               {0,1,0,0,1,0,0,0},
                               {0,0,0,1,0,0,0,0},
                               {0,0,1,0,0,0,0,0},
                               {0,0,1,0,0,0,0,0},
                               {0,0,1,0,0,0,0,0}

                               };
int Degree_C[8] = {2,2,4,2,1,1,1,1};

int main()
{
    srand(time(NULL));
    double arr[Tnode][3];



    //printf("The F of Network _C is %lf\n", BFS(Network_C, Degree_C));
    /*for(int i=1;i<=10;i++){
        NetworkGrow();
    printf("The F of Network is %lf\n", BFS(NetworkD, Degree_NetworkD));

    }
    */
   int TNstep = (Tnode-30)/20;
   for(int i=0;i<TNstep;i++)
   {
       arr[i][0] = 0;
       arr[i][1] = 0;
       arr[i][2] = 0;

   }
   for(int i=0;i<100;i++)
   {
       NetworkGrow_networkD(arr);

   }

   for(int i=0;i<TNstep;i++)
   {
       arr[i][0] = log(arr[i][0]);
       arr[i][1] = log(arr[i][1]/100);
       arr[i][2] = log(arr[i][2]/100);
   }

   FILE *fp1=fopen("myThesis_F_vs_node.csv","w");
   FILE *fp2=fopen("myThesis_F_vs_Diameter.csv","w");
   FILE *fp3=fopen("myThesis_D_vs_N.csv","w");
   fprintf(fp1,"F_vs_node in log\n\n");
   fprintf(fp2,"F_vs_Diameter in log\n\n");
   fprintf(fp3,"D_vs_N in log\n\n");
   for(int i=0;i<TNstep;i++)
   {
     //  printf("Node-F-Diameter\n");

       fprintf(fp1,"%lf,%lf\n",arr[i][0],arr[i][1]);
       fprintf(fp2,"%lf,%lf\n",arr[i][2],arr[i][1]);
       fprintf(fp3,"%lf,%lf\n",arr[i][0],arr[i][2]);
   }
   fclose(fp1);
   fclose(fp2);
   fclose(fp3);

   //printf(" the network dia meter is %lf\n",Network_Diameter());
   //show_NetworkD();





    return 0;
}

void NetworkGrow_networkD(double arr[Tnode][3], int size)
{
    for(int i=0;i<Tnode;i++)
        for(int j=0;j<Tnode;j++)
            NetworkD[i][j] = 0;

    for(int i=0;i<Tnode;i++)
        Degree_NetworkD[i] = 0;

    for(int i=0;i<Tnode;i++)
        Hierarchy_NetworkD[i] = 0;

    int countNode = 1;
    NetworkD[0][0] = 0;

    for(int i=countNode;i<size;i++)
    {
        for(int j=0;j<countNode;j++)
            arrRandChoosing[i] = 0;

        int NumSubNode = rand()%countNode + 1;
        int nthNode = rand()%countNode;
        arrRandChoosing[nthNode] = 1;

        int degree = Degree_NetworkD[nthNode];
        int maxDegree=degree;
        int selectedNode_for_degree = nthNode;

        for(int j = 1; j<NumSubNode; j++)
        {
            for(int k=0;k<countNode;k++)
            {
                nthNode = rand()%countNode;
                if(k==countNode-1 || arrRandChoosing[nthNode] == 0)
                {
                    arrRandChoosing[nthNode] = 1;
                    break;
                }
            }

            degree = Degree_NetworkD[nthNode];
            hierarchy = Hierarchy_NetworkD[nthNode];


            if(degree>maxDegree)
            {
                maxDegree = degree;
                selectedNode_for_degree = nthNode;
            }

        }

        NetworkD[selectedNode_for_degree][countNode] = 1;
        NetworkD[countNode][selectedNode_for_degree] = 1;

        Degree_NetworkD[selectedNode_for_degree]++;
        Degree_NetworkD[countNode]++;


        Hierarchy_NetworkD[countNode] = Hierarchy_NetworkD[selectedNode_for_hierarchy]+1;

        //printf("###Adding %dth node:\n\n",countNode+1);
        //show_all_info(countNode);

        countNode++;


        //printf("Iteration no %d:\n%d %d %d\n\n\n\n",i,NumSubNode,nthNode,selectedNode_for_degree);


    if((countNode-30)%20==0)
    {

       int Nstep = (countNode-30)/20;
       arr[Nstep-1][0] = countNode;
      // printf("node - > %lf\n",arr[Nstep][0]);
       arr[Nstep-1][1] = arr[Nstep-1][1] + BFS(NetworkD, Degree_NetworkD);
       arr[Nstep-1][2] = arr[Nstep-1][2] + Network_Diameter(NetworkD);
    }

 }
}

void NetworkGrow2_with_hierarchy(double arr[Tnode][3], int size)
{
    for(int i=0;i<Tnode;i++)
        for(int j=0;j<Tnode;j++)
            Network_hierarchy[i][j] = 0;


    for(int i=0;i<Tnode;i++)
        Degree_Network_H[i] = 0;

    for(int i=0;i<Tnode;i++)
        Hierarchy_NetworkD[i] = 0;

    int countNode = 1;
    NetworkD[0][0] = 0;
    Network_hierarchy[0][0] = 0;
    Hierarchy_NetworkD[0] = 0;

    for(int i=countNode;i<size;i++)
    {
        for(int j=0;j<countNode;j++)
            arrRandChoosing[i] = 0;

        int NumSubNode = rand()%countNode + 1;
        int nthNode = rand()%countNode;
        arrRandChoosing[nthNode] = 1;

        int degree = Degree_NetworkD[nthNode];
        int hierarchy = Hierarchy_NetworkD[nthNode];

        int maxDegree=degree;
        int maxHierarchy=hierarchy;
        int selectedNode_for_degree = nthNode;
        int selectedNode_for_hierarchy = nthNode;

        for(int j = 1; j<NumSubNode; j++)
        {
            for(int k=0;k<countNode;k++)
            {
                nthNode = rand()%countNode;
                if(k==countNode || arrRandChoosing[nthNode] == 0)
                {
                    arrRandChoosing[nthNode] = 1;
                    break;
                }
            }

            degree = Degree_NetworkD[nthNode];
            hierarchy = Hierarchy_NetworkD[nthNode];

            if(hierarchy>maxHierarchy)
            {
                maxHierarchy = hierarchy;
                selectedNode_for_hierarchy = nthNode;
            }
        }

        NetworkD[selectedNode_for_degree][countNode] = 1;
        NetworkD[countNode][selectedNode_for_degree] = 1;

        Network_hierarchy[selectedNode_for_hierarchy][countNode] = 1;
        Network_hierarchy[countNode][selectedNode_for_hierarchy] = 1;

        Degree_NetworkD[selectedNode_for_degree]++;
        Degree_NetworkD[countNode]++;

        Degree_Network_H[selectedNode_for_hierarchy]++;
        Degree_Network_H[countNode]++;

        Hierarchy_NetworkD[countNode] = Hierarchy_NetworkD[selectedNode_for_hierarchy]+1;

        //printf("###Adding %dth node:\n\n",countNode+1);
        //show_all_info(countNode);

        countNode++;


        //printf("Iteration no %d:\n%d %d %d\n\n\n\n",i,NumSubNode,nthNode,selectedNode_for_degree);


    if((countNode-30)%20==0)
    {

       int Nstep = (countNode-30)/20;
       arr[Nstep-1][0] = countNode;
      // printf("node - > %lf\n",arr[Nstep][0]);
       arr[Nstep-1][1] = arr[Nstep-1][1] + BFS(NetworkD, Degree_NetworkD);
       arr[Nstep-1][2] = arr[Nstep-1][2] + Network_Diameter(NetworkD);
    }

 }
}


void show_NetworkD()
{
    printf("The NetworkD is given below:\n\n");
    for(int i=0;i<Tnode;i++)
    {
        for(int j=0;j<Tnode;j++)
            printf("%d  ",NetworkD[i][j]);
        printf("\n");
    }
    printf("\n\n\n\n");

}
void show_Network_hierarchy()
{
    printf("The Network_hierarchy is given below:\n\n");
    for(int i=0;i<Tnode;i++)
    {
        for(int j=0;j<Tnode;j++)
            printf("%d  ",Network_hierarchy[i][j]);
        printf("\n");
    }
    printf("\n\n\n\n");
}

void show_Degree_NetworkD()
{
    printf("The Degree_NetworkD is given below:\n\n");
    for(int i=0;i<Tnode;i++)
        printf("%d ",Degree_NetworkD[i]);
    printf("\n\n\n\n");
}

void show_Hierarchy_NetworkD()
{
    printf("The Hierarchy_NetworkD is given below:\n\n");
    for(int i=0;i<Tnode;i++)
        printf("%d ",Hierarchy_NetworkD[i]);
    printf("\n\n\n\n");
}



void show_all_info(int countNode)
{
    //show_NetworkD();
    //show_Degree_NetworkD();
    //show_Network_hierarchy();
    //show_Hierarchy_NetworkD();
    //show_Graph(countNode);

}


double BFS(int Graph[][Tnode],int DegreeEachNode[])
{

queue<int> Q;
queue<int> Q2;
int mark[Tnode]={0};
int mark2[Tnode]={0};
int HiericalValue[Tnode] = {0};
int HiericalValue_for_same[Tnode] = {0};


        for(int eachnode =0; eachnode<Tnode; eachnode++){
            Q.push(eachnode);
            int root = eachnode;
            for(int i=0;i<Tnode;i++)
                mark[i] = 0;
            while(!Q.empty()){

                int FrontNode = Q.front();


                for(int node=0; node<Tnode;++node)
                {
                    if(mark[node] ==0 &&root!=node && Graph[FrontNode][node]== 1 && DegreeEachNode[FrontNode]<=DegreeEachNode[node])
                    {
                        HiericalValue[root] = HiericalValue[root]+1;
                        Q.push(node);
                        mark[node] = 1;
                    }
                }
                Q.pop();

             }

        }

        for(int eachnode =0; eachnode<Tnode; eachnode++)
        {
            Q2.push(eachnode);
            int root = eachnode;
            for(int i=0;i<Tnode;i++)
                mark2[i] = 0;
            while(!Q2.empty()){

                int FrontNode = Q2.front();


                for(int node=0; node<Tnode;++node)
                {
                    if(mark2[node] ==0 &&root!=node && Graph[FrontNode][node]== 1 && DegreeEachNode[FrontNode]==DegreeEachNode[node])
                    {
                        HiericalValue_for_same[root] = HiericalValue_for_same[root]+1;
                        Q2.push(node);
                        mark2[node] = 1;
                    }
                }
                Q2.pop();

             }
        }

    double F=0,F_for_same=0;

    for(int i=0;i<Tnode;i++)
        F = F+HiericalValue[i];

    for(int i=0;i<Tnode;i++)
        F_for_same = F_for_same+HiericalValue_for_same[i];

    F = F - F_for_same/2;


    return F/(Tnode*(Tnode-1)/2);
}

///zihad


void bfs_D(int src)
{
	queue<int>Q;
	Q.push(src);
	int visited[Tnode]={0},level[Tnode];
	int parent[Tnode];
	visited[src]=1;
    level[src]=0;
	while(!Q.empty())
	{
		int u=Q.front(); //Q এর সামনের নোড নিয়ে আমরা কাজ করবো
		for(int i=0;i<G[u].size();i++)
		{
			int v=G[u][i];
			if(!visited[v])
			{
				level[v]=level[u]+1;
				parent[v]=u;
				visited[v]=1;
				Q.push(v);
			}
		}
		Q.pop();
	}
	/*
	for(int i=src+1;i<Tnode;i++)
		printf("%d to %d distance %d\n",src,i,level[i]);
		*/

    for(int i=src;i<Tnode;i++){
       DM_sum+=level[i];
    }
    //printf("The Diameter is of summation : %lf\n",DM_sum);
}

void graph_vector(int NetworkD[][Tnode]){

     for(int i=0;i<Tnode;i++){
        for(int j=0;j<Tnode;j++){
            if(NetworkD[i][j]==1){
                G[i].push_back(j);
            }
        }
     }
}
/// For Network Diameter
double Network_Diameter(int NetworkD[][Tnode]){

   graph_vector(NetworkD);
  /* for(int i=0;i<Tnode;i++){

    printf("The graph size %d\n",G[i].size());
   }
   */
   for(int i=0;i<Tnode;i++)
{

    bfs_D(i); /// i is src
}

double DiaMeter=(2*DM_sum)/(Tnode*(Tnode-1));
//printf("The Diameter is %lf\n",DiaMeter);
vector_claer();  /// claer all intilize grpah  node in vector.
DM_sum=0;
return DiaMeter;

}

void vector_claer(){
  for(int node=0;node<Tnode;node++){
    G[node].clear();
  }
}
