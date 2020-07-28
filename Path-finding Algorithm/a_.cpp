#include <bits/stdc++.h>
#define pb push_back
#define pf push_front
#define ll long long
#define ld long double

using namespace std;

double root2=sqrt(2);

class node
{
	public:
		double preVal=pow(10,7);
		double projVal=pow(10,7);
		int x=-1;
		int y=-1;
		int toX=-1;
		int toY=-1;
};

class comparator 
{ 
	public: 
	    int operator() ( node &p1,  node &p2) 
	    { 
	        return ((p1.preVal+p1.projVal)>(p2.preVal+p2.projVal)); 
	    } 
}; 

int main()
{
	int obst[5][6]=
	{
		{1,0,0,0,0,0},
		{0,0,0,1,0,0},
		{0,1,1,1,0,0},
		{0,0,0,0,0,0},
		{0,0,1,0,1,0}
	};
	node n[5][6];
	int s[2]={1,1};
	int e[2]={3,3};
	n[e[0]][e[1]].preVal=0;
	n[e[0]][e[1]].projVal=sqrt(pow(s[0]-e[0],2)+pow(s[1]-e[1],2));
	for(int i=0;i<5;i++)
		for(int j=0;j<6;j++)
		{
			n[i][j].x=i;
			n[i][j].y=j;
		}
	priority_queue <node, vector<node>, comparator > path; 

	path.push(n[e[0]][e[1]]);
	int found=0;
	while(1)
	{
		node curPos=path.top();
		path.pop();
		for(int i=-1;i<=1;i++)
		{
			for(int j=-1;j<=1;j++)
			{
				if((curPos.x+i<5) && (curPos.y+j<6) &&(curPos.x+i>=0) && (curPos.y+j>=0) && ( i!=0 || j!=0) && (obst[curPos.x+i][curPos.y+j]==0))
				{
					node temp;
					temp.x=curPos.x+i;
					temp.y=curPos.y+j;
					if(abs(i)!=abs(j))	temp.preVal=min(curPos.preVal+1,n[temp.x][temp.y].preVal);
					else		temp.preVal=min(curPos.preVal+root2,n[temp.x][temp.y].preVal);
					temp.projVal=sqrt(pow(temp.x-s[0],2)+pow(temp.y-s[1],2));				
					if(temp.preVal!=n[temp.x][temp.y].preVal)	
					{
						temp.toX=curPos.x;
						temp.toY=curPos.y;
						path.push(temp);
						n[temp.x][temp.y]=temp;	
					}
					//cout<<curPos.x<<" "<<curPos.y<<" "<<temp.x<<" "<<temp.y<<" "<<temp.preVal<<"\t"<<temp.projVal<<endl;
					if(temp.projVal==0)	
					{
						found=1;
						break;
					}
				}
			}
			if(found==1)	break;
		}		
		if(found==1)	break;
	}
	node travel;
	travel=n[s[0]][s[1]];
	while(travel.preVal!=0)
	{
		cout<<travel.x<<" "<<travel.y<<endl;
		travel=n[travel.toX][travel.toY];
	}
	cout<<n[s[0]][s[1]].preVal;
    return 0;
}