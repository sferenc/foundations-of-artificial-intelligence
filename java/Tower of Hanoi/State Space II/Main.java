import java.util.Arrays;
import java.util.Set;
import java.util.HashSet;
import java.util.Collections;
import java.util.Scanner;

class Main {

    private static Set<Integer> state[] = new HashSet[3];

    private static boolean isValid(Set<Integer> state[]) {
        Integer counter[] = new Integer[3];

        for (int i = 0; i < 3; i++) {
            for (Integer j : state[i]) {
                // ha nem megfelelő méretű az egyik korong, akkor rossz állapot
                if (j < 0 || j > 2) return false;
                counter[j]++;
            }
        }

        for (int i = 0; i < 3; i++) {
            // Ha valamelyik korong nem fordul elő pontosan egyszer akkor rossz állapot
            if (counter[i] != 1) return false;
        }

        return true;
    }

    private static boolean isGoal(Set<Integer> state[]) {

        // ha az első két oszlopból valamelyik nem üres akkor rossz állapot
        if (!state[0].isEmpty() || !state[1].isEmpty()) return false;

        for (int i = 0; i <= 2; i++) {
            // ha a 3. oszlopon nincs meg a 0. 1. vagy 2. korong akkor rossz állapot 
            if (!state[2].contains(i)) return false;
        }

        return true;
    }

    private static boolean opReq(int from, int to, Set<Integer> state[]) {
        // ha a honnan vagy a hova kisebb mint 0 vagy nagyobb mint 2 akkor rossz állapot
        if (from < 0 || from > 2 || to < 0 || to > 2) return false;

        // ha a honnanban van korong és a legkisebb korongja kisebb mint a hova oszlop minimumja, akkor jó, egyébként rossz operátor
        return state[from].size() > 0 && (state[to].size() == 0 || Collections.min(state[from]) < Collections.min(state[to])); 
    }

    private static void op(int from, int to, Set<Integer> state[]) {
        if (opReq(from, to, state)) {
            // a korong ami átkerül
            int v = Collections.min(state[from]);
            
            // a hova-ra felkerül, a honnan-ról eltűnik
            state[from].remove(v);
            state[to].add(v);
        } else {
            System.err.println("Invalid operation");
        }
    }

    public static void main(String args[]) {
        for (int i = 0; i < 3; i++) state[i] = new HashSet<Integer>();
        state[0].addAll(Arrays.asList(0, 1, 2));

        Scanner scanner = new Scanner(System.in);

        int from, to;
        do {
            System.out.print("Honnan: ");
            from = scanner.nextInt();
            System.out.print("Hova: ");
            to = scanner.nextInt();

            op(from, to, state);

            for (int i = 0; i < 3; i++) {
                System.out.print(i + ": ");
                for (int j : state[i]) {
                    System.out.print(j + " ");
                }
                System.out.println();
            }
            System.out.println();

        } while(!isGoal(state));

        scanner.close();
    }
}