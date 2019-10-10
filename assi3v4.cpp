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

int get_var(int x1,int y1,int n)
{
	return (x1-1)*n + y1;
}

int get_pattern(int x,int y,int m)
{
	if(y<x)
	return (x-1)*(m-1) + y;
	return (x-1)*(m-1) + y-1;
}
int get_var1(int x1,int y1,int x2,int y2,int m,int n)
{
	return  m*n+(get_pattern(x1,y1,n)-1)*m*(m-1)+get_pattern(x2,y2,m);
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


vector<vector<int>> print_gra(vector<vector<int>> c,int h,int x1,int y1,int n)
{
	int k=0;
	vector<vector<int>> x2;
	for(int i=0;i<c.size();i++)
	{
		for(int j=0;j<c.size();j++)
		{
			vector<int> x3;
			if(c[i][j]==0 && h==2 && i!=j)
			{
				int l = get_var(x1,i+1,n);
				int m = get_var(y1,j+1,n);
				x3.push_back(i+1);
				x3.push_back(j+1);
				k=k+1;
			}

			if(c[i][j]==1 && h==1 && i!=j)
			{
				int l = get_var(x1,i+1,n);
				int m = get_var(y1,j+1,n);
				x3.push_back(i+1);
				x3.push_back(j+1);
				k=k+1;
			}
			if(x3.size()!=0)
			x2.push_back(x3);
		}
		
	}
	return x2;
}

void print_graph(vector<vector<int>> c)
{
	cout  << endl;
	for(int i=0;i<c.size();i++)
	{
		for(int j=0;j<c[i].size();j++)
		{
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	cout  << endl;
}

int main(int argc, char const *argv[])
{
  // auto start = high_resolution_clock::now();
  vector<string> graph1; 
  vector<string> graph2;    
  int m=0;
  int n=0;
  string line;
  string filename(argv[1]);
  ifstream myfile (filename + ".graphs");
  int point = 1;

  if (myfile.is_open())
  {
    while ( getline(myfile,line) )
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
    myfile.close();
 }

  else cout << "Unable to open file"; 



  ofstream outfile (filename + ".satinput");
  long nos_clauses = (n*m-1)*n*m/2 + m*m + n;
  long nos_variables = n*m + m*m;

  // graph1 == m, graph2 == n
  outfile << "p cnf " << nos_variables << " " << nos_clauses <<endl;
  vector<vector <int>> gra1 = vector<vector <int>>();
  vector<vector <int>> gra2 = vector<vector <int>>();

  // initialize graphs
  // for(int i=0;i<m;i++)
  // {
  // 	vector<int> x1;
  // 	for(int j=0;j<m;j++)
  // 	{
  // 		x1.push_back(0);
  // 	}
  // 	gra1.push_back(x1);
  // }

  // for(int i=0;i<n;i++)
  // {
  // 	vector<int> x1;
  // 	for(int j=0;j<n;j++)
  // 	{
  // 		x1.push_back(0);
  // 	}
  // 	gra2.push_back(x1);
  // }

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
  	// gra1[x-1][y-1] = 1;
  }
  
  for(int i=0;i<graph2.size();i++)
  {
  	vector<int> x1 = get_nos(graph2[i]);
  	int x = x1[0];
  	int y = x1[1];
    iso_gra2[x] = 0;
    iso_gra2[y] = 0;
  	// gra2[x-1][y-1] = 1;
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

  // initialize graphs with zeros
  for(int i=0;i<m1;i++)
  {
   vector<int> x1;
   for(int j=0;j<m1;j++)
   {
     x1.push_back(0);
   }
   gra1.push_back(x1);
  }

  for(int i=0;i<n1;i++)
  {
   vector<int> x1;
   for(int j=0;j<n1;j++)
   {
     x1.push_back(0);
   }
   gra2.push_back(x1);
  }

  // map nodes
  int map_gra1[m+1] = {0};
  int map_gra2[n+1] = {0};
  int jj = 0;
  for(int i=1; i<m+1; i++){
    if(iso_gra1[i] == 0){
      map_gra1[i] = ++jj;
    }
  }
  jj=0;
  for(int i=1; i<n+1; i++){
    if(iso_gra2[i] == 0){
      map_gra2[i] = ++jj;
    }
  }

  // cout<< "map1 size: "<< m << " " << m1 <<endl;
  // cout<< "map2 size: "<< n << " " << n1 <<endl;

  // initialize graphs with connections
  for(int i=0;i<graph1.size();i++)
  {
    vector<int> x1 = get_nos(graph1[i]);
    int x = x1[0];
    int y = x1[1];
    gra1[map_gra1[x]-1][map_gra1[y]-1] = 1;
  }
  
  for(int i=0;i<graph2.size();i++)
  {
    vector<int> x1 = get_nos(graph2[i]);
    int x = x1[0];
    int y = x1[1];
    gra2[map_gra2[x]-1][map_gra2[y]-1] = 1;
  }

  // clause :: atleast one connection

  n = n1;
  m = m1;


  vector<vector<int>> map;
  int clauses = 0;
  vector<int> var;
  long varb=0;
  for(int i=0;i<n;i++)
  {
  	for(int j=0;j<m;j++)
  	{
  		vector<int> x1;
  		int xl = get_var(i+1,j+1,m);
  		if(j==m-1)
  		  outfile << xl ;  		
  		else
		    outfile << xl << " " ;
  		x1.push_back(i);
  		x1.push_back(j);
  		var.push_back(0);
  		varb+=1;
  		map.push_back(x1);
  	}
  	outfile << " 0" << endl ;
  	clauses = clauses+1;
  }

  for(int i=0;i<m;i++)
  {
  	for(int j=0;j<m;j++)
  	{
  		if(gra1[i][j]==1)
  		  outfile << n*m +get_var(i+1,j+1,m) << " 0" << endl ;
  		else
  		  outfile << "-" << n*m +get_var(i+1,j+1,m) << " 0" << endl ;
  		clauses +=1;
  		varb +=1;

  	}	
  }


  int size = var.size();
  int mark=-1;
  string col[n];
  for(int i=0;i<size;i++)
  {
    std::string str = "";
  	for(int j=0;j<size;j++)
  	{
  		if(i==j)
  		{
  			continue;
  		}
  		if(map[i][0]==map[j][0])
  		{
        str += "-";
        str += to_string(i+1);
        str += " -";
        str += to_string(j+1);
        str += " 0\n";
  		clauses = clauses+1;
  		continue;
  		}
  		if(map[i][1]==map[j][1])
  		{
  			str += "-";
        	str += to_string(i+1);
        	str += " -";
       		str += to_string(j+1);
        	str += " 0\n";
        	clauses +=1;
  			continue;
  		}
  		if(gra2[map[i][0]][map[j][0]] == 1)
  		{
  			
  			str += "-";
        	str += to_string(get_var(map[i][0]+1,map[i][1]+1,m));
        	str += " -";
       		str += to_string(get_var(map[j][0]+1,map[j][1]+1,m));
       		str += " ";
       		int varb1 = n*m + get_var(map[i][1]+1,map[j][1]+1,m);
        	str += to_string(varb1);
        	str += " 0\n";
        	clauses +=1;	
  			continue;       
  		}
  		else
  		{
  			str += "-";
        	str += to_string(get_var(map[i][0]+1,map[i][1]+1,m));
        	str += " -";
       		str += to_string(get_var(map[j][0]+1,map[j][1]+1,m));
       		str += " -";
         	int varb1 = n*m + get_var(map[i][1]+1,map[j][1]+1,m);
        	str += to_string(varb1);
        	str += " 0\n";
        	clauses +=1;
  			continue;
  		}
      str += "\n";
  	}
    outfile <<str;
  }

  outfile.close();
  // auto stop = high_resolution_clock::now(); 
  // auto duration = duration_cast<milliseconds>(stop - start); 

  // int tt = duration.count()/1000;
  // float min = tt/60;
  // float sec = tt%60;
  // cout << "Time Taken : " << min << " mins, " << sec << " secs" << endl; 
  return 0;
}