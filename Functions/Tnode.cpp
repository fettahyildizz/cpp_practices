#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Balanced binary search trees.
struct Node {
  int data;
  Node *left;
  Node *right;
  Node *parent;

  Node() {
    data = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }
  Node(const int &word_) {
    data = word_;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
  }

  void setParent(Node *n) { parent = n; }
  void setLeft(Node *n) { left = n; }
  void setRight(Node *n) { right = n; }

  void setData(const int &word_) { data = word_; }

  const Node getParent() { return *parent; }
  const int getData() { return data; }
};

class Tree {
private:
  int count = 0;
  Node *root;
  bool first_right_iter = true;
  bool first_left_iter = true;

public:
  Tree(const int &word_) {
    root = new Node(word_);
    count = 1;
  }

  ~Tree() { delete root; }

  void insert(const int &data_) {
    count += 1;

    Node *n = root; // Root node
    while (1) {
      if (data_ < n->getData()) {
        if (n->left != nullptr) {

          n = n->left;
          continue;
        } else {
          n->left = new Node(data_);
          n->left->setParent(n);
          break;
        }
      } else if (data_ > n->getData()) {

        if (n->right != nullptr) {
          n = n->right;
          continue;
        }

        else {
          n->right = new Node(data_);
          n->right->setParent(n);
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

  vector<int> getSortedWords() {
    vector<int> data_list;
    int ctr = 0;
    Node *n = root;
    while (ctr != count) {
      // TODO(fettah): Change find to binary_search() method for quicker
      // search.
      // If right word is printed, traverse to parent node.

      // FIX:Fixed when it tries to access n->right->word when n->right is null.
      if ((n->right != nullptr) &&
          (find(data_list.begin(), data_list.end(), n->right->getData()) !=
           data_list.end())) {
        n = n->parent;
      }

      // If there is not left word and right word is not printed, print current
      // node and traverse to right node.
      else if ((n->left == nullptr) && (n->right != nullptr) &&
               (!(find(data_list.begin(), data_list.end(),
                       n->right->getData()) != data_list.end()))) {
        ctr += 1;
        data_list.push_back(n->getData());
        if (n->right != nullptr) {
          n = n->right;
          continue;
        } else {
          n = n->parent;
        }
      }

      // If there is not left word and the word is not printed print the word.
      // If there is not right world, go to parent.

      else if ((n->left == nullptr) && (n->right == nullptr) &&
               (!(find(data_list.begin(), data_list.end(), n->getData()) !=
                  data_list.end()))) {

        ctr += 1;
        data_list.push_back((n->getData()));
        n = n->parent;
      }
      // If there is a left children node, traverse to left children node.
      else if ((n->left != nullptr) &&
               !(find(data_list.begin(), data_list.end(), n->left->getData()) !=
                 data_list.end())) {
        n = n->left;
        continue;
      }

      // If there is a left children node but you already pushed it back to
      // list, then traverse to right node.
      else if ((n->left != nullptr) &&
               (find(data_list.begin(), data_list.end(), n->left->getData()) !=
                data_list.end())) {
        ctr += 1;
        data_list.push_back(n->getData());
        if (n->right != nullptr) {
          n = n->right;
        } else {
          n = n->parent;
        }
      }
    }
    n = nullptr;
    return data_list;
  }

  const int getCount() { return count; }
};

int main() {

  Tree *root = new Tree(1000);
  for (int i = 0; i < 100000; i++) {
    root->insert(rand() % 100000);
  }

  //   root->insert(15);
  //   root->insert(30);
  //   root->insert(22);
  //   root->insert(37);
  //   root->insert(5);
  //   root->insert(9);
  //   root->insert(8);
  //   root->insert(7);
  //   root->insert(6);
  //   root->insert(10);
  //   root->insert(13);
  //   root->insert(15);
  //   root->insert(19);
  //   root->insert(16);
  //   root->insert(17);
  //   root->insert(33);
  //   root->insert(24);
  //   root->insert(4);
  //   root->insert(21);
  //   root->insert(43);
  //   root->insert(35);
  //   root->insert(27);
  //   root->insert(23);
  //   root->insert(31);
  //   root->insert(32);
  //   root->insert(34);
  //   root->insert(36);
  //   root->insert(41);

  auto start = chrono::high_resolution_clock::now();

  vector<int> sorted_words = root->getSortedWords();
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << endl;

  //   cout << "List: \n";
  //   for (const auto n : sorted_words) {
  //     cout << n << '\n';
  //   }
  //   cout << "Lists length: " << sorted_words.size() << '\n';
  cout << "Tree's size: " << root->getCount();
  return 0;
}