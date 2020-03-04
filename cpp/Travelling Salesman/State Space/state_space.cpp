#include <bits/stdc++.h>

std::string state = "AA***";

bool is_valid(std::string state) {
    std::map<char, int> counter;

    for (char c : state) {
        if (counter['A'] == 2 && c != '*') return false;
        if ((c < 'A' || c > 'D') && c != '*') return false;
        counter[c]++;
    }

    for (char c = 'B'; c <= 'D'; c++) {
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
    std::string abc = "ABCD";
    return (state.find(from) != std::string::npos && state.find(to) == std::string::npos && abc.find(to) != std::string::npos);
}

void op(char from, char to, std::string& state) {
    if (op_req(from, to, state)) {
        int pos = state.find(from);

        for (int i = 4; i > pos + 1; i--) {
            state[i] = state[i - 1];
        }

        state[pos + 1] = to;
    } else {
        std::cerr << "Invalid operation" << std::endl;
    }
}

int main() {
    char from, to;
    
    do {
        std::cout << "Honnan: ";
        std::cin >> from;
        std::cout << "Hova: ";
        std::cin >> to;

        op(from, to, state);
        std::cout << state << std::endl << std::endl;
    } while (!is_goal(state));
    std::cout << state << std::endl;
}