import java.util.Scanner;

class Main {

    private static char state[] = {'A', 'A', 'A'};

    private static boolean isValid(char state[]) {
        for (int i = 0; i < 3; i++) {
            if (state[i] != 'A' && state[i] != 'B' && state[i] != 'C') {
                return false;
            }
        }
        return true;
    }

    private static boolean isGoal(char state[]) {
        for (int i = 0; i < 3; i++) {
            if (state[i] != 'C') {
                return false;
            }
        }
        return true;
    }

    private static boolean opReq(int n, char m, char state[]) {

        if (n < 0 || n > 3) return false;
        if (m < 'A' || m > 'C') return false;
        if (state[n] == m) return false;

        for (int i = 0; i < 3; i++) {
            if (state[i] == m && i < n)
                return false;
            if (state[i] == state[n] && i < n)
                return false;
        }

        return true;
    }

    private static void op(int n, char m, char state[]) {
        if (opReq(n, m, state)) {
            state[n] = m;
        } else {
            System.err.println("Invalid operation...");
        }
    }

    public static void main(String[] args) {
        int n;
        char m;

        Scanner scanner = new Scanner(System.in);

        do {

            System.out.print("Mit: ");
            n = scanner.nextInt();

            System.out.print("Hova: ");
            m = scanner.next().charAt(0);

            op(n, m, state);

            for (int i = 0; i < 3; i++) {
                if (i > 0) System.out.print(' ');
                System.out.print(state[i]);
            }
            System.out.println("\n");

        } while (!isGoal(state));

        scanner.close();
    }
}