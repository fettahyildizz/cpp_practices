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

template<typename T>

struct Node {
	int depth;
	Node* left;
	Node* right;
	Node* parent;
	T data;

	Node() {
		depth = 1;
		data = 0;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	};
	Node(const T& value_) {
		depth = 1;
		data = value_;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	Node(const T& word_, const int& depth_) {
		depth = depth_;
		data = word_;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

	void calculateMaxDepth(Node* root_) {
		int ctr = 0;
		vector<T> data_list;
		int depth = 0;
		Node* n = this;
		while (1) {
			// If right word is printed, traverse to parent node.
			if ((n->right != nullptr) &&
				(binary_search(data_list.begin(), data_list.end(),
					n->right->getData())) &&
				(n != this)) {
				n = n->parent;
			}

			// If there is not left word and right word is not printed, print current
			// node and traverse to right node.
			else if ((n->left == nullptr) && (n->right != nullptr) &&
				(!(binary_search(data_list.begin(), data_list.end(),
					n->right->getData())))) {
				ctr += 1;
				data_list.push_back(n->getData());

				if (n->getDepth(root_) >= depth) {
					depth = n->getDepth(root_);
				}

				if (n->right != nullptr) {
					n = n->right;
					continue;
				}
				else {
					if (n != this) {
						n = n->parent;
						continue;
					}

					else
						break;
				}
			}

			// If there is not left word and the word is not printed print the word.
			// If there is not right world, go to parent.

			else if ((n->left == nullptr) && (n->right == nullptr) &&
				(!(binary_search(data_list.begin(), data_list.end(),
					n->getData())))) {
				ctr += 1;
				data_list.push_back((n->getData()));

				if (n->getDepth(root_) >= depth) {
					depth = n->getDepth(root_);
				}

				if (n != this) {
					n = n->parent;
					continue;
				}
				else {
					break;
				}
			}

			// If there is a left children node, traverse to left children node.
			else if ((n->left != nullptr) &&
				!(binary_search(data_list.begin(), data_list.end(),
					n->left->getData()))) {
				n = n->left;
				continue;
			}

			// If there is a left children node but you already pushed it back to
			// list, then traverse to right node.
			else if ((n->left != nullptr) &&
				(binary_search(data_list.begin(), data_list.end(),
					n->left->getData()))) {
				ctr += 1;
				data_list.push_back(n->getData());

				if (n->getDepth(root_) >= depth) {
					depth = n->getDepth(root_);
				}

				if (n->right != nullptr) {
					n = n->right;
				}
				else {
					if (n != this) {
						n = n->parent;
						continue;
					}
					else {
						break;
					}
				}
			}
		}
		n = nullptr;
	}

	void setParent(Node* n) {
		parent = n;
		depth = parent->depth + 1;
	}
	void setLeft(Node* n) { left = n; }
	void setRight(Node* n) { right = n; }

	void setData(const T& value_) { data = value_; }
	void setDepth(const int& depth_) { depth = depth_; }
	int getDepth(Node* root_) {

		Node* n = this;
		int depth_ = 1;
		while (n != root_) {

			n = n->parent;
			depth_ += 1;
		}
		return depth_;
	}
	const Node getParent() { return *parent; }
	const T getData() { return data; }

};