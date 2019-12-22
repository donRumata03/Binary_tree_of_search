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


Node::Node() {
    left = nullptr;
    right = nullptr;
    has_val = false;
    val = -1;
}


Node::Node(int _val) : Node() {
    val = _val;
    has_val = true;
}

Node::Node(char) : Node() {
    this->construct_node_form_input();
}

vector<Node*> Node::get_kids() {
    vector<Node*> kids;
    if (left) {
        kids.push_back(left);
    }
    if (right) {
        kids.push_back(right);
    }
    return kids;

}


int Node::get_height() {
    int left_height = 0;
    int right_height = 0;
    if(this->left) left_height = (this->left)->get_height();
    if (this->right) right_height = (this->right)->get_height();
    return 1 + max(left_height, right_height);
}

bool Node::push_back(Node* son) { // False => no adding; True => there was the same element
    if (!has_val) {
        val = (*son).val;
        has_val = true;
        return false;
    }
    if ((*son).val > val) {
        if (right) { // Right node exists
            return right->push_back(son);
        }
        else {
            right = son;
            return false;
        }
    }
    else if ((*son).val == val) {
        return true;
    }
    else {
        if (left) { // Left node exists
            return left->push_back(son);
        }
        else {
            left = son;
            return false;
        }
    }
}

int Node::count_lenght()
{
    int left_length = 0;
    int right_length = 0;
    if (this->left) left_length = (this->left)->count_lenght();
    if (this->right) right_length = (this->right)->count_lenght();
    return 1 + left_length + right_length;
}

vector<Node*> Node::all_lex_ord()
{
    vector<Node*> nodes;
    this->add_to_order(&nodes);
    return nodes;
}

void Node::add_to_order(vector<Node*> *nodes) {
    if (this->left) {
        (this->left)->add_to_order(nodes);
    }
    (*nodes).push_back(this);
    if (this->right) {
        (this->right)->add_to_order(nodes);
    }
}

vector<Node*> Node::leaves()
{
    vector<Node*> nodes;
    this->add_leaves(&nodes);
    return nodes;
}

void Node::print_leaves()
{
    auto vec = (*this).leaves();
    this->print_node_vec(vec);
}

void Node::add_leaves(vector<Node*>* nodes)
{
    bool is_leave = true;
    if (this->left) {
        is_leave = false;
        (this->left)->add_leaves(nodes);
    }
    if (this->right) {
        is_leave = false;
        (this->right)->add_leaves(nodes);
    }
    else if (is_leave) {
        nodes->push_back(this);
    }
}



vector<Node*> Node::rels()
{
    vector<Node*> nodes;
    this->add_rels(&nodes);
    return nodes;
}

void Node::print_rels()
{
    auto vec = (*this).rels();
    this->print_node_vec(vec);
}

void Node::add_rels(vector<Node*>* nodes)
{
    bool is_rel = (this->left && this->right);
    if (this->left) {
        (this->left)->add_rels(nodes);
    }
    if (this->right) {
        (this->right)->add_rels(nodes);
    }
    if (is_rel) {
        nodes->push_back(this);
    }
}



vector<Node*> Node::strings()
{
    vector<Node*> nodes;
    this->add_strings(&nodes);
    return nodes;
}

void Node::print_strings()
{
    auto vec = (*this).strings();
    this->print_node_vec(vec);
}

void Node::add_strings(vector<Node*>* nodes)
{
    bool is_rel = (this->left || this->right) && (!(this->right && this->left));
    if (this->left) {
        (this->left)->add_strings(nodes);
    }
    if (this->right) {
        (this->right)->add_strings(nodes);
    }
    if (is_rel) {
        nodes->push_back(this);
    }
}

bool Node::is_ballanced(){
    if (this->left && this->right) {
        if (abs((this->left)->get_height() - (this->right)->get_height()) > 1) {
            return false;
        }
        return (this->left)->is_ballanced() && (this->right)->is_ballanced();
    }
    else if (this->left) {
        if ((this->left)->get_height() <= 1) return true;
        return false;
    }
    else if (this->right) {
        if ((this->right)->get_height() <= 1) return true;
        return false;
    }
    else {
        return true;
    }    
}

void Node::print_ballanceness()
{
    cout << ((this->is_ballanced()) ? "YES" : "NO") << endl;
}




void Node::print_lex_ord()
{
    vector<Node*> nodes = (*this).all_lex_ord();
    this->print_node_vec((nodes));
}

void Node::print_node_vec(vector<Node*> &vec)
{
    // char splt = '\n';
    char splt = ' ';
    for (auto i : vec) {
        cout << i->val << splt;
    }
    cout << endl;
}


void Node::construct_node_form_input() {
    int inp = -1;
    while (inp != 0) {
        cin >> inp;
        if (inp == 0) {
            break;
        }
        this->push_back(new Node(inp));
    }
}


map<int, int> Node::input_with_counting() {
    int inp = -1;
    bool this_in;
    map<int, int> data;
    while (inp != 0) {
        cin >> inp;
        if (inp == 0) {
            break;
        }
        this_in = this->push_back(new Node(inp));
        if (!this_in) {
            data[inp] = 1;
        }
        else {
            data[inp] += 1;
        }
    }
    return data;
}


void Node::cout_counting() {
    map<int, int> data = this->input_with_counting();
    for (auto i : data) {
        cout << i.first << " " << i.second << endl;
    }
}


std::ostream& operator<< (std::ostream& out, const Node& node) {
    out << "Node: " << node.val << "; Left: ";
    if (node.left) {
        out << *(node.left);
    }
    else {
        out << "nothing";
    }
    out << "; Right: ";
    if (node.right) {
        out << *(node.right);
    }
    else {
        out << "nothing";
    }
    out << " ; ";
    return out;
}



int main(){
    Node tree ('i');
    tree.print_leaves();
    return 0;
}