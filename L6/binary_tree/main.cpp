#include <fstream>
#include <iostream>
using namespace std;
struct sNode
{
    std::string word_;
    int counter_;
    sNode *l_ = nullptr;
    sNode *r_ = nullptr;
};
sNode *create_node(string word)
{
    sNode *tmp = new sNode;
    tmp->counter_ = 1;
    tmp->word_ = word;
    return tmp;
}
sNode *insert_node(sNode *node, string word)
{
    if (node->word_ == word) {
        node->counter_++;
        return node;
    }
    if (node->word_ > word) {
        if (node->l_ == nullptr) {
            node->l_ = create_node(word);
            return node->l_;
        } else {
            return insert_node(node->l_, word);
        }
    } else {
        if (node->r_ == nullptr) {
            node->r_ = create_node(word);
            return node->r_;
        } else {
            return insert_node(node->r_, word);
        }
    }
}

void print_node(sNode *node)
{
    cout << node->word_ << " - " << node->counter_ << endl;
}

void print_tree(sNode *node)
{
    if (node->l_ != nullptr) {
        print_tree(node->l_);
    }
    print_node(node);
    if (node->r_ != nullptr) {
        print_tree(node->r_);
    }
}

int main()
{
    sNode *root = nullptr;
    fstream file("gpl-3.0.txt", ios::in);
    if (file.is_open()) {
        while (!file.eof()) {
            string word;
            file >> word;
            // cout << word << endl;
            if (root == nullptr) {
                root = create_node(word);
            } else {
                insert_node(root, word);
            }
        }

        print_tree(root);
    }
    return 0;
}
