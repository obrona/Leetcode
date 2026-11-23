#include <bits/stdc++.h>
using namespace std;

// prefix multiplication.
// to handle 0 we store 1 instead of 0 and take prefix count of 0.
// have to store as uint64_t
// have to do division under modulo which means have to find modulo inverse

class ProductOfNumbers {
public:
    uint64_t P = 4294967291;
    vector<uint64_t> mults;
    vector<int> zero_cnts;

    inline uint64_t mulmod(uint64_t a, uint64_t b) {
        return (a * b) % P;
    }

    uint64_t powmod(uint64_t base, uint64_t exp) {
        uint64_t result = 1;
        base %= P;
        while (exp) {
            if (exp & 1) result = mulmod(result, base);
            base = mulmod(base, base);
            exp >>= 1;
        }
        return result;
    }

    uint64_t invmod(uint64_t b) {
        return powmod(b, P - 2);   // b must not be 0 mod P
    }



    ProductOfNumbers() {
        
    }
    
    void add(int num) {
        if (mults.size() == 0) {
            if (num == 0) {
                mults.push_back(1);
                zero_cnts.push_back(1);
            } else {
                mults.push_back(num);
                zero_cnts.push_back(0);
            }
        } else {
            if (num == 0) {
                mults.push_back(mults.back());
                zero_cnts.push_back(zero_cnts.back() + 1);
            } else {
                mults.push_back(mulmod(mults.back(), num));
                zero_cnts.push_back(zero_cnts.back());
            }
        }
    }
    
    int getProduct(int k) {
        if (k == mults.size()) {
            if (zero_cnts.back() > 0) return 0;
            return (int) mults.back();
        }

        int l = mults.size() - 1 - k;
        if (zero_cnts.back() - zero_cnts[l] > 0) return 0;
        return (int) mulmod(mults.back(), invmod(mults[l]));
    }
};

int main() {
    ProductOfNumbers sol;

    sol.add(3);
    sol.add(0);
    sol.add(2);
    sol.add(5);
    sol.add(4);

    cout << sol.getProduct(2) << endl;
}
