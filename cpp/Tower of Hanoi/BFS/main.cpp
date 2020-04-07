#include <bits/stdc++.h>

bool is_valid(std::vector<char> state) {
    for (int i = 0; i < 3; i++) {
        // ha az egyik korong nem az A, B vagy C oszlopon van akkor nem állapot
        if (state[i] != 'A' && state[i] != 'B' && state[i] != 'C') return false;
    }

    return true;
}

bool is_goal(std::vector<char> state) {
    for (int i = 0; i < 3; i++) {
        // ha az egyik korong nem az utolsó oszlopon van akkor nem célállapot
        if (state[i] != 'C') return false;
    }

    return true;
}

bool op_req(int n, char m, std::vector<char> state) {

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

std::vector<char> op(int n, char m, std::vector<char> state) {
    std::vector<char> result(3);

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

void print_state(std::vector<char> state) {

    for (int i = 0; i < 3; i++) {
        if (i) std::cout << ' ';
        std::cout << state[i];
    }

    std::cout << std::endl;
}

int main() {

    {
        std::vector<char> state(3);
        state[0] = state[1] = state[2] = 'A';
        std::queue<std::pair<std::vector<char>, int>> opened;
        std::vector<std::pair<std::vector<char>, int>> closed;
        std::map<std::vector<char>, bool> taken; 
        
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
                        std::vector<char> result = op(i, c, front.first);

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