#include "Tree.hpp"
#include "Node.hpp"

using namespace std;

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
	root->insert(18);
	root->insert(33);
	root->insert(24);
	root->insert(4);
	root->insert(2);
	root->insert(1);

	Tree* root2 = new Tree(root->findNode(15));

	// auto start = chrono::high_resolution_clock::now();
	//cout << "Count: " << root2->getCount() << '\n';
	//cout << "Max depth: " << root2->getMaxDepth() << '\n';

	//// cout << "Height balanced: " << root2->isHeightBalanced() << '\n';
	//if (root->isHeightBalanced()) {
	//	cout << "Height is balanced \n";
	//}
	//else cout << "Height is not balanced. \n";
	vector<int> sorted_array_{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	Tree* root3 = new Tree(sorted_array_);

	cout << "Count: " << root3->getCount() << '\n';
	cout << "Max depth: " << root3->calculateMaxDepth() << '\n';
	cout << "Root data: " << root3->getRoot()->data << '\n';
	cout << "Root->right data: " << root3->getRoot()->right->data << '\n';
	cout << "Root->left-> data: " << root3->getRoot()->left->data << '\n';
	cout << "Root->left->left data: " << root3->getRoot()->left->left->data << '\n';
	cout << "Root->right data: " << root3->getRoot()->right->data << '\n';
	cout << "Root->right->right data: " << root3->getRoot()->right->right->data << '\n';
	cout << "Root->left->right data: " << root3->getRoot()->left->right->data << '\n';
	cout << "Root->right->left data: " << root3->getRoot()->right->left->data << '\n';
	cout << "Root->left->left->left data: " << root3->getRoot()->left->left->left->data << '\n';
	if (root3->isHeightBalanced()) {
		cout << "Height is balanced \n";
	}
	else cout << "Height is not balanced. \n";
	

	/*const double split_index = floor(static_cast<float>(sorted_array_.size()) / 2);
	vector<int> split_low(sorted_array_.begin(), sorted_array_.begin() + split_index);
	vector<int> split_high(sorted_array_.begin() + split_index +1, sorted_array_.end());
	cout << "split index: " << split_index << '\n';;
	cout << "split low: ";
	for (auto a : split_low) {
		cout << a << " ";
	}
	cout << "\n";
	cout << "split high: ";
	for (auto a : split_high) {
		cout << a << " ";
	}*/
	/*auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << duration.count() << endl;*/
	return 0;
}