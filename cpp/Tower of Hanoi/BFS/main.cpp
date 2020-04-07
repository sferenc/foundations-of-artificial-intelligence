#include <bits/stdc++.h>

bool is_valid(char* state) {
    for (int i = 0; i < 3; i++) {
        // ha az egyik korong nem az A, B vagy C oszlopon van akkor nem állapot
        if (state[i] != 'A' && state[i] != 'B' && state[i] != 'C') return false;
    }

    return true;
}

bool is_goal(char* state) {
    for (int i = 0; i < 3; i++) {
        // ha az egyik korong nem az utolsó oszlopon van akkor nem célállapot
        if (state[i] != 'C') return false;
    }

    return true;
}

bool op_req(int n, char m, char* state) {

    // ha a 'melyiket' kisebb mint 0 vagy 3 vagy nagyobb akkor nem alkalmazható operátor    
    if (n < 0 || n >= 3) return false;
    // ha nem A, B vagy C oszlopra akarunk rakni akkor nem alkalmazható operátor
    if (m < 'A' || m > 'C') return false;

    // ha ugyanoda raknánk ahol van a korong akkor nem alkalmazható az operátor
    if  (state[n] == m) return false;

	for (int i = 0; i < 3; i++) {
        // nem alkalmazható az operátor, ha van kisebb korong azon az oszlopon amiről el akarunk rakni
		if (state[i] == state[n] && i < n) return false;
        // nem alkalmazható az operátor, ha van kisebb korong azon az oszlopon amire rakni akarunk
        if (state[i] == m && i < n) return false;
	}

    return true;
}

char* op(int n, char m, char* state) {
    char* result = new char[3];

    for (int i = 0; i < 3; i++) {
        result[i] = state[i];
    }

    if (op_req(n, m, state)) {
        // a 'melyiket' korong a 'hova' oszlopra kerül
        result[n] = m;
    } else {
        std::cerr << "Invalid operation..." << std::endl;
    }

    return result;
}

void print_state(char* state) {

    for (int i = 0; i < 3; i++) {
        if (i) std::cout << ' ';
        std::cout << state[i];
    }

    std::cout << std::endl;
}

int main() {

    {
        char* state = new char[3];
        state[0] = state[1] = state[2] = 'A';
        std::queue<std::pair<char*, int>> opened;
        std::vector<std::pair<char*, int>> closed;
        std::map<char*, bool> taken; 
        
        opened.push(std::make_pair(state, -1));

        while (opened.size()) {
            auto front = opened.front();
            closed.push_back(front);

            taken[front.first] = true;
            
            if (is_goal(closed.back().first)) {
                break;
            }

            opened.pop();

            for (int i = 0; i < 3; i++) {
                for (char c = 'A'; c != 'D'; c++) {
                    if (op_req(i, c, front.first)) {
                        char* result = op(i, c, front.first);

                        if (!taken[result]) {
                            opened.push(std::make_pair(result, closed.size() - 1));
                        }
                    }
                }
            }
        }

        if (opened.empty()) {
            std::cout << "No solution found for the problem" << std::endl;
        } else {
            std::stack<int> solution_indexes;
            solution_indexes.push(closed.size() - 1);

            while (closed[solution_indexes.top()].second != -1) {
                solution_indexes.push(closed[solution_indexes.top()].second);
            }

            while (solution_indexes.size()) {
                print_state(closed[solution_indexes.top()].first);
                solution_indexes.pop();
            }
        }
    }

    return 0;
}