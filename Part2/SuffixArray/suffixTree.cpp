#include "suffixTree.h"
#include <iostream>
#include <unordered_map> // Required c++11 support.
#include <string>
#include <cassert>
#include <ctime>
#include <chrono>
#include <sstream>
#include <vector>
#include <math.h>
#include <map>
using namespace std;



// The initial tree contains one node i.e. root node so count = 1;
int Node::noOfNodes;

struct Key {
    int nodeID;
    int asciiChar;
};

/*
 * Edges are being stored in a hash table for better access time.
 * I was planning to use map instead of unorderedMap, but since map keeps the
 * elements in ordered fashion, it's average case time complexity is logn.
 * On the other hand, unorderedmap has a average case constant time complexity.
 * Key would be an integer which would be a function of nodeID and asciiChar
 */

/*
 * Insert an edge into the hash table
 */
void Edge::insert(string Input,unordered_map <long, Edge> &hash) {
    long key = returnHashKey(startNode, Input[startLabelIndex]);
   // edgeHash.insert(make_pair<int, Node>(key, this));
    hash[key] = *this;
  //  cout << "Inserted " << startNode << " " << endNode << " " << startLabelIndex  
 //       << " " << endLabelIndex <<  " " << key <<  endl; 
}
/*
 * Remove an edge from the hash table.
 */
void Edge::remove(string Input,unordered_map <long, Edge> &hash) {
     long key = returnHashKey(startNode, Input[startLabelIndex]);
     hash.erase(key);
     //cout << "Removed " << key << " " << startNode << " " << Input[startLabelIndex] << endl;
}

/*
 * Find an edge in the hash table corresponding to NODE & ASCIICHAR
 */
Edge Edge::findEdge(int node, int asciiChar, unordered_map <long, Edge> &hash) {
    long key = returnHashKey(node, asciiChar);
    unordered_map<long, Edge>::const_iterator search = hash.find(key);
    if (search != hash.end()) {
    //    cout << "Entry found for " << node << " " << asciiChar << endl;
        return hash.at(key);
    }
    
  //  cout << "Entry NOT found for " << node << " " << asciiChar << endl;
    // Return an invalid edge if the entry is not found.
    return Edge();
}
 // rootNode should be equal to the closest node to the end of the tree so
 // tht this can be used in the next iteration.
void suffixTree::migrateToClosestParent(string Input,Node* nodeArray,unordered_map <long, Edge> &hash) {
    // If the current suffix tree is ending on a node, this condition is already
    // met.
    if (endReal()) {
   //     cout << "Nothing needs to be done for migrating" << endl;
    }
    else {
        Edge e = Edge::findEdge(rootNode, Input[startIndex],hash);
        // Above will always return a valid edge as we call this method after
        // adding above.
        if(e.startNode == -1) {
            cout <<  rootNode << " " << startIndex << " " << Input[startIndex] << endl;
        }
        assert(e.startNode != -1);
        int labelLength = e.endLabelIndex - e.startLabelIndex;

        // Go down
        while (labelLength <= (endIndex - startIndex)) {
            startIndex += labelLength + 1;
            rootNode = e.endNode;
            if (startIndex <= endIndex) {
                e = Edge::findEdge(e.endNode, Input[startIndex],hash);
          if(e.startNode == -1) {
            cout <<  rootNode << " " << startIndex << " " << Input[startIndex] << endl;
        }
               assert(e.startNode != -1);
                labelLength = e.endLabelIndex - e.startLabelIndex;
            }
        }
        
    }
}

/*
 * Break an edge so as to add new string at a specific point.
 */
int breakEdge(suffixTree &s, Edge &e, Node* nodeArray, string Input,unordered_map <long, Edge> &hash) {
    // Remove the edge 
    e.remove(Input,hash);

    Edge *newEdge = new Edge(s.rootNode, e.startLabelIndex, 
                             e.startLabelIndex + s.endIndex - s.startIndex);
    newEdge -> insert(Input,hash);
    // Add the suffix link for the new node.
    nodeArray[newEdge -> endNode].suffixNode = s.rootNode;
    e.startLabelIndex += s.endIndex - s.startIndex + 1;
    e.startNode = newEdge -> endNode;
    e.insert(Input,hash);
    return newEdge->endNode;
}
/*
 * Main function which will carry out all the different phases of the Ukkonen's
 * algorithm. Through suffixTree we'll maintain the current position in the tree
 * and then add the prefix 0 -> lastIndex in the tree created in the previous
 * iteration.
 */
