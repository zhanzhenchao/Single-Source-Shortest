#include<iostream>
using namespace std;

const int Max = 10000;

//------------------------------------------------------
//The Structure of Graph
//------------------------------------------------------
struct Vertexs
{
	char data;
	int weight;
	int d;
	Vertexs *¦Ð;
	Vertexs *next;
};

struct AdjGraph
{
	char data;
	Vertexs *first;
};

struct Graph
{
	AdjGraph Adj[50];
	int n;
	int e;
};

//------------------------------------------------------
//Main Structure of Graph Class
//------------------------------------------------------
class Path
{
public:
	Path();
	~Path();
	Graph * I_G(char u , char v , int weight );                                   //Initialize Graph vertexs u ¡ÊG.V ,and edges ¡ÊG.E
	void Initialize_Single_Source ( Graph *G , char s );                          //Initialize u.d and u.pi ( u ¡ÊG.V-{s},),s.d;
	bool Relax ( char u , char v , int weight);                                   //Return the bool whether it has been relaxed
	bool Bellman_Ford ( Graph *G , char s );                                      //Return the bool whether it succeed
	int Max_Number(int a[],int n);                                                //Return the maximun from array 
	void Shortest_Path();                                                         //Get the shortest vertexs from array Adj[u]
	void DisPlay_test();                                                          //test;

private:
	Graph *G;
};

//------------------------------------------------------
//Implementation of Graph Class
//------------------------------------------------------

Path::Path()
{
	G = ( Graph *)malloc(sizeof(Graph));
	G->n = 7;
	G->e = 9; 
	for ( int i = 0; i < G->n; i++ )                         //Initialize the Adj[u];       
	{
		G->Adj[i].first = (Vertexs*)malloc(sizeof(Vertexs));
		G->Adj[i].data = '0';
		G->Adj[i].first->d = 0;
		G->Adj[i].first->data = '0'; 
		G->Adj[i].first->next = NULL;
		G->Adj[i].first->weight = Max;
		G->Adj[i].first->¦Ð = NULL;
	}
}

Path::~Path(){}

Graph * Path::I_G(char u , char v , int weight )
{
	int temp = 0;
	int j = 0;
	Vertexs *p = (Vertexs *)malloc(sizeof(Vertexs ));
	Vertexs *q = (Vertexs *)malloc(sizeof(Vertexs ));
	while (j < G->n  && G->Adj[j].first->data != u )                 //No-repeat filling into Adj[u];
		j++;
	if ( j < G->n )
		temp = j;
	else 
	{
		for ( int i = 0; i < G->n; i++ )
		{
			if ( G->Adj[i].first->data == '0' )
			{
				temp = i;                                    //Record the temporary location
				//cout<<i<<endl;                             //test Graph            
				break;
			}
		}
		G->Adj[temp].first->data = u;                                   //Stores adj[u]
	}

	p = G->Adj[temp].first ;                                //The rest of G.V - {u}
	while ( p->next != NULL )
	{
		p = p->next;
	}
	p->next = q;
	p->next->data = v;
	p->next->weight = weight;
	p->next->¦Ð = p;
	p->next->next =NULL;
	
	return G;
}


void Path::DisPlay_test()
{
	Vertexs *p,*q;
	int j = 0;
	for ( int i = 0; i < G->n; i++ )                       
	{
		p = q = G->Adj[i].first;
		cout<<p->data<<"-";
		while ( p->next !=	NULL )
		{
			p = p->next;
			cout<<"-"<<p->data;
		}
		cout<<endl;
	}
}


void Path::Initialize_Single_Source( Graph *G, char s )
{
	Vertexs *p;
	for ( int i = 0; i < G->n; i++ )                         //Initialize the Adj[u];       
	{
		G->Adj[i].first->d = Max;
		G->Adj[i].first->¦Ð = NULL;
	}
	for ( int i = 0; i < G->n; i++ )                         // s.d = 0;
	{
		p = G->Adj[i].first;
		if ( p->data == s )
		{
			p->d = 0;
			break;
		}
	}
}

bool Path::Relax( char u,char v,int weight )
{
	/*
	if ( v->d > u->d + weight )
	{
		v->d = u->d + weight;
		v->¦Ð = u;
	}
	*/
	Vertexs *p = NULL,*q = NULL;
	for ( int i = 0; i < G->n; i++ )
	{
		if ( G->Adj[i].first->data == u )
		{
			p = G->Adj[i].first;
			break;
		}
	}
	for ( int i = 0; i < G->n; i++ )
	{
		if ( G->Adj[i].first->data == v )
		{
			q = G->Adj[i].first;
			break;
		}
	}

	if ( q->d > p->d + weight )
	{
		q->d = p->d + weight;
		q->¦Ð= p;
		return true;
	}
	else 
		return false;
}

