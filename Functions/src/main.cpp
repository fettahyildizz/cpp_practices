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

  // auto start = chrono::high_resolution_clock::now();
  Tree *root2 = new Tree(root->findNode(5));

  vector<int> sorted_words = root2->getSortedWords();
  cout << "List\n";
  for (const auto n : sorted_words) {
    cout << n << '\n';
  }

  cout << "node count: " << root2->getCount() << '\n';


    Tree *root3 = new Tree(root->findNode(9));

  vector<int> sorted_words3 = root3->getSortedWords();
  cout << "List\n";
  for (const auto n : sorted_words3) {
    cout << n << '\n';
  }

  cout << "node count: " << root3->getCount() << '\n';

  root->deleteKey(7);

  vector<int> sorted_words4 = root2->getSortedWords();
  cout << "List\n";
  for (const auto n : sorted_words4) {
    cout << n << '\n';
  }

  cout << "node count: " << root2->calculateCount() << '\n';



  vector<int> sorted_words5 = root3->getSortedWords();
  cout << "List\n";
  for (const auto n : sorted_words5) {
    cout << n << '\n';
  }

  cout << "node count: " << root3->calculateCount() << '\n';

  /*auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << endl;*/
  return 0;
}