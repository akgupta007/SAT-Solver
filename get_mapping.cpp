#include <fstream>
#include <iostream>
#include <stdio.h>      
#include <time.h>   
#include <vector> 
#include <math.h>
#include <algorithm>
#include <random> 
#include <map>
#include <tuple>
#include <string>
#include <chrono> 

using namespace std::chrono;
using namespace std;

int get_max(string s)
{
	int i=0;
	for(i=0;i<s.size();i++)
	{
		if(s[i] == ' ')
		{
			break;
		}
	}
	string s1 = s.substr(0,i);
	string s2 = s.substr(i+1,s.size());

	if(stoi(s1)>stoi(s2))
	{
		return stoi(s1);
	}
	return stoi(s2);
}
vector<int> get_nos(string s)
{
	int i=0;
	for(i=0;i<s.size();i++)
	{
		if(s[i] == ' ')
		{
			break;
		}
	}
	string s1 = s.substr(0,i);
	string s2 = s.substr(i+1,s.size());
	vector<int> c;
	c.push_back(stoi(s1));
	c.push_back(stoi(s2));
	return c;

}

int main(int argc, char const *argv[]){
	string filename(argv[1]);

	ifstream graphs (filename + ".graphs");
	int point = 1;
	vector<string> graph1; 
  vector<string> graph2;    
  
	int m=0, n = 0;
	string line;
	if (graphs.is_open())
	{
		while ( getline(graphs,line) )
		{
			if(line=="0 0")
			{
				point = 0;
				continue;
			}

			if(point==1)
			{
     			graph1.push_back(line);

				if(get_max(line)>m)
				{
			 		m = get_max(line);
				}
			}
			if(point==0)
			{
 	 			graph2.push_back(line);

				if(get_max(line)>n)
				{
					n = get_max(line);
				}
			}
		}
		graphs.close();
	}

	else cout << "Unable to open file";


  int iso_gra1[m+1];
  int iso_gra2[n+1];

  for(int i=0 ; i< m+1; i++){
    iso_gra1[i] = 1;
  }
  for(int i=0; i< n+1; i++){
    iso_gra2[i] = 1;
  }
  int m1 = 0;
  int n1 = 0;
  // find isolated nodes
  for(int i=0;i<graph1.size();i++)
  {
  	vector<int> x1 = get_nos(graph1[i]);
  	int x = x1[0];
  	int y = x1[1];
    iso_gra1[x] = 0;
    iso_gra1[y] = 0;
  }
  
  for(int i=0;i<graph2.size();i++)
  {
  	vector<int> x1 = get_nos(graph2[i]);
  	int x = x1[0];
  	int y = x1[1];
    iso_gra2[x] = 0;
    iso_gra2[y] = 0;
  }

  // calculate new size of graphs having atleast one edge
  for(int i=1; i<n+1; i++){
    if(iso_gra2[i] == 0){
      n1++;
    }
  }
  for(int i=1; i<m+1; i++){
    if(iso_gra1[i] == 0){
      m1++;
    }
  }

  // map nodes
  int map_gra1[m1+1] = {0};
  int map_gra2[n1+1] = {0};
  int jj = 0;
  for(int i=1; i<m+1; i++){
    if(iso_gra1[i] == 0){
      map_gra1[++jj] = i;
      // cout<< map_gra1[jj]<<" ";
    }
  }
  // cout<<endl;
  jj=0;
  for(int i=1; i<n+1; i++){
    if(iso_gra2[i] == 0){
      map_gra2[++jj] = i;
      // cout<<map_gra2[jj]<< " " ;
    }
  }
  // cout<<endl;


	ofstream mapping ( filename + ".mapping");
	if (!mapping.is_open()) return 0;
  if( n-n1 > m-m1){
  	mapping << 0 << "\n";
  	return 0;
  }
  int last_node = 1;
  for(int i=1; i<n+1; i++){
    if(iso_gra2[i] == 1){
      for(int j=last_node; j<m+1; j++){
      	if(iso_gra1[j] == 1){
      		mapping << i << " " << j << "\n";
      		last_node = j+1;
      		break;
      	}
      }
    }
  }


  n = n1;
  m = m1;

	ifstream myfile ( filename + ".satoutput");

	if(!myfile.is_open()){
		return 0;
	}

	string sat = "";
	myfile >> sat;
	if(sat == "UNSAT"){
		mapping << 0;
		return 0;
	}

	string var = "";
	while(myfile >> var){
		int v = stoi(var);
		if(v <= n*m){
			if ( v > 0){
				mapping << map_gra2[(v-1)/m+1] << " " << map_gra1[(v-1)%m+1] << "\n";
			}
		}
	}
	mapping.close();
	myfile.close();
	return 0;
}