#pragma once
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include "Node.hpp"

using namespace std;

class Tree {
private:
	int count = 0;
	int max_depth = 0;
	Node* root;
	vector<Node*> nodes;
	bool first_right_iter = true;
	bool first_left_iter = true;

public:
	 bool operator== (Tree& rhs)const;
	Tree(const int& word_);
	Tree(Node* root_);
	/**
	* Constructor taking sorted array as parameter.
	* \param sorted_array_ sorted vector<int> to be constructed od.
	* \return creates height balanced binary search tree given by vector.
	* 
	*/
	Tree(vector<int>& sorted_array_);
	/**
	* Destructor of object.
	*/
	~Tree();
	/**
	* Insert a data to the correct position in binary search tree as a node.
	* \param data_ Value to be inserted in tree.
	* \return It does not return. 
	*/
	void insert(const int& data_);
	Node* findNode(const int& data_);
	void deleteKey(const int& data_);
	bool isHeightBalanced();
	vector<int> getSortedWords();
	int calculateCount();
	int calculateMaxDepth();
	const bool isLeaf(const Node* key_);
	void setCount(const int& count_);
	const int getCount();
	const int getMaxDepth();
	Node* Tree::getRoot();

};