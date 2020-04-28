#ifndef NODE_H
#define NODE_H

#include <bits/stdc++.h>

using namespace std;

class Node {

public:

    Node(char state[3][3], int depth, pair<int, int> generator_operator);
    ~Node();

    Node(const Node& node);
    Node& operator=(const Node& node);

    void generate_children();
    int calculate_wellness();

    pair<int, int> get_best_operator();

protected:

    int calculate_heuristics();
    int calculate_possibilities(char player);

    char state[3][3];
    int depth;
    int wellness;
    pair<int, int> generator_operator;

    static char players[2];
    static int limit;
    char winner();
    vector<shared_ptr<Node>> children;
};


#endif //NODE_H