package pkg;

import java.util.Scanner;

import pkg.State;

class Main {

    public static void main(String args[]) {
        int startState[] = {0, 0, 5};
        State state = new State(startState); 

        Scanner scanner = new Scanner(System.in);

        int from, to;

        state.printState();
        while (!state.isGoalState()) {
            System.out.print("From: ");
            from = scanner.nextInt();
            System.out.print("To: ");
            to = scanner.nextInt();

            state.pour(from, to);
            state.printState();
        }

        scanner.close();
    }

}