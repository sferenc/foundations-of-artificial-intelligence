import java.util.Scanner;

class Main {

    private static char state[] = {'A', 'A', 'A'};

    private static boolean isValid(char state[]) {
        // Ha az egyik korong nem az A, B vagy C oszlopon van, akkor rossz állapot
        for (int i = 0; i < 3; i++) {
            if (state[i] != 'A' && state[i] != 'B' && state[i] != 'C') {
                return false;
            }
        }
        return true;
    }

    private static boolean isGoal(char state[]) {
        // Ha valamelyik korong nem a C oszlopon van, akkor nem célállapot
        for (int i = 0; i < 3; i++) {
            if (state[i] != 'C') {
                return false;
            }
        }
        return true;
    }

    private static boolean opReq(int n, char m, char state[]) {

        if (n < 0 || n > 2) return false;
        if (m < 'A' || m > 'C') return false;
        // ha ugyanoda raknánk ahol most van akkor helytelen operátor
        if (state[n] == m) return false;

        for (int i = 0; i < 3; i++) {
            // ha a cél oszlopon van kisebb korong akkor nem jó operátor
            if (state[i] == m && i < n) return false;
            // ha a jelen oszlopon van kisebb korong akkor nem jó operátor
            if (state[i] == state[n] && i < n) return false;
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