void carryPhase(suffixTree &tree, int lastIndex, int inputLength, string Input, Node* nodeArray, unordered_map <long, Edge> &hash) {
    int parentNode;
    // to keep track of the last encountered node.
    // Used for creating the suffix link.
    int previousParentNode = -1;
    while (true) {
        // First we try to match an edge for this, if there is one edge and all
        // other subsequent suffixs would already be there.
        Edge e;
        parentNode = tree.rootNode;

        if (tree.endReal() ) {
            e = Edge::findEdge(tree.rootNode, Input[lastIndex],hash);
            if (e.startNode != -1)
                break;
        }
        // If previoustree ends in between an edge, then we need to find that
        // edge and match after that. 
        else {
            e = Edge::findEdge(tree.rootNode, Input[tree.startIndex],hash);
            int diff = tree.endIndex - tree.startIndex;
            if (Input[e.startLabelIndex + diff + 1] == Input[lastIndex])
                // We have a match
                break;
            //If match was not found this way, then we need to break this edge
            // and add a node and insert the string.
      //      cout << " breaking edge " << endl; 
            parentNode = breakEdge(tree, e, nodeArray, Input, hash);
        }

        // We have not matchng edge at this point, so we need to create a new
        // one, add it to the tree at parentNode position and then insert it
        // into the hash table.
        //
        // We are creating a new node here, which means we also need to update
        // the suffix link here. Suffix link from the last visited node to the
        // newly created node.
        // cout << "adding new edge" << endl;
        Edge *newEdge = new Edge(parentNode, lastIndex, inputLength);
        newEdge -> insert(Input,hash);
        if (previousParentNode > 0)
            nodeArray[previousParentNode].suffixNode = parentNode;
        previousParentNode = parentNode;

        // Move to next suffix, i.e. next extension.
        if (tree.rootNode == 0)
            tree.startIndex++;
        else {
            tree.rootNode = nodeArray[tree.rootNode].suffixNode;
      //      printf("using suffix link while adding %d %d\n",tree.rootNode, nodeArray[tree.rootNode].suffixNode);
        }
        tree.migrateToClosestParent(Input,nodeArray,hash);
    }

    if (previousParentNode > 0)
        nodeArray[previousParentNode].suffixNode = parentNode;
    tree.endIndex++;
    tree.migrateToClosestParent(Input,nodeArray,hash);
}

bool search(string pattern, string Input, unordered_map <long, Edge> &hash) {
    int len = pattern.length();
    // Starting from 0 we start searching the pattern.
    Edge e = Edge::findEdge(0, pattern[0],hash);
    // index until where we have matched on edge.
    int iter = 0;
    int i = -1;
    if (e.startNode != -1) {
        while(i < len) {
            // cout << "Search:\tEdge: " << e.startNode << " " << e.endNode << " : " 
            //     << Input[e.startLabelIndex]  << " " << Input[e.endLabelIndex] << " I: " << i << endl;
            // Match the pattern on this edge.
            iter = 0;
            // Match this edge as much as possible.
            while (e.endLabelIndex >= e.startLabelIndex + iter)   
                    {
                        // cout << "Search:\tmatching " << Input[e.startLabelIndex + iter] << " " 
                        //      << pattern[i + iter + 1]
                        //     << " at index: " << e.startLabelIndex + iter << endl;
                        // If character matches we increase the iterator
                        // otherwise we are done. No match.
                        if (Input[e.startLabelIndex + iter] == pattern[i + iter + 1]) { 
                            iter++;
                            // If we have a match in the middle then we are done.
                            if (i + iter  + 1 >= len) {
                                // cout << "Search:\tWe have a match ending at " 
                                //      << e.startLabelIndex + iter  - 1 << endl;
                                return true;
                            }
                        }
                        else {
                            //cout << "Search:\tMatch not found, matched only upto index:" << i+iter << endl;
                            return false;     
                        }
                   }
            // We have done all possible matches on this edge. We can proceed
            // only if the entire label matches.
            assert(iter = (e.endLabelIndex - e.startLabelIndex + 1));

            // Now we need to find another edge to match.
            e = Edge::findEdge(e.endNode, pattern[i + iter + 1], hash);
            if (e.startNode == -1) {
                //cout << "Search:\tMatch not found, matched only upto " << i + iter  
                //     << " " << pattern[i + iter + 1]<< endl;
                return false;    
                }
            i+=(iter);
        }
    }
    //cout << "Search:\tMatched :D " << iter << " " << pattern << endl;
    return false;
}

