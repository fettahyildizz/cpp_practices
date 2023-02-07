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

	Tree<int>* root2 = root->convertToBalanced();

	// cout << "Height balanced: " << root2->isHeightBalanced() << '\n';
	
	cout << "Distance between 20 and 37 " << root->findDistance(20, 37) << '\n';
	cout << "Distance between 15 and 37 " << root->findDistance(15, 37) << '\n';
	cout << "Distance between 19 and 37 " << root->findDistance(19, 37) << '\n';
	cout << "Distance between 5 and 33 " << root->findDistance(5, 33) << '\n';
	cout << "Distance between 1 and 6 " << root->findDistance(1, 6) << '\n';
	cout << "Distance between 1 and 20 " << root->findDistance(1, 20) << '\n';
	cout << "Distance between 20 and 20 " << root->findDistance(20, 20) << '\n';
	cout << "Distance between 5 and 5 " << root->findDistance(5, 5) << '\n';
	cout << "Distance between 1 and 2 " << root->findDistance(1, 2) << '\n';
	cout << "Distance between 1 and 13 " << root->findDistance(1, 13) << '\n';


	return 0;
}