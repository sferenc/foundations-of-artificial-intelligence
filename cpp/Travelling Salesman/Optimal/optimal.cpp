#include <bits/stdc++.h>

int cost[5][5] = {
    {0, 7, 6, 10, 13},
    {7, 0, 7, 10, 10},
    {6, 7, 0, 5, 9},
    {10, 10, 5, 0, 6},
    {13, 10, 9, 6, 0}
};

using namespace std;

vector<pair<pair<int, string>, int>> closed;

bool is_valid(string state) {
    map<char, int> counter;

    for (char c : state) {
        if (counter['A'] == 2 && c != '*') return false;
        if ((c < 'A' || c > 'E') && c != '*') return false;
        counter[c]++;
    }

    for (char c = 'B'; c <= 'E'; c++) {
        if (counter[c] > 1) return false;
    }

    return counter['A'] == 2;
}

bool is_goal(string state) {
    
    for (char c : state) {
        if (c == '*') return false;
    }
    return true;
}

bool op_req(char from, char to, string state) {
    string abc = "ABCDE";
    return (state.find(from) != string::npos && state.find(to) == string::npos && abc.find(to) != string::npos);
}

string op(char from, char to, string state) {
    if (op_req(from, to, state)) {
        int pos = state.find(from);

        for (int i = 5; i > pos + 1; i--) {
            state[i] = state[i - 1];
        }

        state[pos + 1] = to;
    } else {
        cerr << "Invalid operation" << endl;
    }

    return state;
}

void print_path(int i) {

    if (closed[i].second != -1) {
        print_path(closed[i].second);
    }

    cout << closed[i].first.second << " " << -1 * closed[i].first.first << endl;

}

int main() {
    //                       cost, state,  parent
    priority_queue<pair<pair<int, string>, int>> pq;
    pq.push({{0, "AA****"}, -1});

    while(!pq.empty()) {
    
        auto top = pq.top();
        closed.push_back(top);
        if (is_goal(top.first.second)) {
            break;
        }

        pq.pop();

        for (char from = 'A'; from <= 'E'; from++) {
            for (char to = 'A'; to <= 'E'; to++) {
                if (op_req(from, to, top.first.second)) {
                    string result = op(from, to, top.first.second);
                    int new_cost = -top.first.first
                        - cost[from - 'A'][top.first.second[top.first.second.find(from) + 1] - 'A']
                        + cost[from - 'A'][to - 'A']
                        + cost[to - 'A'][top.first.second[top.first.second.find(from) + 1] - 'A'];

                    pq.push({{-new_cost, result}, closed.size() - 1});
                }
            }
        }
    }
    print_path(closed.size() - 1);
}