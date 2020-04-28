#include <bits/stdc++.h>
#include "Node.h"

using namespace std;

bool goal_state(char table[3][3]) {
    bool winner_exists = false;

    winner_exists = winner_exists || (table[0][0] != '-' && table[0][0] == table[1][1] && table[1][1] == table[2][2]);
    winner_exists = winner_exists || (table[2][0] != '-' && table[2][0] == table[1][1] && table[1][1] == table[0][2]);

    for (int i = 0; i < 3 && !winner_exists; i++) {
        winner_exists = winner_exists || (table[i][0] != '-' && table[i][0] == table[i][1] && table[i][1] == table[i][2]);
        winner_exists = winner_exists || (table[0][i] != '-' && table[0][i] == table[1][i] && table[1][i] == table[2][i]);
    }

    if (winner_exists) return true;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (table[i][j] == '-') return false;
        }
    }

    return true;
}

bool op_req(int row, int col, char table[3][3]) {
    return !(row < 0 || row > 2 || col < 0 || col > 2 || table[row][col] != '-');
}

void print(char table[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << table[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    char table[3][3];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            table[i][j] = '-';
        }
    }

    while (!goal_state(table)) {
        
        int row, col;
        cout << "Enter row and column: " << endl;
        cin >> row >> col;

        if (op_req(row, col, table)) {
            table[row][col] = 'O';
        } else {
            continue;
        }
        print(table);
        if (goal_state(table)) break;

        Node n(table, 0, make_pair(-1, -1));
        table[n.get_best_operator().first][n.get_best_operator().second] = 'X';
        print(table);
    }
}