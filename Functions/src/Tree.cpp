#include "Tree.hpp"
#include "Node.hpp"
#include <stdexcept>

using namespace std;

// Balanced binary search trees.
// TODO: Create isHeightBalanced() method

Tree::Tree(const int& word_) {
	root = new Node(word_);
	nodes.push_back(root);
	count = 1;
	max_depth = 1;
}

Tree::Tree(Node* root_) {
	if (root_ != nullptr) {
		root = root_;
		count = this->calculateCount();
		max_depth = this->calculateMaxDepth();
	}
	else {
		cout << "This node does not exist.\n";
	}
}
Tree::Tree(vector<int>& sorted_array_) {
	const size_t split_index = floor(static_cast<float>(sorted_array_.size() / 2));
	root = new Node(sorted_array_[split_index]);
	count = 1;
	nodes.push_back(root);
	Node* node = root;

	auto insert = [](Node* node_, vector<int>& sorted_array_, const size_t& parent_index_, int& count, vector<Node*>& nodes, auto& lambda) -> void {
		vector<int> split_low(sorted_array_.begin(), sorted_array_.begin() + parent_index_);
		vector<int> split_high(sorted_array_.begin() + parent_index_ + 1, sorted_array_.end());
		if (split_low.size() > 0) {
			const size_t left_child_index = floor(static_cast<float>(split_low.size()) / 2);
			node_->left = new Node(split_low[left_child_index]);
			node_->left->parent = node_;
			count += 1;
			nodes.push_back(node_->left);
			lambda(node_->left, split_low, left_child_index, count, nodes, lambda);
		}
		if (split_high.size() > 0) {
			if (split_high.size() == 2) {
				const size_t right_child_index = 0;
				node_->right = new Node(split_high[right_child_index]);
				node_->right->parent = node_;
				count += 1;
				nodes.push_back(node_->left);
				lambda(node_->right, split_high, right_child_index, count, nodes, lambda);
			}
			else {
				const size_t right_child_index = floor(static_cast<float>(split_high.size() / 2));
				node_->right = new Node(split_high[right_child_index]);
				node_->right->parent = node_;
				count += 1;
				nodes.push_back(node_->left);
				lambda(node_->right, split_high, right_child_index, count, nodes, lambda);
			}
		}
	};
	insert(root, sorted_array_, split_index, count, nodes, insert);
}

Tree::~Tree() {
	delete root;
	for (const auto& node : nodes)
		delete node;
}

bool Tree::operator== (Tree& rhs_) const {

	auto traverse = [](Node* lhs_node, Node* rhs_node, auto& lambda) -> bool {
		if ((rhs_node != nullptr) && (lhs_node != nullptr)) {
			if (rhs_node->getData() != lhs_node->getData()) {
				return false;
			}
			else {
				lambda(rhs_node->left, lhs_node->left, lambda);
				lambda(rhs_node->right, lhs_node->right, lambda);
			}
		}
		else if ((rhs_node != nullptr) && (lhs_node == nullptr)) { cout << "2\n"; return false; }
		else if ((rhs_node == nullptr) && (lhs_node != nullptr)) {
			return false;
		}
		else {
			return true;
		}
		
	};
	Node* node = this->root;
	Node* rhs_node = rhs_.getRoot();
	return traverse(node, rhs_node, traverse);
}