bool Path::Bellman_Ford( Graph *G, char s )
{
	Vertexs *p,*q;
	char u,v;
	Initialize_Single_Source(G,s);
	for ( int i = 0; i < G->n - 1; i++ )                            
	{
		for ( int j = 0; j < G->n; j++ )                            //For each edges(u,e)¡ÊG.E
		{
			p = q = G->Adj[j].first;
			while ( q->next != NULL )
			{
				u = p->data;
				v = q->next->data;
				Relax(u,v,q->next->weight);                               //function Relax
				q = q->next;
			}
		}
	}
	//For each edges(u,e)¡ÊG.E 
	//testing whether the graph existed minus loops
	//if existed,return true,else return false 
	for ( int i = 0; i < G->n; i++ )                                
	{
		p = q = G->Adj[i].first;
		while ( q->next != NULL )
		{
			u = p->data;
			v = q->next->data;
			if ( Relax(u,v,q->next->weight) )
				return false;
			q = q->next;
		}
	}
	return true;
}

int Path::Max_Number(int a[],int n)
{
	int key = a[0];
	for ( int i = 1; i < n; i++ )
	{
		if ( key < a[i] )
		{
			key = a[i];
		}
	}
	return key;                             //return the max number of array
}
		
void Path::Shortest_Path()
{
	int a[100];
	Vertexs b[100];
	int key ,location;
	//sorted each shortest single-source 
	for ( int i = 0; i < G->n; i++ )
	{
		Bellman_Ford(G,G->Adj[i].first->data);
		for ( int j = 0; j < G->n; j++ )
		{
			a[j] = G->Adj[j].first->d;
			//cout<<a[j]<<"  ";                               //test
		}
		cout<<endl<<endl;
		b[i].data = G->Adj[i].first->data;
		b[i].d = Max_Number(a,G->n);
	}

	key = b[0].d;                                             //Gets the minimum numbers from all the shortest single-source
	for ( int i = 1; i < G->n; i++ )
	{
		if ( key > b[i].d )                                  
		{
			key = b[i].d;
			location = i;                                    //Recorded the minimum numbers location from array
		}
	}
	
	cout<<"the best place choosing to bulid hospital is :"<<b[location].data<<endl;
}

//------------------------------------------------------
//Main function
//------------------------------------------------------
void main()
{
	Path A;
	Graph *G;
	char s = 's',
		t = 't',
		x = 'x',
		y = 'y',
		z = 'z',
		k = 'k',
		m = 'm';

	A.I_G(s,t,3);
	A.I_G(s,m,4);
	A.I_G(s,k,1);
	A.I_G(s,z,2);

	A.I_G(t,s,3);
	A.I_G(t,m,2);
	A.I_G(t,y,3);
	A.I_G(t,x,2);

	A.I_G(x,t,2);
	A.I_G(x,m,3);
	A.I_G(x,y,4);
	A.I_G(x,z,1);

	A.I_G(y,x,4);
	A.I_G(y,t,3);
	A.I_G(y,m,6);
	A.I_G(y,z,4);

	A.I_G(z,s,2);
	A.I_G(z,m,3);
	A.I_G(z,x,6);
	A.I_G(z,y,4);
	A.I_G(z,k,5);

	A.I_G(k,s,1);
	A.I_G(k,m,1);
    A.I_G(k,z,5);

	A.I_G(m,t,2);
	A.I_G(m,x,3);
	A.I_G(m,y,6);
	A.I_G(m,z,3);
	A.I_G(m,k,1);
	G = A.I_G(m,s,4);
	
	//A.Bellman_Ford(G,s);
	//A.Bellman_Ford(G,t);
	//A.Bellman_Ford(G,x);
	//A.Bellman_Ford(G,y);
	//A.Bellman_Ford(G,z);
	//A.Bellman_Ford(G,k);
	//A.Bellman_Ford(G,m);
	A.DisPlay_test();
	A.Shortest_Path();
	system("pause");
}
	

/*
	The First Sample

	A.I_G(s,t,3);
	A.I_G(s,x,2);
	A.I_G(s,y,2);
	
	A.I_G(t,s,3);
    A.I_G(t,x,1);
	A.I_G(t,y,6);
	A.I_G(t,z,3);

	A.I_G(x,s,2);
	A.I_G(x,t,6);
	A.I_G(x,y,4);
	A.I_G(x,z,7);

	A.I_G(y,s,2);
	A.I_G(y,t,1);
	A.I_G(y,x,4);
	A.I_G(y,z,6);

	A.I_G(z,t,3);
	A.I_G(z,x,7);
	A.I_G(z,y,6);
	*/

/*
    The Second Sample

	A.I_G(s,t,3);
	A.I_G(s,m,4);
	A.I_G(s,k,1);
	A.I_G(s,z,2);

	A.I_G(t,s,3);
	A.I_G(t,m,2);
	A.I_G(t,y,3);
	A.I_G(t,x,2);

	A.I_G(x,t,2);
	A.I_G(x,m,3);
	A.I_G(x,y,4);
	A.I_G(x,z,1);

	A.I_G(y,x,4);
	A.I_G(y,t,3);
	A.I_G(y,m,6);
	A.I_G(y,z,4);

	A.I_G(z,s,2);
	A.I_G(z,m,3);
	A.I_G(z,x,6);
	A.I_G(z,y,4);
	A.I_G(z,k,5);

	A.I_G(k,s,1);
	A.I_G(k,m,1);
    A.I_G(k,z,5);

	A.I_G(m,t,2);
	A.I_G(m,x,3);
	A.I_G(m,y,6);
	A.I_G(m,z,3);
	A.I_G(m,k,1);
	A.I_G(m,s,4);
	*/
