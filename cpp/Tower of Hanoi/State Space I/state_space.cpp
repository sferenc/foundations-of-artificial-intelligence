#include <bits/stdc++.h>

char state[3] = {'A', 'A', 'A'};

bool is_valid(char state[3]) {
    for (int i = 0; i < 3; i++) {
        // ha az egyik korong nem az A, B vagy C oszlopon van akkor nem állapot
        if (state[i] != 'A' && state[i] != 'B' && state[i] != 'C') return false;
    }

    return true;
}

bool is_goal(char state[3]) {
    for (int i = 0; i < 3; i++) {
        // ha az egyik korong nem az utolsó oszlopon van akkor nem célállapot
        if (state[i] != 'C') return false;
    }

    return true;
}

bool op_req(int n, char m, char state[3]) {

    // ha ugyanoda raknánk ahol van a korong akkor nem alkalmazható az operátor
    if  (state[n] == m) return false;

    // ha a 'melyiket' kisebb mint 0 vagy 3 vagy nagyobb akkor nem alkalmazható operátor    
    if (n < 0 || n >= 3) return false;
    // ha nem A, B vagy C oszlopra akarunk rakni akkor nem alkalmazható operátor
    if (m < 'A' || m > 'C') return false;

	for (int i = 0; i < 3; i++) {
        // nem alkalmazható az operátor, ha van kisebb korong azon az oszlopon amiről el akarunk rakni
		if (state[i] == state[n] && i < n) return false;
        // nem alkalmazható az operátor, ha van kisebb korong azon az oszlopon amire rakni akarunk
        if (state[i] == m && i < n) return false;
	}

    return true;
}

void op(int n, char m, char state[3]) {

    if (op_req(n, m, state)) {
        // a 'melyiket' korong a 'hova' oszlopra kerül
        state[n] = m;
    } else {
        std::cerr << "Invalid operation..." << std::endl;
    }
}

void print_state(char state[3]) {

    for (char c = 'A'; c <= 'C'; c++) {
        std::cout << c << ": ";
        for (int i = 0; i < 3; i++) {
            if (state[i] == c) {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0; i < 3; i++) {
        if (i) std::cout << ' ';
        std::cout << state[i];
    }

    std::cout << std::endl << std::endl;
}

int main() {

    while (print_state(state), !is_goal(state)) {
        int n;
        char m;
        std::string trash;

        std::cout << "Mit: ";
        std::cin >> n;
        getline(std::cin, trash);
        std::cout << "Hova: ";
        std::cin >> m;

        op(n, m, state);
    }

    return 0;
}
