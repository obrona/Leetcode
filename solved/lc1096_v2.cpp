#include <bits/stdc++.h>
using namespace std;

// parse into AST.
// then eval.
// tricky thing is to parse.

struct op {
    virtual unordered_set<string> eval() = 0;
    virtual ~op() {}
};

struct union_op: op {
    vector<unique_ptr<op>> children;

    union_op(vector<unique_ptr<op>>&& arr): children(std::move(arr)) {}

    unordered_set<string> eval() {
        unordered_set<string> out;
        for (auto& p : children) {
            auto s = p->eval();
            out.insert(s.begin(), s.end());
        }
        return out;
    }
};

struct mult_op: op {
    array<unique_ptr<op>, 2> children;

    mult_op(unique_ptr<op>&& op1, unique_ptr<op>&& op2) {
        children = {std::move(op1), std::move(op2)};
    }

    unordered_set<string> eval() {
        unordered_set<string> out;
        auto s1 = children[0]->eval();
        auto s2 = children[1]->eval();
        for (const auto& l : s1) {
            for (const auto& r : s2) {
                out.insert(l + r);
            }
        }
        return out;
    }
};

struct single_word_op: op {
    string s;

    single_word_op(const string& s): s(s) {}

    unordered_set<string> eval() {
        return {s};
    }
};

pair<int, unique_ptr<op>> parse(const string& expr, int start) {
    // stores the op to concat.
    vector<unique_ptr<op>> to_union;
    // the last op may be used in a mult_op so keep it here first.
    unique_ptr<op> prev;
    int p = start;

    while (p < expr.size()) {
        if (expr[p] == '}') {
            if (prev) to_union.emplace_back(std::move(prev));
            return {p + 1, make_unique<union_op>(std::move(to_union))};
        }

        if (expr[p] == ',') {
            to_union.emplace_back(std::move(prev));
            p++;
            continue;
        } else if (expr[p] == ' ') {
            p++;
            continue;
        }

        unique_ptr<op> res;
        if (expr[p] == '{') {
            auto [p_next, op] = parse(expr, p + 1);
            res = std::move(op);
            p = p_next;
        } else if (islower(expr[p])) {
            int e = p + 1;
            while (e < expr.size() && islower(expr[e])) e++;
            string word = expr.substr(p, e - p);
            res = make_unique<single_word_op>(word);
            p = e;
        }

        if (prev) {
            prev = make_unique<mult_op>(std::move(prev), std::move(res));
        } else {
            prev = move(res);
        }
    }

    if (to_union.size() == 0) {
        return {p, std::move(prev)};
    } else {
        if (prev) {
            to_union.emplace_back(move(prev));
        }
        return {p, make_unique<union_op>(move(to_union))};
    }
}

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        auto [p, op] = parse(expression, 0);
        auto s = op->eval();
        vector<string> out(s.begin(), s.end());
        sort(out.begin(), out.end());
        return out;
    }
};

int main() {
    Solution sol;
    string expr = "{a,b}{c,{d,e}}";
    vector<string> out = sol.braceExpansionII(expr);

    for (auto x : out) cout << x << endl;
};