void Tree::insert(const int& data_) {
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

Node* Tree::findNode(const int& data_) {
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

void Tree::deleteKey(const int& data_) {
	Node* n = findNode(data_);

	// Key is not found.
	if (n == nullptr)
		cout << "Key is not found.";

	// If key has no children node, delete it.
	else if ((n->right == nullptr) && (n->left == nullptr)) {
		if (n->parent != nullptr) {
			if (n->parent->right == n) {
				count -= 1;
				n->parent->right = nullptr;
				delete (n->parent->right);

			}
			else if (n->parent->left == n) {
				count -= 1;
				n->parent->left = nullptr;
				delete (n->parent->left);

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
// TODO:
bool Tree::isHeightBalanced() {
	Node* node = root;
	if (node == nullptr)
		return false;

	if ((node->left != nullptr) && (node->right != nullptr)) {

		Tree* left_subtree = new Tree(node->left);
		Tree* right_subtree = new Tree(node->right);
		if (abs(left_subtree->calculateMaxDepth() -
			right_subtree->calculateMaxDepth()) > 1) {

			return false;
		}
		else {
			left_subtree->isHeightBalanced();
			right_subtree->isHeightBalanced();
		}
	}
	else {
		return true;
	}
}

vector<int> Tree::getSortedWords() {
	vector<int> data_list;
	int ctr = 0;
	Node* n = root;
	while (ctr != count) {
		// If right word is printed, traverse to parent node.
		if ((n->right != nullptr) &&
			(binary_search(data_list.begin(), data_list.end(),
				n->right->getData())) &&
			(n != root)) {
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
				if (n != root)
					n = n->parent;
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
			if (n != root) {
				n = n->parent;
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
			if (n->right != nullptr) {
				n = n->right;
			}
			else {
				if (n != root)
					n = n->parent;
				else {
					break;
				}
			}
		}
	}
	n = nullptr;
	return data_list;
}

int Tree::calculateCount() {
	vector<int> data_list;
	int ctr = 0;
	Node* n = root;
	while (1) {

		// If there is a left children node
		if ((n->left != nullptr)) {
			// If left children is not printed, traverse to left children node.
			if (!(find(data_list.begin(), data_list.end(), n->left->getData()) !=
				data_list.end())) {
				n = n->left;
				continue;
			}
			// If left children is printed
			else {
				// If left children is printed and there is a right children.
				if (n->right != nullptr) {
					// If right children is not printed, traverse to right children
					if (!(find(data_list.begin(), data_list.end(), n->right->getData()) !=
						data_list.end())) {
						n = n->right;
						continue;
					}
					// If right children is printed
					else {
						ctr += 1;
						data_list.push_back((n->getData()));
						if (n == root) {
							break;
						}
						else {
							n = n->parent;
							continue;
						}
					}
				}
				// If left children is printed and there is not a right children.
				// Print current node and if there is one, traverse to parent node.
				else {
					ctr += 1;
					data_list.push_back((n->getData()));
					if (n == root) {
						break;
					}
					else {
						n = n->parent;
						continue;
					}
				}
			}
		}

		// If there is not a left children node, but there is only right children
		// node.
		else if (n->right != nullptr) {
			// If right node is printed on the list.
			if ((find(data_list.begin(), data_list.end(), n->right->getData()) !=
				data_list.end())) {
				ctr += 1;
				data_list.push_back((n->getData()));
				if (n != root) {
					n = n->parent;
				}
				else {
					break;
				}
			}
			// If right children node is not printed.
			else {
				n = n->right;
				continue;
			}
		}
		// If there is no children node.
		else if ((n->right == nullptr) && (n->left == nullptr)) {
			ctr += 1;
			data_list.push_back((n->getData()));
			if (n != root) {
				n = n->parent;
			}
			else {
				break;
			}
		}
		else {
			throw runtime_error("Error 1");
		}
	}
	n = nullptr;
	count = ctr;
	return ctr;
}

int Tree::calculateMaxDepth() {
	vector<int> data_list;
	int depth = 0;
	Node* n = root;
	while (1) {
		// If there is a left children node
		if ((n->left != nullptr)) {
			// If left children is not printed, traverse to left children node.
			if (!(find(data_list.begin(), data_list.end(), n->left->getData()) !=
				data_list.end())) {
				n = n->left;
				continue;
			}
			// If left children is printed
			else {
				// If left children is printed and there is a right children.
				if (n->right != nullptr) {
					// If right children is not printed, traverse to right children
					if (!(find(data_list.begin(), data_list.end(), n->right->getData()) !=
						data_list.end())) {
						n = n->right;
						continue;
					}
					// If right children is printed
					else {
						data_list.push_back((n->getData()));

						if (n->getDepth(root) >= depth) {
							depth = n->getDepth(root);
						}
						if (n == root) {
							break;
						}
						else {
							n = n->parent;
							continue;
						}
					}
				}
				// If left children is printed and there is not a right children.
				// Print current node and if there is one, traverse to parent node.
				else {
					data_list.push_back((n->getData()));

					if (n->getDepth(root) >= depth) {
						depth = n->getDepth(root);
					}
					if (n == root) {
						break;
					}
					else {
						n = n->parent;
						continue;
					}
				}
			}
		}

		// If there is not a left children node, but there is only right children
		// node.
		else if (n->right != nullptr) {
			// If right node is printed on the list.
			if ((find(data_list.begin(), data_list.end(), n->right->getData()) !=
				data_list.end())) {
				data_list.push_back((n->getData()));

				if (n->getDepth(root) >= depth) {
					depth = n->getDepth(root);
				}
				if (n != root) {
					n = n->parent;
				}
				else {
					break;
				}
			}
			// If right children node is not printed.
			else {
				n = n->right;
				continue;
			}
		}
		// If there is no children node.
		else if ((n->right == nullptr) && (n->left == nullptr)) {
			data_list.push_back((n->getData()));

			if (n->getDepth(root) >= depth) {
				depth = n->getDepth(root);
			}
			if (n != root) {
				n = n->parent;
			}
			else {
				break;
			}
		}
		else {
			throw runtime_error("Error 1");
		}
	}
	n = nullptr;
	max_depth = depth;
	return depth;
}

void Tree::setCount(const int& count_) { count = count_; }
const bool Tree::isLeaf(const Node* key_) {
	if ((key_ != nullptr) && (key_->right == nullptr) &&
		(key_->left == nullptr)) {
		return true;
	}
	else
		return false;
}
const int Tree::getCount() { return count; }
const int Tree::getMaxDepth() { return max_depth; }
Node* Tree::getRoot() { return root; }
