#include "Node.hpp"
#include "Tree.hpp"

using namespace std;

// Node for tree structures.

Node::Node() {
	depth = 1;
	data = 0;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}
Node::Node(const int& word_) {
	depth = 1;
	data = word_;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}
Node::Node(const int& word_, const int& depth_) {
	depth = depth_;
	data = word_;
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

void Node::calculateMaxDepth(Node* root_) {
	int ctr = 0;
	vector<int> data_list;
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

void Node::setParent(Node* n) {
	parent = n;
	depth = parent->depth + 1;
}
void Node::setLeft(Node* n) { left = n; }
void Node::setRight(Node* n) { right = n; }

void Node::setData(const int& word_) { data = word_; }
void Node::setDepth(const int& depth_) { depth = depth_; }
int Node::getDepth(Node* root_) {

	Node* n = this;
	int depth_ = 1;
	while (n != root_) {

		n = n->parent;
		depth_ += 1;
	}
	return depth_;
}
const Node Node::getParent() { return *parent; }
const int Node::getData() { return data; }