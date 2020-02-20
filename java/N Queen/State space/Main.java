import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Main {

    private final static int MAX_SIZE = 15;
    private static int N;
    private static List<Integer> state = new ArrayList<Integer>();

    private static boolean is_goal(List<Integer> state) {
        // N darab királynő le van rakva és helyes az állapot
        return state.size() == N && is_valid(state);
    }

    private static boolean is_valid(List<Integer> state) {
        for (int i = 0; i < state.size(); i++) {
            for (int j = i + 1; j < state.size(); j++) {
                // i. és j. oszlopban levő királynő azonos sorban van
                // két királynő oszlopainak távolsága abs(i - j) ugyanannyi, mint a sorok távolsága abs(state[i] - state[j])
                if (state.get(i) == state.get(j) || Math.abs(i - j) == Math.abs(state.get(i) - state.get(j))) {
                    return false;
                }
            }
        }
        // egyébként helyes állapot
        return true;
    }

    private static boolean put_req(int i, List<Integer> state) {
        if (i == -1) {
            // királynő levételnél, ha nem üres a vector akkor helyes
            return state.size() > 0;
        }
       
        for (int j = 0; j < state.size(); j++) {
            // a beszúrandó i már szerepel a listában
            if (state.get(j) == i) return false;

            // két királynő oszlopának és sorának a távolsága ugyanannyi
            // j - oszlop
            // state.size() - beszúrandó királynő indexe

            // state.get(j) - j oszlopon levő királynő sora
            // i - beszúrandó sor
            if (Math.abs(j - state.size()) == Math.abs(state.get(j) - i)) return false;
        }

        return i >= 0 && i < N && state.size() <= N;
    }

    private static void put(int i, List<Integer> state) {

        if (put_req(i, state)) {
            // ha -1, akkor levesz,      egyébként beilleszt
            if (i == -1) {
                state.remove(state.size() - 1);
            } else {
                state.add(i);
            }
        } else {
            System.err.println("Invalid operation");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter n: ");
        N = scanner.nextInt();
        N = Math.min(MAX_SIZE, N);

        while (!is_goal(state)) {
            System.out.print("Enter next value: ");
            int next_value = scanner.nextInt();

            put (next_value, state);

            for (int i = 0; i < state.size(); i++) {
                if (i > 0) System.out.print(' ');
                System.out.print(state.get(i));
            }
            System.out.println();
        }

        scanner.close();
    }

}