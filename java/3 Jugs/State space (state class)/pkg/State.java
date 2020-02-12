package pkg;

public class State {

    public State(int state[]) {
        this.state = new int[3];

        for (int i = 0; i < 3; i++) {
            this.state[i] = state[i];
        }
    }

    public boolean isValid() {
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

    public boolean isGoalState() {
        // célállapot, ha 4 liter van az utolsó kancsóban
        return state[2] == 4;
    }

    public boolean isValidOperation(int from, int to) {
        // a 'honnan' és 'hova' kancsók megfelelő indexeket jelölnek-e
        // üresbe öntünk-e
        // üresből öntünk-e
        return (from > -1 && from < 3 && to > -1 && to < 3 &&
            from != to && state[from] != 0 && state[to] != max[to]);
    }

    public void pour(int from, int to) {
        // A n. kancsó az az n-1. indexen van..
        from--;
        to--;
    
        // Operátor alkalmazási előfeltétel ellenőrzés
        if (!isValidOperation(from, to)) {
            System.err.println("The requested operation is not valid...");
            return;
        }
    
        // Amennyi át lesz öntve:
        // min ('honnan' kancsó tartalma, 'hova' kancsóban levő üres hely)
        int value = Math.min(state[from], max[to] - state[to]);
    
        // Operátor hatás
        state[from] -= value;
        state[to] += value;
    }

    public void printState() {
        System.out.print("\n{");;
        for (int i = 0; i < 3; i++) {
            if (i > 0) System.out.print(", ");
            System.out.print(state[i]);
        }
        System.out.println("}");
    }

    private int state[];
    private static int max[] = {2, 3, 5};

}