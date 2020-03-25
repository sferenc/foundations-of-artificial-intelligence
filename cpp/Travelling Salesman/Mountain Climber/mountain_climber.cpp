#include <bits/stdc++.h>

std::string state = "AA****";
int current_cost = 0;

int cost[5][5] = {
    {0, 7, 6, 10, 13},
    {7, 0, 7, 10, 10},
    {6, 7, 0, 5, 9},
    {10, 10, 5, 0, 6},
    {13, 10, 9, 6, 0}
};


bool is_valid(std::string state) {
    std::map<char, int> counter;

    for (char c : state) {
        if (counter['A'] == 2 && c != '*') return false;
        if ((c < 'A' || c > 'E') && c != '*') return false;
        counter[c]++;
    }

    for (char c = 'B'; c <= 'E'; c++) {
        if (counter[c] > 1) return false;
    }

    return counter['A'] == 2;
}

bool is_goal(std::string state) {
    
    for (char c : state) {
        if (c == '*') return false;
    }
    return true;
}

bool op_req(char from, char to, std::string state) {
    std::string abc = "ABCDE";
    return (state.find(from) != std::string::npos && state.find(to) == std::string::npos && abc.find(to) != std::string::npos);
}

void op(char from, char to, std::string& state) {
    if (op_req(from, to, state)) {
        int pos = state.find(from);

        for (int i = 5; i > pos + 1; i--) {
            state[i] = state[i - 1];
        }

        state[pos + 1] = to;
    } else {
        std::cerr << "Invalid operation" << std::endl;
    }
}

int main() {
   
    do {
        char from_best, to_best;
        int best_cost = INT_MAX;

        for (char from = 'A'; from <= 'E'; from++) {
            for (char to = 'A'; to <= 'E'; to++) {
                if (op_req(from, to, state)) {
                    int new_cost = current_cost 
                        - cost[from - 'A'][state[state.find(from) + 1] - 'A']
                        + cost[from - 'A'][to - 'A']
                        + cost[to - 'A'][state[state.find(from) + 1] - 'A'];
                    if (new_cost < best_cost) {
                        best_cost = new_cost;
                        from_best = from;
                        to_best = to;
                    }
                }
            }
        }

        op(from_best, to_best, state);
        current_cost = best_cost;
        std::cout << state << '\t' << "Jelenlegi költség: " << current_cost << std::endl;
    } while (!is_goal(state));
    std::cout << state << std::endl;
}