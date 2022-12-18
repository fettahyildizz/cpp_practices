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
	int depth = -1;
	Node* left;
	Node* right;
	Node* parent;
	int data;

	Node() {
		depth = 1;
		data = 0;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	Node(const int& word_) {
		depth = 1;
		data = word_;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	Node(const int& word_, const int& depth_) {
		depth = depth_;
		data = word_;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}

	void setParent(Node* n) { parent = n; depth = parent->depth + 1; }
	void setLeft(Node* n) { left = n; }
	void setRight(Node* n) { right = n; }

	void setData(const int& word_) { data = word_; }
	void setDepth(const int& depth_) { depth = depth_; }
	int getDepth() {
		if (depth == -1) {
			throw runtime_error("Trying to access a null node.\n");
		}
		else {
			Node* n = this;
			int depth_ = 1;
			cout << "data: " << n->getData() << '\n';
			while (n->parent != nullptr) {
				
				
				n = n->parent;
				cout << "data: " << n->getData() << '\n';
				depth_ += 1;
			}
			return depth_;
		}
			
	}
	const Node getParent() { return *parent; }
	const int getData() { return data; }

};

class Tree {
private:
	int count = 0;
	int max_depth = 0;
	Node* root;
	vector<Node*> nodes;
	bool first_right_iter = true;
	bool first_left_iter = true;

public:
	Tree(const int& word_) {
		root = new Node(word_);
		nodes.push_back(root);
		count = 1;
		max_depth = 1;
	}

	~Tree() {
		delete root;
		for (const auto& node : nodes)
			delete node;
	}

	void insert(const int& data_) {
		count += 1;
		int depth_loop = 1;
		Node* n = root; // Root node
		while (1) {
			depth_loop += 1;
			if (data_ < n->getData()) {
				if (n->left != nullptr) {
					n = n->left;
					continue;
				}
				else {
					if (depth_loop > max_depth) {
						max_depth = depth_loop;
					}

					n->left = new Node(data_, depth_loop);
					n->left->setParent(n);
					nodes.push_back(n->left);
					break;
				}
			}
			else if (data_ > n->getData()) {

				if (n->right != nullptr) {
					n = n->right;
					continue;
				}

				else {
					if (depth_loop > max_depth) {
						max_depth = depth_loop;
					}
					n->right = new Node(data_, depth_loop);
					n->right->setParent(n);
					nodes.push_back(n->left);
					break;
				}
			}

			else {
				count -= 1;
				break;
			}
		}
		n = nullptr;
		// delete n;
	}

	Node* searchKey(const int& data_) {
		Node* n = root;
		while (1) {

			// If root is null.
			if (n == nullptr) {
				break;
			}
			// If current node's data is the key.
			else if (data_ == n->getData()) {
				break;
			}

			// If data is smaller than current node's data, traverse to left children
			// node.
			else if (data_ < n->getData()) {
				if (n->left != nullptr) {
					n = n->left;
					continue;
				}
				else {
					cout << "Not found key. ";
					n = nullptr;
					break;
				}
			}

			// If data is bigger than current node's data, traverse to right children
			// node.
			else {
				if (n->right != nullptr) {
					n = n->right;
					continue;
				}
				else {
					cout << "Not found key. ";
					n = nullptr;
					break;
				}
			}
		}
		return n;
	}

	void deleteKey(const int& data_) {
		Node* n = searchKey(data_);

		// Key is not found.
		if (n == nullptr)
			cout << "Key is not found.";

		// If key has no children node, delete it.
		else if ((n->right == nullptr) && (n->left == nullptr)) {
			if (n->parent != nullptr) {
				if (n->parent->right == n) {
					count -= 1;
					delete (n->parent->right);
					n->parent->right = nullptr;
				}
				else if (n->parent->left == n) {
					count -= 1;
					delete (n->parent->left);
					n->parent->left = nullptr;
				}
				else {
					throw "Error 1";
				}
			}

			// If key is the root node and has no children node.
			else {
				count -= 1;
				delete root;
				nodes.erase(nodes.begin());
				n = nullptr;

			}

		}

		// If key has only right children node.
		else if ((n->right != nullptr) && (n->left == nullptr)) {
			// If key is not root node.
			if (n->parent != nullptr) {
				if (n->parent->right == n) {
					count -= 1;
					n->right->parent = n->parent;
					n->parent->right = n->right;
					delete (n);
				}
				else if (n->parent->left == n) {
					count -= 1;
					n->right->parent = n->parent;
					n->parent->left = n->right;
					delete (n);
				}
				else {
					throw "Error 2";

				}
			}

			// If key is root node.
			else {
				count -= 1;
				n->right->parent = nullptr;
				root = n->right;
				nodes.erase(nodes.begin());
				delete n;
			}
		}

		// If key has only left children node.
		else if ((n->right == nullptr) && (n->left != nullptr)) {
			if (n->parent != nullptr) {
				if (n->parent->right == n) {
					count -= 1;
					n->left->parent = n->parent;
					n->parent->right = n->left;
					delete (n);

				}
				else if (n->parent->left == n) {
					count -= 1;
					n->left->parent = n->parent;
					n->parent->left = n->left;
					delete (n);
				}
				else {
					throw "Error 2";
				}
			}

			// If key is root node.
			else {
				count -= 1;
				n->left->parent = nullptr;
				root = n->left;
				nodes.erase(nodes.begin());
				delete n;
			}
			
		}

		// If key has two children node. Determine if it has inorder successor (Left
		// submost children node of the right children node.) or inorder
		// predecessor.
		else if ((n->right != nullptr) && (n->left != nullptr)) {

			// If it has inorder successor.
			if (n->right->left != nullptr) {

				Node* successor = n->right->left;
				while (successor->left != nullptr) {
					successor = successor->left;
				}

				if (successor->right != nullptr) {
					successor->parent->left = successor->right;
					successor->right->parent = successor->parent; 
				}

				// If key is not rood node.
				if (n->parent != nullptr) {
					if (n->parent->right == n) {

						successor->parent = n->parent;
						n->parent->right = successor;
						successor->left = n->left;
						successor->right = n->right;
						n->right->parent = successor;
						n->left->parent = successor;
						count -= 1;
						delete (n);
					}
					else if (n->parent->left == n) {
						successor->parent = n->parent;
						n->parent->left = successor;
						successor->left = n->left;
						successor->right = n->right;
						n->right->parent = successor;
						n->left->parent = successor;
						count -= 1;
						delete (n);
					}
				}

				// If key is root node.
				else {
					successor->right = n->right;
					successor->left = n->left;
					successor->parent = nullptr;
					n->right->parent = successor;
					n->left->parent = successor;
					count -= 1;
					root = successor;
					nodes.erase(nodes.begin());
					delete n;
				}
				
			}
			// If it has inorder predecessor node.
			else if (n->left->right != nullptr) {

				Node* successor = n->left->right;
				while (successor->right != nullptr) {
					successor = successor->right;
				}
				if (successor->left != nullptr) {
					successor->parent->right = successor->left;
					successor->left->parent = successor->parent;
				}

				// If key is not root node.
				if (n->parent != nullptr) {
					if (n->parent->right == n) {
						successor->parent = n->parent;
						n->parent->right = successor;
						successor->left = n->left;
						successor->right = n->right;
						n->right->parent = successor;
						n->left->parent = successor;
						count -= 1;
						delete (n);

					}
					else if (n->parent->left == n) {
						successor->parent = n->parent;
						n->parent->left = successor;
						successor->left = n->left;
						successor->right = n->right;
						n->right->parent = successor;
						n->left->parent = successor;
						count -= 1;
						delete (n);
					}
				}

				// If key is root node.
				else {
					successor->right = n->right;
					successor->left = n->left;
					successor->parent = nullptr;
					n->right->parent = successor;
					n->left->parent = successor;
					count -= 1;
					root = successor;
					nodes.erase(nodes.begin());
					delete n;
				}
				
			}

			// If key dont have inorder successor or predecessor.
			else {
				// If key is not rood node.
				if (n->parent != nullptr) {
					if (n->parent->right == n) {
						n->right->parent = n->parent;
						n->parent->right = n->right;
						count -= 1;
						delete (n);
					}
					else if (n->parent->right == n) {
						n->left->parent = n->parent;
						n->parent->left = n->left;
						count -= 1;
						delete (n);
					}
					else {
						throw "Error 3.\n";
					}
				}

				// If key is root node.
				else {
					n->right->parent = nullptr;
					n->right->left = n->left;
					count -= 1;
					root = n->right;
					nodes.erase(nodes.begin());
					delete n;
				}
				
			}
		}
	}

	bool isHeightBalanced

	vector<int> getSortedWords() {
		vector<int> data_list;
		int ctr = 0;
		Node* n = root;
		while (ctr != count) {
			// If right word is printed, traverse to parent node.
			if ((n->right != nullptr) &&
				(binary_search(data_list.begin(), data_list.end(),
					n->right->getData()))) {
				n = n->parent;
			}

			// If there is not left word and right word is not printed, print current
			// node and traverse to right node.
			else if ((n->left == nullptr) && (n->right != nullptr) &&
				(!(binary_search(data_list.begin(), data_list.end(),
					n->right->getData())))) {
				ctr += 1;
				data_list.push_back(n->getData());
				if (n->right != nullptr) {
					n = n->right;
					continue;
				}
				else {
					n = n->parent;
				}
			}

			// If there is not left word and the word is not printed print the word.
			// If there is not right world, go to parent.

			else if ((n->left == nullptr) && (n->right == nullptr) &&
				(!(binary_search(data_list.begin(), data_list.end(),
					n->getData())))) {
				ctr += 1;
				data_list.push_back((n->getData()));
				n = n->parent;
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
				if (n->right != nullptr) {
					n = n->right;
				}
				else {
					n = n->parent;
				}
			}
		}
		n = nullptr;
		return data_list;
	}

	const bool isLeaf(const Node* key_) {
		if ((key_ != nullptr) && (key_->right == nullptr) &&
			(key_->left == nullptr)) {
			return true;
		}
		else
			return false;
	}
	const int getCount() { return count; }
	const int getMaxDepth() { return max_depth; }
};

int main() {

	Tree* root = new Tree(20);
	/*for (int i = 0; i < 1000000; i++) {
			root->insert(rand() % 1000000);
	}*/

	root->insert(15);
	root->insert(30);
	root->insert(22);
	root->insert(37);
	root->insert(5);
	root->insert(9);
	root->insert(8);
	root->insert(7);
	root->insert(6);
	root->insert(10);
	root->insert(13);
	root->insert(15);
	root->insert(19);
	root->insert(16);
	root->insert(17);
	root->insert(33);
	root->insert(24);
	root->insert(4);
	root->insert(21);
	root->insert(43);
	root->insert(35);
	root->insert(27);
	root->insert(23);
	root->insert(31);
	root->insert(32);
	root->insert(34);
	root->insert(36);
	root->insert(41);
	root->insert(18);
	root->insert(44);
	root->insert(39);
	root->insert(40);

	// auto start = chrono::high_resolution_clock::now();

	vector<int> sorted_words = root->getSortedWords();
	/*auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << duration.count() << endl;*/

	/*for (const auto n : sorted_words) {
		cout << n << '\n';
	}*/
	cout << "Tree's size: " << root->getCount() << '\n';
	cout << "Get Max depth: " << root->getMaxDepth() << '\n';
	cout << "Node=32 depth: " << root->searchKey(32)->getDepth() << '\n';
	cout << "Node=36 depth: " << root->searchKey(36)->getDepth() << '\n';
	cout << "Node=23 depth: " << root->searchKey(23)->getDepth() << '\n';
	root->deleteKey(20);


	return 0;
}
