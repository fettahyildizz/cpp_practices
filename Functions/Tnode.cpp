#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Balanced binary search trees.

class Node {
private:
	string word;
	int count = 0;
	Node* left;
	Node* right;
	Node* parent;
	bool first_right_iter = true;
	bool first_left_iter = true;

public:
	Node(const string& word_) {
		word = word_;
		count = 1;
		right = nullptr;
		left = nullptr;
		parent = nullptr;
	}

	void setParent(Node* n) {
		parent = n;
	}
	void setWord(const string& word_) {
		word = word_;
	}

	const string getWord() {
		return word;
	}

	void insert(const string& word_) {
		count += 1;
		Node* n = this; // Root node
		while (1) {
			if (word_ < n->getWord()) {
				if (n->left != nullptr) {

					n = n->left;
					continue;
				}
				else {
					n->left->setWord(word_);
					n->left->setParent(n);
					break;
				}
			}
			else if (word_ > n->getWord()) {
				if (n->right != nullptr) {
					n = n->right;
					continue;
				}
				else {
					n->right->setWord(word_);
					n->right->setParent(n);
					break;
				}
			}

			else {
				cout << "Word is occupied already. \n";
				count -= 1;
				break;
			}

		}
	}

	vector<string> getSortedTree() {
		vector<string> data_list;
		Node* n = this;
		while (1) {
			//TODO(fettah): Change find to binary_search() method for quicker search.
			// If right word is printed, traverse to parent node.
			if (find(data_list.begin(), data_list.end(), n->right->getWord()) != data_list.end()) {
				n = n->parent;
			}

			// If right word is not printed, print current node and traverse to right node.
			else if ((n->left == nullptr) && !(find(data_list.begin(), data_list.end(), n->right->getWord()) != data_list.end())) {
				data_list.push_back(n->getWord());
				if (n->right != nullptr) {
					n = n->right;
					continue;
				}
				else {
					n = n->parent;
				}
			}

			// If there is a left children node, traverse to left children node.
			else if ((n->left != nullptr) && !(find(data_list.begin(), data_list.end(), n->left->getWord()) != data_list.end())) {
				n = n->left;
				continue;
			}

			// If there is a left children node but you already pushed it back to list, then traverse to right node.
			else if ((n->left != nullptr) && (find(data_list.begin(), data_list.end(), n->left->getWord()) != data_list.end())) {
				data_list.push_back(n->getWord());
				if (n->right != nullptr) {
					n = n->right;
				}
			}
		}

		return data_list;
	}
};


int main() {

	Node* root = new Node("20");
	root->insert("15");
	root->insert("30");
	root->insert("22");
	root->insert("37");
	root->insert("5");
	root->insert("9");
	root->insert("8");
	root->insert("7");
	root->insert("6");
	root->insert("10");
	root->insert("13");
	root->insert("15");
	root->insert("19");
	root->insert("16");
	root->insert("17");
	root->insert("33");
	root->insert("24");
	root->getSortedTree();


	return 0;
}