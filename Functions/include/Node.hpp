#pragma once
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

// Balanced binary search trees.

struct Node {
	int depth;
	Node* left;
	Node* right;
	Node* parent;
	int data;

	Node();
	Node(const int& word_);
	Node(const int& word_, const int& depth_);
	void setParent(Node* n);
	void setLeft(Node* n);
	void setRight(Node* n);
	void setData(const int& word_);
	void setDepth(const int& depth_);
	int getDepth();
	const Node getParent();
	const int getData();

};