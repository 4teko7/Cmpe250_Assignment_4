/*
Student Name: Bilal Tekin
Student Number:2017400264
Project Number: 4
Compile Status: [SUCCESS/FAIL]
Running Status: [SUCCESS/FAIL]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "HelpStudents.h"
#include <set>
#include <vector>
#include <iostream>
#include <limits>
#include <list>
using namespace std;

const long long int INF = numeric_limits<long long int>::max();


long long int totalWay = 0;
HelpStudents::HelpStudents(int  N, int  M, int K, vector < pair< pair <int,int> , int > > ways) {
    // IMPLEMENT ME!
    path = ways;
    numberOfEdges = M;
    numberOfVertices = N;
    target = K;

}

long long int HelpStudents::firstStudent() {
    // IMPLEMENT ME!
    list <pair<long long int,long long int>> adjlist[numberOfVertices+1];
    vector<long long int> dist(numberOfVertices+1, INF);

    addRelations(adjlist);
    dijkstra(1,adjlist,dist);
    return dist.at(target);

}
long long int HelpStudents::secondStudent() {
    // IMPLEMENT ME!
    vector<bool> visited(numberOfVertices+1,false);
    list <pair<long long int,long long int>> adjlist[numberOfVertices+1];
    vector<long long int> dist(numberOfVertices+1, INF);
    vector<long long int> max(numberOfVertices+1,0);
    addRelations(adjlist);
    return prim(1,adjlist,dist,visited,max);

}
long long int HelpStudents::thirdStudent() {
    // IMPLEMENT ME!
    list <pair<long long int,long long int>> adjlist[numberOfVertices+1];
    vector<bool> visited(numberOfVertices+1,false);
    addRelations(adjlist);
    return bfs(1,adjlist,visited);
}
long long int HelpStudents::fourthStudent() {
    // IMPLEMENT ME!
    if(target == 1) return 1;
    list <pair<long long int,long long int>> adjlist[numberOfVertices+1];
    list <pair<long long int,long long int>> edges[numberOfVertices+1];
    addRelations(adjlist);
    return minWays(1,adjlist,edges);

}
long long int HelpStudents::fifthStudent() {
    // IMPLEMENT ME!
}

// YOU CAN ADD YOUR HELPER FUNCTIONS

void HelpStudents::dijkstra(long long int root,list <pair<long long int,long long int>> adjlist[],vector<long long int> &dist){
    vertices.insert(make_pair(0,root));
    dist.at(root) = 0;;
    while(!vertices.empty()){

        pair<long long int,long long int> temp = *(vertices.begin());
        vertices.erase(vertices.begin());

        long long int u = temp.second;
        list<pair<long long int,long long int>>::iterator it;

        for(it = adjlist[u].begin(); it != adjlist[u].end(); it++){
            long long int v = (*it).second;
            long long int w = (*it).first;

            if(dist.at(v) > dist.at(u) + w){

                if(dist.at(v) != INF)
                    vertices.erase(vertices.find(make_pair(dist.at(v),v)));
                dist.at(v)= dist.at(u) + w;
                vertices.insert(make_pair(dist.at(v),v));
            }
        }
    }
}
long long int HelpStudents::bfs(long long int root,list <pair<long long int,long long int>> adjlist[],vector<bool> &visited){
    if (target == 0) {
        return 0;
    }
    visited.at(root) = true;

    verticeQueue.push(make_pair(0,root));
    long long int sortway = 0;

    while(!verticeQueue.empty()) {

        long long int size = verticeQueue.size();

        for (int i = 0; i < size; i++) {
            pair<long long int, long long int> temp = verticeQueue.front();
            verticeQueue.pop();
            if(temp.second == target){
                return sortway;
            }
            list<pair<long long int,long long int>>::iterator it;
            for(it = adjlist[temp.second].begin(); it != adjlist[temp.second].end(); it++){
                if(visited.at((*it).second)) continue;
                verticeQueue.push(*it);
                visited.at((*it).second) = true;
            }
        }
        sortway++;
    }
}
long long int HelpStudents::minWays(long long int root,list <pair<long long int,long long int>> adjlist[],list <pair<long long int,long long int>> edges[]){

    long long int temp = root;
    while(true) {
        long long int min = INF;
        long long int nodeNum = 0;
        bool found = false;

        list<pair<long long int, long long int>>::iterator it;
        for (it = adjlist[temp].begin(); it != adjlist[temp].end(); it++) {
            if ((*it).first <= min) {
                if(!findEdge(temp, (*it).first, (*it).second,edges)){
                    found = true;
                    if((*it).first == min){
                        if((*it).second < nodeNum)
                            nodeNum = (*it).second;
                        else
                            continue;
                    }else{
                        min = (*it).first;
                        nodeNum = (*it).second;
                    }
                }
            }
        }
        if (found) {
            edges[temp].push_back(make_pair(min, nodeNum));
            edges[nodeNum].push_back(make_pair(min, temp));
            temp = nodeNum;
        } else {
            return -1;
        }

        totalWay += min;

        if(nodeNum == target){
            return totalWay;
        }
    }
}
bool HelpStudents::findEdge(const long long int u,const long long int w , const long long int v,list <pair<long long int,long long int>> edges[]){
    list<pair<long long int,long long int>>::iterator it;
    it = edges[u].begin();
    long long int size = edges[u].size();
    for(long long int i = 0; i < size; it++,i++){
        if(((*it).first == w ) && (*it).second == v) return true;
    }
    return false;
}

long long int HelpStudents::prim(long long int root,list <pair<long long int,long long int>> adjlist[],vector<long long int> &dist,vector<bool> &visited,vector<long long int> &max){
    vertices.insert(make_pair(0,root));
    dist.at(root) = 0;;
    max.at(1) = 0;
    visited.at(root) = true;
    while(!vertices.empty()){

        pair<long long int,long long int> temp = *(vertices.begin());
        vertices.erase(vertices.begin());

        long long int u = temp.second;
        visited.at(u) = true;
        list<pair<long long int,long long int>>::iterator it;

        for(it = adjlist[u].begin(); it != adjlist[u].end(); it++){
            if(visited.at((*it).second)) continue;
            long long int v = (*it).second;
            long long int w = (*it).first;

            if(dist.at(v) >  w){
                if(max.at(temp.second) < w){
                    max.at((*it).second) = w;
                }else{
                    max.at((*it).second) = max[temp.second];
                }
                if(dist.at(v) != INF)

                    vertices.erase(vertices.find(make_pair(dist.at(v),v)));
                dist.at(v)= w;
                vertices.insert(make_pair(dist.at(v),v));
            }
        }
    }

    return max[target];
}


void HelpStudents::addRelations(list <pair<long long int,long long int>> adjlist[]) {

    for(int i = 0; i < numberOfEdges; i++){
        if(path[i].first.first == path[i].first.second) continue;
        adjlist[path[i].first.first].push_back(make_pair(path[i].second,path[i].first.second));
        adjlist[path[i].first.second].push_back(make_pair(path[i].second,path[i].first.first));

    }

}