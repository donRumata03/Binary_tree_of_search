#ifndef TREE_CPP
#define TREE_CPP
#pragma once

#include <vector>
#include <map>
#include <iostream>
using namespace std;

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

#define print_if_not_none(pointer) ((pointer != 0) ? ((char*)(pointer->val)) : ("none"))


class Node
{
    public:
        Node* left;
        Node* right;
        int val;
        bool has_val;
        char splt = ' ';

        Node();
        Node(int);
        Node(char);
        void construct_node_form_input();
        vector<Node*> get_kids();
        int get_height();
        bool push_back(Node* val);
        int count_lenght();
        void print_node_vec(vector<Node*>&);
        friend ostream& operator<< (std::ostream& out, const Node& node);
    // Lex_order:
        void print_lex_ord();
        vector<Node*> all_lex_ord();
        void add_to_order(vector<Node*>* nodes);
    // Leaves:
        vector<Node*> leaves();
        void  print_leaves();
        void add_leaves(vector<Node*>* nodes);
    // Rels:
        vector<Node*> rels();
        void  print_rels();
        void add_rels(vector<Node*>* nodes);
    // Strings
        vector<Node*> strings();
        void  print_strings();
        void add_strings(vector<Node*>* nodes);
    // Ballance
        bool is_ballanced();
        void print_ballanceness();
    // Count additions
        map<int, int> input_with_counting();
        void cout_counting();
};

#endif
