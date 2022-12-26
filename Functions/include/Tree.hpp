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
	Tree(const int& word_);
	Tree(Node* root_);
	~Tree();
	void insert(const int& data_);
	Node* findNode(const int& data_);
	void deleteKey(const int& data_);
	bool isHeightBalanced();
	vector<int> getSortedWords();
	int calculateCount();
	void calculateMaxDepth();
	const bool isLeaf(const Node* key_);
	void setCount(const int& count_);
	const int getCount();
	const int getMaxDepth();

};