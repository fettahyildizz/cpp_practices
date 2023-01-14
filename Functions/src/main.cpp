#include "Tree.hpp"
#include "Node.hpp"

using namespace std;

int main() {

	Tree<int>* root = new Tree(20);
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

	Tree<int>* root2 = new Tree(root->findNode(15));
	Tree<int>* root3 = new Tree(root->findNode(15));
	Tree<int>* root4 = new Tree(root->findNode(33));
	Tree<int>* root5 = new Tree(root->findNode(20));


	if (*root == *root2) {
		cout << "root == root2 \n";
	}
	else {
		cout << "root != root2 \n";
	}
	if (*root2 == *root3) {
		cout << "root2 == root3 \n";
	}
	else {
		cout << "root2 != root3 \n";
	}
	if (*root3 == *root4) {
		cout << "root3 == root4 \n";
	}
	else {
		cout << "root3 != root4 \n";
	}
	if (*root6 == *root7) {
		cout << "root6 == root7 \n";
	}
	else {
		cout << "root6 != root7 \n";
	}
	// auto start = chrono::high_resolution_clock::now();
	//cout << "Count: " << root2->getCount() << '\n';
	//cout << "Max depth: " << root2->getMaxDepth() << '\n';

	/*auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << duration.count() << endl;*/
	return 0;
}