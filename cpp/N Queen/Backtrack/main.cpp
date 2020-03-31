#include <bits/stdc++.h>

#define MAX_SIZE 8

std::vector<int> state;

bool is_valid(std::vector<int> state) {

    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (state[i] == state[j]) return false;
            if (abs(i - j) == abs(state[i] - state[j])) return false; 
        }
    }

    return true;
}

bool is_goal(std::vector<int> state) {
    return state.size() == MAX_SIZE && is_valid(state);
}

bool put_requirement(int i, std::vector<int> state) {

    std::vector<int> state_cpy = state;
    state_cpy.push_back(i);

    return i >= 0 && i < MAX_SIZE && state_cpy.size() <= MAX_SIZE && is_valid(state_cpy);
}

void put(int i, std::vector<int>& state) {

    if (put_requirement(i, state)) {
        state.push_back(i);
    } else {
        std::cerr << "Invalid operation" << std::endl;
    }

}

int main() {

    state.push_back(0);

    while (state.size() && !is_goal(state)) {
        while (state.size() && state.back() == MAX_SIZE) {
            state.pop_back();
            state.back()++;
        }

        if (state.size() == 0) {
            std::cerr << "Couldn't find solution..." << std::endl;
            break;       
        }


        if (!is_valid(state)) {
            state.back()++;
        } else if (state.size() != MAX_SIZE) {
            state.push_back(0); 
        }
    }

    for (int i = 0; i < state.size(); i++) {
        std::cout << state[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}