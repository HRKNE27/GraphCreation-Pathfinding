/**
 * Name: Harrison Nguyen
 * PID: A16127257
 * Email: han002@ucsd.edu
 * Sources: Stepik
 *
 * This file takes a csv file ("first","second","weight") and represents it
 * as a graph where "first" and "second" are nodes connected by edge with
 * "weight". It allows the user to find shortest path between two nodes if
 * it exists and can find smallest "threshold" where a path still exists.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <string>
#include <limits>
#include "Graph.h"

/*
 * Comparative class used to implement priority queue for Dijkstra algorithm
 */
class comparatorClass{
public:
    bool operator()(Graph::dijkstraNode obj1,Graph::dijkstraNode obj2){
        return (obj1.distance > obj2.distance);
    }
};

/*
 * Global variables that stores nodes and dijikstraNodes
 */
vector<Graph::Node> undirectedGraph;
vector<Graph::dijkstraNode> vect;

/*
 * The constructor, takes in csv file and creates a graph representation
 * with entries as node
 * @param File with edge list to load to graph
 */
Graph::Graph(const string &edgelist_csv_fn) {
    ifstream my_file(edgelist_csv_fn);
    string line;
    while(getline(my_file,line)){
        //Parse through csv file and save values
        istringstream ss(line);
        string firstNode;
        string secondNode;
        string weightStr;
        getline(ss,firstNode,',');
        getline(ss,secondNode,',');
        getline(ss,weightStr,'\n');
        stringstream convert(weightStr);
        int weight = 0;
        convert >> weight;
        //Creates node with information from file
        Node newNode;
        newNode.nodeSrc = firstNode;
        newNode.nodeDest.push_back(secondNode);
        newNode.weights.push_back(weight);
        //Creates node to make graph undirected
        Node revNode;
        revNode.nodeSrc = secondNode;
        revNode.nodeDest.push_back(firstNode);
        revNode.weights.push_back(weight);
        bool checkNewNode = false;
        bool checkRevNode = false;
        //Check if node is already in graph
        unsigned int placeHolder1,placeHolder2;
        for(unsigned int i = 0; i < undirectedGraph.size();i++){
            if(undirectedGraph[i].nodeSrc.compare(firstNode)==0){
                checkNewNode = true;
                placeHolder1 = i;
            }
            if(undirectedGraph[i].nodeSrc.compare(secondNode)==0){
                checkRevNode = true;
                placeHolder2 = i;
            }
        }
        //If graph is empty, insert both nodes
        if(undirectedGraph.size()==0){
            undirectedGraph.push_back(newNode);
            undirectedGraph.push_back(revNode);
            continue;
        }
        //If node is present, then update nodes linked to it and weight
        if(checkNewNode == true){
            undirectedGraph[placeHolder1].nodeDest.push_back(secondNode);
            undirectedGraph[placeHolder1].weights.push_back(weight);
        }else{
            undirectedGraph.push_back(newNode);
        }
        //Similar to above, just to make graph undirected
        if(checkRevNode == true){
            undirectedGraph[placeHolder2].nodeDest.push_back(firstNode);
            undirectedGraph[placeHolder2].weights.push_back(weight);
        }else{
            undirectedGraph.push_back(revNode);
        }
    }
}

/*
 * Returns number of nodes in graph
 */
unsigned int Graph::num_nodes() {
    if(undirectedGraph.empty() == true){
            return 0;
    }
    return undirectedGraph.size();
}

/*
 * Return an unordered set of all nodes in graph
 */
unordered_set<string> Graph::nodes() {
    unordered_set<string> allNodes;
    //Loop through and insert node into allNodes
    for(unsigned int i = 0; i < undirectedGraph.size();i++){
        allNodes.insert(undirectedGraph[i].nodeSrc);
    }
    if(undirectedGraph.empty()==true){
        allNodes.clear();
    }
    return allNodes;
}

/*
 * Return the number of edges in graph
 */
unsigned int Graph::num_edges() {
    unsigned int numEdges = 0;
    //Loop through all nodes and count edges
    for(unsigned int i = 0; i < undirectedGraph.size();i++){
        for(unsigned int j = 0; j < undirectedGraph[i].nodeDest.size();j++){
            numEdges = numEdges + 1;
        }
    }
    //Since undirected, divide by 2
    numEdges = numEdges/2;
    return numEdges;
}

/*
 * Given a node, return the number of neighbors
 */
unsigned int Graph::num_neighbors(string const &node_label) {
        unsigned int numNeighbors = 0;
        //Loop through, find node and get all neighors
        for(unsigned int i = 0; i < undirectedGraph.size(); i++){
            if(undirectedGraph[i].nodeSrc.compare(node_label) == 0){
                numNeighbors = undirectedGraph[i].nodeDest.size();
                break;
            }
        }
        return numNeighbors;
}

/*
 * Given two nodes, return the edge weight between the two
 */
