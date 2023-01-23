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
	if (root->isHeightBalanced()) {
		cout << "Root is Height  balanced \n";
	}
	else cout << "Root Height is not balanced. \n";

	if (root2->isHeightBalanced()) {
		cout << "Root2 is Height  balanced \n";
	}
	else cout << "Root2 Height is not balanced. \n";

	cout << "ROOT************************* \n";
	cout << "Count: " << root->getCount() << '\n';
	cout << "Max depth: " << root->calculateMaxDepth() << '\n';
	cout << "Root data: " << root->getRoot()->data << '\n';

	cout << "\n\n\n ROOT2 ******************* \n";
	cout << "Count: " << root2->getCount() << '\n';
	cout << "Max depth: " << root2->calculateMaxDepth() << '\n';
	cout << "Root data: " << root2->getRoot()->data << '\n';


	return 0;
}