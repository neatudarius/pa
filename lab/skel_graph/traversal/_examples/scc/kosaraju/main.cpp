//Componente tare conexe - Kosaraju - O(N+M)
// https://infoarena.ro/problema/ctc

#include <fstream>
#include <bitset>
#include <vector>
#define Nmax 100099
#define pb push_back
using namespace std;
ifstream f("ctc.in");
ofstream g("ctc.out");
 
int N,M,sol,Tsort[Nmax],x,y;
bitset < Nmax> viz;
vector < int > G[Nmax],T[Nmax],CTC[Nmax];
 
 
void PrintOutput()
{
 
}
 
void DFS(int node)
{
     viz[node]=1;
     for(vector<int>::iterator it=G[node].begin();it!=G[node].end();++it)
          if(!viz[*it])DFS(*it);
     Tsort[++Tsort[0]]=node;
}
 
void DFS_T(int node)
{
     viz[node]=0; CTC[sol].pb(node);
     for(vector<int>::iterator it=T[node].begin();it!=T[node].end();++it)
          if(viz[*it])DFS_T(*it);
}
 
void Tarjan()
{
     for(int i=1; i<=N; ++i)
          if(!viz[i])DFS(i);
     for(int i=N; i>=1; --i)
          if(viz[Tsort[i]])
                ++sol , DFS_T(Tsort[i]);
}
int main()
{
     f>>N>>M;
     for(int i=1;i<=M;++i)
          f>>x>>y , G[x].pb(y) , T[y].pb(x);
     Tarjan();
     g<<sol<<'\n';
     for(int i=1;i<=sol;++i)
     {
         for(vector<int>::iterator it=CTC[i].begin();it!=CTC[i].end();++it)
               g<<*it<<' ';
         g<<'\n';
     }
     f.close();g.close();
     return 0;
}