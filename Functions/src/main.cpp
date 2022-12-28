#include "Tree.hpp"
#include "Node.hpp"

using namespace std;

int main() {

  Tree *root = new Tree(20);
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
  root->insert(2);
  root->insert(4);
  root->insert(1);

  Tree *root2 = new Tree(root->findNode(5));

  // auto start = chrono::high_resolution_clock::now();
  cout << "Count: " << root2->getCount() << '\n';
  cout << "Max depth: " << root2->getMaxDepth() << '\n';

  /*auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << endl;*/
  return 0;
}