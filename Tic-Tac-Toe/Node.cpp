#include "Node.h"

char Node::players[2] = {'X', 'O'};
int Node::limit = 10;

Node::Node(char state[3][3], int depth, pair<int, int> generator_operator) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->state[i][j] = state[i][j];
        }
    }

    this->depth = depth;

    if (depth == Node::limit) {
        wellness = calculate_heuristics();
    } else {
        char win = winner();

        if (win == 'O') {
            wellness = -100;
        } else if (win == 'X') {
            wellness = 100;
        } else if (win == 'D') {
            wellness = 0;
        } else {
            generate_children();
            wellness = calculate_wellness();
        }
    }

    this->generator_operator = generator_operator;

/*
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < depth; k++) cout << "\t";
        for (int j = 0; j < 3; j++) {
            cout << state[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < depth + 1; i++) cout << "\t"; cout << wellness << endl;
*/
}

Node::~Node() {

}

Node::Node(const Node &node) {
    
    this->wellness = node.wellness;
    this->depth = node.depth;
    this->generator_operator = node.generator_operator;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->state[i][j] = state[i][j];
        }
    }

    for (auto i : children) {
        this->children.push_back(i);
    }
}

Node &Node::operator=(const Node &node) {

    this->wellness = node.wellness;
    this->depth = node.depth;
    this->generator_operator = node.generator_operator;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->state[i][j] = state[i][j];
        }
    }

    for (auto i : children) {
        this->children.push_back(i);
    }

    return *this;
}

void Node::generate_children() {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state[i][j] == '-') {
                char copy_state[3][3];

                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        copy_state[k][l] = state[k][l];
                    }
                }

                copy_state[i][j] = players[depth % 2];

                auto new_node = make_shared<Node>(copy_state, depth + 1, make_pair(i, j));
                children.push_back(new_node);
            }
        }
    }
}

int Node::calculate_wellness() {

    // Ha mi lépünk akkor a legjobba akarunk lépni
    if (depth % 2 == 0) {
        int wellness = INT_MIN;
        for (auto i : children) {
            wellness = max(wellness, i.get()->wellness);
        }
        return wellness;
    } else {
        // Ha az ellenfél lép akkor a nekünk legrosszabba akar lépni
        int wellness = INT_MAX;
        for (auto i : children) {
            wellness = min(wellness, i.get()->wellness);
        }
        return wellness;
    }
}

// Az a legjobb amelyiknek a jósága annyi mint jelenlegi jósága
pair<int, int> Node::get_best_operator() {

    for (auto i : children) {
        if (i.get()->wellness == this->wellness) {
            return i.get()->generator_operator;
        }
    }

    return {-1, -1};
}

// Az X szempontjából heurisztika
// X-es lehetséges hármasok száma - O-s lehetséges hármasok száma
int Node::calculate_heuristics() {
    
    return calculate_possibilities(Node::players[0]) - calculate_possibilities(Node::players[1]);
}

// hányféleképpen lehet még lerakni 3 egymás melletti jelet
int Node::calculate_possibilities(char player) {

    int heur = 0;

    int h_diagonal_counter1 = 0;
    int h_diagonal_counter2 = 0;

    for (int i = 0; i < 3; i++) {

        if (state[i][i] == player || state[i][i] == '-') {
            h_diagonal_counter1++;
        }

        if (state[2 - i][i] == player || state[2 - i][i] == '-') {
            h_diagonal_counter2++;
        }

        int h_horizontal_counter = 0;
        int h_vertical_counter = 0;

        for (int j = 0; j < 3; j++) {
            if (state[i][j] == player || state[i][j] == '-') {
                h_horizontal_counter++;
            }

            if (state[j][i] == player || state[j][i] == '-') {
                h_vertical_counter++;
            }
        }

        heur += (h_horizontal_counter == 3 ? 1 : 0) + (h_vertical_counter == 3 ? 1 : 0);
    }
    heur += (h_diagonal_counter1 == 3 ? 1 : 0) + (h_diagonal_counter2 == 3 ? 1 : 0);

    return heur;
}

// ki a nyertes?
char Node::winner() {

    if (state[0][0] != '-' && state[0][0] == state[1][1] && state[1][1] == state[2][2]) return state[1][1];
    if (state[2][0] != '-' && state[2][0] == state[1][1] && state[1][1] == state[0][2]) return state[1][1];

    for (int i = 0; i < 3; i++) {
        if (state[i][0] != '-' && state[i][0] == state[i][1] && state[i][1] == state[i][2]) return state[i][0];
        if (state[0][i] != '-' && state[0][i] == state[1][i] && state[1][i] == state[2][i]) return state[0][i];
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state[i][j] == '-') return 'N';
        }
    }

    return 'D';
}