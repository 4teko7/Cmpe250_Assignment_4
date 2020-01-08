#ifndef CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#define CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <limits>
#include <queue>
using namespace std;

struct Node{
    long long int parent,min;
    bool isRelated;
};
class HelpStudents{

public:

    HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways);
    long long int firstStudent();
    long long int secondStudent();
    long long int thirdStudent();
    long long int fourthStudent();
    long long int fifthStudent();


    int numberOfVertices = 0,numberOfEdges = 0,target = 0;
    vector < pair< pair <int,int> , int > > path;



    set<pair<long long int,long long int>> vertices;
    queue<pair<long long int,long long int>> verticeQueue;

    // YOU CAN ADD YOUR HELPER FUNCTIONS AND MEMBER FIELDS
    void addRelations(list <pair<long long int,long long int>> adjlist[]);
    void dijkstra(long long int root,list <pair<long long int,long long int>> adjlist[],vector<long long int> &dist);
    long long int bfs(long long int root,list <pair<long long int,long long int>> adjlist[],vector<bool> &visited);
    long long int minWays(long long int root,list <pair<long long int,long long int>> adjlist[],list <pair<long long int,long long int>> edges[]);
    bool findEdge(const long long int ,const long long int, const long long int,list <pair<long long int,long long int>> edges[]);
    void fillSecondStudent();
    long long int prim(long long int root,list <pair<long long int,long long int>> adjlist[],vector<long long int> &dist,vector<bool> &visited,vector<long long int> &max);

};

#endif //CMPE250_ASSIGNMENT3_HELPSTUDENTS_H
