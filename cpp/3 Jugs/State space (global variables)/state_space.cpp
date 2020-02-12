#include <iostream>
#include <cmath>

int state[3] = {0, 0, 5};
int max[3] = {2, 3, 5};

bool is_valid() {

    int sum = 0;

    for (int i = 0; i < 3; i++) {
        sum += state[i];

        // Kevesebb mint 0, vagy több mint a maximum van-e benne?
        if (state[i] < 0 || state[i] > max[i]) {
            return false;
        }
    }

    // Összesen annyi folyadék van-e, mint a kezdetben?
    return sum == max[2];
}

bool is_goal_state() {
    // célállapot, ha 4 liter van az utolsó kancsóban
    return state[2] == 4;
}

bool is_valid_operation(int from, int to) {
    // a 'honnan' és 'hova' kancsók megfelelő indexeket jelölnek-e
    // üresbe öntünk-e
    // üresből öntünk-e
    return (from < 3 && from > -1 &&
             to < 3 && to > -1 &&
             from != to &&
             state[from] != 0 && state[to] != max[to]);
}

void pour(int from, int to) {
    // A n. kancsó az az n-1. indexen van..
    from--;
    to--;

    // Operátor alkalmazási előfeltétel ellenőrzés
    if (!is_valid_operation(from, to)) {
        std::cerr << "The requested operation is not valid..." << std::endl;
        return;
    }

    // Amennyi át lesz öntve:
    // min ('honnan' kancsó tartalma, 'hova' kancsóban levő üres hely)
    int value = std::min(state[from], max[to] - state[to]);

    // Operátor hatás
    state[from] -= value;
    state[to] += value;
}

void print_state() {
    std::cout << std::endl << "{";
    for (int i = 0; i < 3; i++) {
        if (i) std::cout << ", ";
        std::cout << state[i];
    }
    std::cout << "}" << std::endl;
}

int main() {
    
    int from, to;
        
    while (!is_goal_state()) {

        std::cout << "From: ";
        std::cin >> from;
        std::cout << "To: ";
        std::cin >> to;

        pour(from, to);
        print_state();
    }

    return 0;
}
