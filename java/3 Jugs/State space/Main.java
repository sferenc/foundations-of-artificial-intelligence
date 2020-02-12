import java.util.Scanner;

class Main {

    private static int state[] = {0, 0, 5};
    private static int max[] = {2, 3, 5};

    static boolean isValid() {

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

    static boolean isGoalState() {
        // célállapot, ha 4 liter van az utolsó kancsóban
        return state[2] == 4;
    }

    static boolean isValidOperation(int from, int to) {
        // a 'honnan' és 'hova' kancsók megfelelő indexeket jelölnek-e
        // üresbe öntünk-e
        // üresből öntünk-e
        return (from > -1 && from < 3 && to > -1 && to < 3 &&
            from != to && state[from] != 0 && state[to] != max[to]);
    }

    static void pour(int from, int to) {
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

    static void printState() {
        System.out.print("\n{");;
        for (int i = 0; i < 3; i++) {
            if (i > 0) System.out.print(", ");
            System.out.print(state[i]);
        }
        System.out.println("}");
    }

    public static void main(String args[]) {

        Scanner scanner = new Scanner(System.in);

        int from, to;

        printState();
        while (!isGoalState()) {
            System.out.print("From: ");
            from = scanner.nextInt();
            System.out.print("To: ");
            to = scanner.nextInt();

            pour(from, to);
            printState();
        }

        scanner.close();
    }
}