/*
 * This function prints all the edges in the suffix tree.
 */
 
 
/* recursive DFS function */
void printAllEdges(suffixTree &tree, int inputLength, Node* nodeArray, string Input, unordered_map <long, Edge> &hash) {
    int count = 0;
    cout << "StartNode\tEndNode\tSuffixLink\tFirstIndex\tlastIndex\tString" << endl;
    // For auto : C++11 FTW :)
    for (auto it = hash.begin(); it != hash.end(); it++) {
        cout << it -> second.startNode << "\t\t" << it -> second.endNode 
            << "\t\t" << nodeArray[it -> second.endNode].suffixNode
            << "\t\t" << it -> second.startLabelIndex 
            << "\t\t" << it -> second.endLabelIndex
            << "\t\t";
        count++;
        int head;
        if (inputLength > it -> second.endLabelIndex)
            head = it -> second.endLabelIndex;
        else 
            head = inputLength;
        for (int i = it -> second.startLabelIndex; i < head + 1; i++) {
            cout << Input[i];
        }
        cout << endl;
    }
    cout << "Total edges: " << count << endl;
}

void recursiveLexDFS(suffixTree &tree, string Input, unordered_map <long, Edge>::iterator currNode,string *smallestString,unordered_map <long, Edge> &hash) {
  bool hasChild = false;
  std::map<char,unordered_map <long, Edge>::iterator > ordering;
  // cout << "current letter: " << Input[currNode->second.startLabelIndex] << endl;
  // cout << "smallestString before: " << *smallestString << endl;
  for (auto it = hash.begin(); it != hash.end(); it++) {
    if (it->second.startNode == currNode->second.endNode) {
          // cout << "hasChild" << endl;
          hasChild = true;
          ordering[Input[it->second.startLabelIndex]] = it;
    }
  }
  if (currNode->second.startLabelIndex == currNode->second.endLabelIndex && smallestString->length() < floor(Input.length()/2)) {
      smallestString->append(string(1,Input[currNode->second.startLabelIndex]));
  }
  else {
    for (auto i = currNode->second.startLabelIndex; i != currNode->second.endLabelIndex+1 && smallestString->length() < floor(Input.length()/2); i++) {
        smallestString->append(string(1,Input[i]));
    }
  }
  // cout << "smallestString after: " << *smallestString << endl;
  if (hasChild != true){
    return;
  }

  else {
    int count = 0;
    for (auto it = ordering.begin(); it != ordering.end(); it++) {
        if (count > 0) {
          break;
        }
        currNode = it->second;
        count++;
    }
    recursiveLexDFS(tree,Input,currNode,smallestString,hash);
  }
  return;
}

std::string baseLexDFS(suffixTree &tree,string Input, unordered_map <long, Edge> &hash) {
  unordered_map <long, Edge>::iterator currNode;
  //char highestLetter = 'z';
  std::string smallestString = "";
  int count = 0;
  char highestLetter = 'z';
  std::map<char,unordered_map <long, Edge>::iterator > ordering;
    // order nodes alphabetically
    for (auto it = hash.begin(); it != hash.end(); it++) {
      if (it->second.startNode == 0){
        ordering[Input[it->second.startLabelIndex]] = it;
      }
    } 
    for (auto it = ordering.begin(); it != ordering.end(); it++) {
        if (count > 0) {
          break;
        }
        currNode = it->second;
        count++;
    }
    recursiveLexDFS(tree,Input,currNode,&smallestString,hash);
  return smallestString;
}


