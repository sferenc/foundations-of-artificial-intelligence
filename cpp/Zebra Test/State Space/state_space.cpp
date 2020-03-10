#include <bits/stdc++.h>

std::string state[5][5];

std::vector<std::vector<std::string>> abc = {
    {"piros", "zöld", "fehér", "sárga", "kék", "-"},
    {"brit", "dán", "svéd", "norvég", "német", "-"},
    {"kv", "tea", "tej", "sör", "víz", "-"},
    {"pallmall", "dunhill", "blend", "bluemaster", "prince", "-"},
    {"madár", "kutya", "cica", "ló", "hal", "-"}
};

bool statement_type1(std::string state[5][5], int ii, std::string val1, int jj, std::string val2) {
    for (int i = 0; i < 5; i++) {
        if (!(state[i][ii] != val1 || (state[i][jj] == val2 || state[i][jj] == "-"))) return false;
        if (!(state[i][jj] != val2 || (state[i][ii] == val1 || state[i][ii] == "-"))) return false;
    }
    return true;
}

bool statement_type2(std::string state[5][5], int ii, std::string val1, int jj, std::string val2) {
    for (int i = 1; i < 4; i++) {
        if (!(state[i][ii] != val1 || (state[i + 1][jj] == val2 || state[i - 1][jj] == val2 || state[i + 1][jj] == "-" || state[i - 1][jj] == "-"))) return false;
        if (!(state[i][jj] != val2 || (state[i + 1][ii] == val1 || state[i - 1][ii] == val1 || state[i + 1][ii] == "-" || state[i - 1][ii] == "-"))) return false;
    }
    return true;
}

bool is_valid(std::string state[5][5]) {
    std::map<std::string, int> counter;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            counter[state[i][j]]++;
            if (find(abc[j].begin(), abc[j].end(), state[i][j]) == abc[j].end()) return false;
        }
    }

    for (auto i : counter) {
        if (i.first == "-") continue;
        if (i.second > 1) return false;
    }

    // 1. A piros házban a brit lakik
    if (!statement_type1(state, 1, "brit", 0, "piros")) return false;
    // 2. A svédnek kutyája van
    if (!statement_type1(state, 1, "svéd", 4, "kutya")) return false;
    // 3. A dán teát iszik
    if (!statement_type1(state, 1, "dán", 2, "tea")) return false;
    // 4. A zöld ház a fehér ház bal oldalán van
    for (int i = 0; i < 4; i++) {
        if (!(state[i][0] != "zöld" || (state[i + 1][0] == "fehér" || state[i + 1][0] == "-"))) return false;
    }
    for (int i = 1; i < 5; i++) {
        if (!(state[i][0] != "fehér" || (state[i - 1][0] == "zöld" || state[i - 1][0] == "-"))) return false;
    }
    // 5. A zöld ház tulajdonosa kávézik
    if (!statement_type1(state, 0, "zöld", 2, "kv")) return false;
    // 6. A Pall Mall-t szívó embernek madara van
    if (!statement_type1(state, 3, "pallmall", 4, "madár")) return false;
    // 7. A sárga ház tulajdonosa Dunhill-t szívó
    if (!statement_type1(state, 0, "sárga", 3, "dunhill")) return false;
    // 8. A középen élő ember tejet iszik
    if (!(state[2][2] == "-" || state[2][2] == "tej")) return false;
    // 9. A norvég az első házban lakik
    if (!(state[0][1] == "-" || state[0][1] == "norvég")) return false;
    // 10. A macskatulajdonos a Blend-et szívó mellett lakik
    if (!statement_type2(state, 4, "cica", 3, "blend")) return false;
    // 11. A lótulajdonos a Dunhill-t szívó mellett lakik
    if (!statement_type2(state, 4, "ló", 3, "dunhill")) return false;
    // 12. Aki sörözik az BlueMaster-t szív
    if (!statement_type1(state, 2, "sör", 3, "bluemaster")) return false;
    // 13. A német Prince-t szív
    if (!statement_type1(state, 1, "német", 3, "prince")) return false;
    // 14. A norvég a kék ház mellett lakik
    if (!statement_type2(state, 0, "kék", 1, "norvég")) return false;
    // 15. A vizet ivónak a szomszédja Blend-et szív
    if (!statement_type2(state, 2, "víz", 4, "blend")) return false;

    return true;
}

bool is_goal(std::string state[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (state[i][j] == "-") return false;
        }
    }
    return true;
}

bool op_req(int who, int what, std::string value, std::string state[5][5]) {

    if (who < 0 || who >= 5 || what < 0 || what >= 5) return false;

    auto save = state[who][what];
    state[who][what] = value;
    
    bool result = is_valid(state);
    state[who][what] = save;

    return result;
}

void op(int who, int what, std::string value, std::string state[5][5]) {
    if (op_req(who, what, value, state)) {
        state[who][what]= value;
    } else {
        std::cerr << "Wrong operation..." << std::endl;
    }
}

int main() {

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            state[i][j] = "-";
        }
    }

    while (true) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                std::string _ws = std::string(10 - state[i][j].length(), ' ');
                std::cout << state[i][j] << _ws << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        if (is_goal(state)) break;

        int who, what;
        std::string value;

        if (!(std::cin >> who >> what >> value)) break;
        op(who, what, value, state);
    }

    return 0;
}