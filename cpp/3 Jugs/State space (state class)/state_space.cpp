#include <iostream>
#include <cmath>

class State {

    public:
        State(int jugs[3]) {
            for (int i = 0; i < 3; i++) {
                this->jugs[i] = jugs[i];
            }
        }
        
        bool is_valid_state() {
            int sum = 0;

            for (int i = 0; i < 3; i++) {
                sum += jugs[i];

                // Kevesebb mint 0, vagy több mint a maximum van-e benne?
                if (jugs[i] < 0 || jugs[i] > max[i]) {
                    return false;
                }
            }

            // Összesen annyi folyadék van-e, mint a kezdetben?
            return sum == max[2];
        }

        bool is_goal_state() {
            // célállapot, ha 4 liter van az utolsó kancsóban
            return jugs[2] == 4;
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
            int value = std::min(jugs[from], max[to] - jugs[to]);

            // Operátor hatás
            jugs[from] -= value;
            jugs[to] += value;
        }

        bool is_valid_operation(int from, int to) {
            // a 'honnan' és 'hova' kancsók megfelelő indexeket jelölnek-e
            // üresbe öntünk-e
            // üresből öntünk-e
            return (from < 3 && from > -1 &&
                     to < 3 && to > -1 &&
                     from != to &&
                     jugs[from] != 0 && jugs[to] != max[to]);
        }

        ~State() {

        }

        void print_state() {
            std::cout << std::endl << "{";
            for (int i = 0; i < 3; i++) {
                if (i) std::cout << ", ";
                std::cout << jugs[i];
            }
            std::cout << "}" << std::endl;
        }

    private:
        int jugs[3];
        int max[3] = {2, 3, 5};

        State(const State& state);
        State& operator= (const State& state);
        State(State&& state);
        State& operator= (State&& state);
};

int main() {

    int jugs[3] = {0, 0, 5};
    State state(jugs);

    int from, to;

    state.print_state();
    while (!state.is_goal_state()) {

        std::cout << "From: ";
        std::cin >> from;
        std::cout << "To: ";
        std::cin >> to;

        state.pour(from, to);
        state.print_state();
    }

    return 0;
}