void recursiveDFS(suffixTree &tree, string Input, unordered_map <long, Edge>::iterator currNode,std::vector<int> *suffixArray,unordered_map <long, Edge> &hash, int numChars) {
  bool hasChild = false;
  std::map<char,unordered_map <long, Edge>::iterator > ordering;
  for (auto it = hash.begin(); it != hash.end(); it++) {
    if (it->second.startNode == currNode->second.endNode) {
          hasChild = true;
          ordering[Input[it->second.startLabelIndex]] = it;
    }
  }
  if (currNode->second.startLabelIndex == currNode->second.endLabelIndex) {
      numChars++;
  }
  else {
    for (auto i = currNode->second.startLabelIndex; i != currNode->second.endLabelIndex; i++) {
      numChars++;
    }
  }

  if (hasChild != true){
    // leaf
    suffixArray->push_back(Input.length()-numChars);
    return;
  }

  else {
    int prevChar = numChars;
    int count = 0;
    for (auto it = ordering.begin(); it != ordering.end(); it++) {
        currNode = it->second;
        recursiveDFS(tree,Input,currNode,suffixArray,hash, numChars);
        numChars = prevChar;
        count++;
    }
  }
  return;
}

std::vector<int> baseDFS(suffixTree &tree,string Input, unordered_map <long, Edge> &hash) {
  unordered_map <long, Edge>::iterator currNode;
  std::vector<int> suffixArray;
  int numChars = 0;
  std::map<char,unordered_map <long, Edge>::iterator > ordering;
    // order nodes alphabetically
    for (auto it = hash.begin(); it != hash.end(); it++) {
      if (it->second.startNode == 0){
        ordering[Input[it->second.startLabelIndex]] = it;
      }
    } 


    for (auto it = ordering.begin(); it != ordering.end(); it++) {
        currNode = it->second;
        recursiveDFS(tree,Input,currNode,&suffixArray,hash, numChars);
        numChars = 0;
    }

  return suffixArray;
}

bool runPart1(string text,string pattern) {
  std::unordered_map <long, Edge> edgeHash;
  int inputLength;
  string Input;
  Node::noOfNodes = 1;
  Node* nodeArray;
  Input = text;
  inputLength = Input.length();
  // Allocating memory to the array of nodes.
  nodeArray = (Node *)malloc(2*inputLength*(sizeof (Node)));
  suffixTree tree (0, 0, -1);
  // Carry out different phases.
  for (int i = 0; i < inputLength; i++) {
      carryPhase(tree, i, inputLength, Input, nodeArray, edgeHash);
  }
  
  if (search(pattern,Input,edgeHash)) {
    return true;
  }
  else {
    return false;
  }
  return false;
}

std::string runLex(string text) {
  std::unordered_map <long, Edge> edgeHash;
  int inputLength;
  string Input;
  Node::noOfNodes = 1;
  Node* nodeArray;
  // ~ higher than alphabet
  Input = text+text+"~";
  inputLength = Input.length();
  // Allocating memory to the array of nodes.
  nodeArray = (Node *)malloc(2*inputLength*(sizeof (Node)));
  suffixTree tree (0, 0, -1);
  // Carry out different phases.
  for (int i = 0; i < inputLength; i++) {
      carryPhase(tree, i, inputLength, Input, nodeArray, edgeHash);
  }

  std::string smallest = baseLexDFS(tree, Input, edgeHash);
  return smallest;
}

std::vector<int> runArray(string text) {
  std::unordered_map <long, Edge> edgeHash;
  int inputLength;
  string Input;
  Node::noOfNodes = 1;
  Node* nodeArray;
  Input = text;
  //getline(cin,Input);
  inputLength = Input.length();
  // Allocating memory to the array of nodes.
  nodeArray = (Node *)malloc(2*inputLength*(sizeof (Node)));
  suffixTree tree (0, 0, -1);
  // Carry out different phases.
  for (int i = 0; i < inputLength; i++) {
      carryPhase(tree, i, inputLength, Input, nodeArray, edgeHash);
  }

  std::vector<int> sArray = baseDFS(tree,Input, edgeHash);
  return sArray;
}