int Graph::edge_weight(string const &u_label, string const &v_label) {
        //Node is the same
        if(u_label.compare(v_label)==0){
            return -1;
        }
        //Find first node, then loop through neighbors until second node found
        int edgeWeight;
    for(unsigned int i = 0; i < undirectedGraph.size();i++){
        if(undirectedGraph[i].nodeSrc.compare(u_label) == 0){
            for(unsigned int j = 0; j < undirectedGraph[i].nodeDest.size(); j++){
                if(undirectedGraph[i].nodeDest[j].compare(v_label) == 0){
                    edgeWeight = undirectedGraph[i].weights[j];
                    return edgeWeight;
                }
            }
        }
        }
        //Couldn't find edge
        return -1;
    }

/*
 *  Given some node, return set of all neighbors
 */
unordered_set<string> Graph::neighbors(string const &node_label) {
    unordered_set<string> allNeighbors;
    for(unsigned int i = 0; i < undirectedGraph.size();i++){
        if(undirectedGraph[i].nodeSrc.compare(node_label)==0){
            for(unsigned int j = 0; j < undirectedGraph[i].nodeDest.size();j++){
                allNeighbors.insert(undirectedGraph[i].nodeDest[j]);
            }
        }
    }
    return allNeighbors;
}

//given label, find node in graph
Graph::Node Graph::findNode(string const &node_label){
    Node temp;
    for(unsigned int i = 0; i < undirectedGraph.size();i++){
        if(undirectedGraph[i].nodeSrc.compare(node_label)==0){
            temp = undirectedGraph[i];
        }
    }
    return temp;
}

//given label, find dijkstraNode in graph
Graph::dijkstraNode Graph::findDijkstraNode(string const &node_label){
    dijkstraNode temp;
    for(unsigned int i = 0; i < vect.size();i++){
        if(vect[i].label.compare(node_label)==0){
            temp = vect[i];
        }
    }
    return temp;
}

//Find shortest path between two nodes
vector<tuple<string, string, int>>
Graph::shortest_path_weighted(string const &start_label,
                                string const &end_label) {
priority_queue<dijkstraNode,vector<dijkstraNode>,comparatorClass> pq;
    dijkstraNode startingNode;

    //For each node, make a dijkstraNode and find startingNode
    for(unsigned int i = 0; i < undirectedGraph.size();i++) {
        dijkstraNode newNode;
        newNode.label = undirectedGraph[i].nodeSrc;
        if (undirectedGraph[i].nodeSrc.compare(start_label) == 0) {
            startingNode = newNode;
        }
        vect.push_back(newNode);
    }
    startingNode.distance = 0;
    pq.push(startingNode);
    while(pq.size() != 0){
        dijkstraNode currNode = pq.top();
        pq.pop();
        if(currNode.done == false){
            currNode.done = true;
            Node workNode = findNode(currNode.label);
            //Loop through each neighbor of workNode
            for(unsigned int i = 0; i < workNode.nodeDest.size();i++){
                int newDist = currNode.distance + workNode.weights[i];
                dijkstraNode subNode;
                unsigned int placeHolder;
                //Finding dijikstraNode version of w
                for(unsigned int j = 0; j < vect.size();j++){
                    if(vect[j].label.compare(workNode.nodeDest[i])==0){
                        subNode = vect[j];
                        placeHolder = j;
                    }
                }

                if(newDist < (int)subNode.distance){
                    subNode.previous = currNode.label;
                    subNode.distance = newDist;
                    vect[placeHolder].previous = currNode.label;
                    vect[placeHolder].distance = newDist;
                    pq.push(subNode);
                }
            }
        }
    }

    //Begin making vector with whole path
    vector<tuple<string,string,int>> shortestPath;
    dijkstraNode itrNode;
    for(unsigned int i = 0; i < vect.size();i++){
        if(vect[i].label.compare(end_label)==0){
            itrNode = vect[i];
        }
    }
    while(itrNode.label.compare(start_label) != 0){
        Node startNode = findNode(itrNode.label);
        Node endNode = findNode(itrNode.previous);
        int edgeWeight = edge_weight(startNode.nodeSrc,endNode.nodeSrc);
shortestPath.push_back(make_tuple(itrNode.previous,itrNode.label,edgeWeight));
        itrNode = findDijkstraNode(itrNode.previous);
    }
    reverse(shortestPath.begin(),shortestPath.end());
    return shortestPath;
}

//Returns the smallest threshold where a path still exists
int Graph::smallest_connecting_threshold(string const &start_label,
                                            string const &end_label) {
    vector<tuple<string,string,int>> shortestPath;
    shortestPath = shortest_path_weighted(start_label,end_label);
    //Loop through and find largest distance
    int threshold = 0;
    for(unsigned int i = 0; i < shortestPath.size();i++){
        if(get<2>(shortestPath[i]) >= threshold){
            threshold = get<2>(shortestPath[i]);
        }
    }
    return threshold;
}


