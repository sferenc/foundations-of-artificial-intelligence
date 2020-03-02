#include <bits/stdc++.h>

// 3 elemből álló halmaztömb
std::set<int> state[3] = {{0, 1, 2}, {}, {}};

bool is_valid(std::set<int> state[3]) {

    bool found[3] = {false, false, false};

    for (int i = 0; i < 3; i++) {
        for (int j : state[i]) {
            // ha kisebb mint 0 vagy nagyobb mint 2 a korong száma akkor rossz állapot
            if (j < 0 || j > 2) return false;
            // ha már volt ilyen akkor rossz állapot
            if (found[j]) return false;
            // jelezzük, hogy megtaláltuk 1x
            found[j] = true;
        }
    }

    for (int i = 0; i < 3; i++) {
        // ha valamelyik nincs meg akkor rossz állapot
        if (!found[i]) return false;
    }

    return true;
}

bool is_goal(std::set<int> state[3]) {

    for (int i : {0, 1, 2}) {
        // ha nincs a halmazban valamelyik érték akkor nem cél állapot
        if (find(state[2].begin(), state[2].end(), i) == state[2].end()) return false;
    }

    return state[0].size() == 0 && state[1].size() == 0;
}

int min(std::set<int> state) {

    int minimum = INT_MAX;

    /*
    if (state.size()) {
        return *state.begin(); 
    } else {
        return INT_MAX;
    }
    */

    for (int i : state) {
        minimum = std::min(minimum, i);
    }

    return minimum;
}

bool op_req(int from, int to, std::set<int> state[3]) {
    // ha a 'honnan'-ban van elem és a 'honnan' minimumja kisebb
    // mint a 'hova' minimumja akkor alkalmazható
    return from >= 0 && from < 3 && to >= 0 && to < 3 && state[from].size() > 0 && min(state[from]) < min(state[to]);
}

void op(int from, int to, std::set<int> state[3]) {
    if (op_req(from, to, state)) {
        // a 'honnan'-ból töröljük a minimumját, a 'hova'-ba beillesztjük 
        state[to].insert(min(state[from]));
        state[from].erase(min(state[from]));
    } else {
        std::cerr << "Invalid operation..." << std::endl;
    }
}

void print_state(std::set<int> state[3]) {
    
    for (int i = 0; i < 3; i++) {
        std::cout << i << ": ";
        for (int j : state[i]) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {

    int from, to;

    while (print_state(state), !is_goal(state)) {
        std::cout << "Honnan: ";
        std::cin >> from;
        std::cout << "Hova: ";
        std::cin >> to;

        op(from, to, state);
    }
}
