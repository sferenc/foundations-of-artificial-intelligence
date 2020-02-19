#include <bits/stdc++.h>

#define MAX_SIZE 15

int N = -1;
std::vector<int> state;

bool is_valid(std::vector<int> state) {

    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < i; j++) {
            // i. és j. oszlopban levő királynő azonos sorban van
            if (state[i] == state[j]) return false;
            // két királynő oszlopainak távolsága abs(i - j) ugyanannyi, mint a sorok távolsága abs(state[i] - state[j])
            if (abs(i - j) == abs(state[i] - state[j])) return false; 
        }
    }

    // egyébként helyes állapot
    return true;
}

bool is_goal(std::vector<int> state) {
    // N darab királynő le van rakva és helyes az állapot
    return state.size() == N && is_valid(state);
}

bool put_requirement(int i, std::vector<int> state) {
    // királynő levételnél, ha nem üres a vector akkor helyes
    if (i == -1 && state.size()) {
        return true;
    }

    // királynő lerakása (csak másolatba, az eredeti tömb nem változik)
    std::vector<int> state_cpy = state;
    state_cpy.push_back(i);

    // a beillesztett érték 0 és N - 1 között vesz fel értéket
    // a beillesztett értékkel együtt a tömb max N méretű
    // a beillesztett értékkel együtt helyes állapotba kerül a tömb
    return i >= 0 && i < N && state_cpy.size() <= N && is_valid(state_cpy);
}

void put(int i, std::vector<int>& state) {

    if (put_requirement(i, state)) {
        // ha -1, akkor levesz,      egyébként beilleszt
        i == -1 ? state.pop_back() : state.push_back(i);
    } else {
        std::cerr << "Invalid operation" << std::endl;
    }

}

int main() {

    std::cout << "Enter N: ";
    std::cin >> N;

    N = std::min(N, MAX_SIZE);

    int operation;
    // addig fut, amíg nem célállapot, és van a bemeneten mit olvasni
    while (!is_goal(state) && (std::cout << "Value to insert: ", std::cin >> operation)) {
        
        // operátor hívás
        put (operation, state);
    
        // kiírás
        std::cout << "{";
        for (int i = 0; i < state.size(); i++) {
            if (i) std::cout << ' ';
            std::cout << state[i];
        }
        std::cout << "}" << std::endl;
    }

    return 0;
}