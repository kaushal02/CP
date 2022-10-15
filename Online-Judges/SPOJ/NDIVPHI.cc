#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <algorithm>

using namespace std;

/*
n/phi(n) = prod{p/(p-1)} for all p <= n
Return smallest x = p1.p2...pk such that x <= n

2*3 <= 7

*/

class number {
    void sum(number& add) {
        number ans;
        int n = digits.size(), m = add.digits.size();
        int i = 0, carry = 0;
        while (i < n and i < m) {
            carry += digits[i] + add.digits[i];
            ans.digits.push_back(carry % 10);
            carry /= 10;
            i++;
        }
        while (i < n) {
            carry += digits[i];
            ans.digits.push_back(carry % 10);
            carry /= 10;
            i++;
        }
        while (i < m) {
            carry += add.digits[i];
            ans.digits.push_back(carry % 10);
            carry /= 10;
            i++;
        }
        while (carry) {
            ans.digits.push_back(carry % 10);
            carry /= 10;
        }
        digits = ans.digits;
    }
    number product(int d) {
        number ans;
        if (!d) {
            ans.digits.push_back(0);
            return ans;
        }
        int carry = 0, i = 0;
        while (i < digits.size()) {
            carry += digits[i] * d;
            ans.digits.push_back(carry % 10);
            carry /= 10;
            i++;
        }
        while (carry) {
            ans.digits.push_back(carry % 10);
            carry /= 10;
        }
        return ans;
    }

public:
    deque <int> digits;
    number() {}
    number(int n) {
        if (!n) {
            digits.push_back(0);
            return;
        }
        while (n) {
            digits.push_back(n % 10);
            n /= 10;
        }
    }
    number(string value) {
        reverse(value.begin(), value.end());
        for (int d : value) {
            digits.push_back(d - '0');
        }
    }
    string value() {
        string ans = "";
        for (int i = digits.size(); i--; ) {
            ans += (char) (digits[i] + '0');
        }
        return ans;
    }

    number multiply(int n) {
        if (digits.empty() or digits == deque<int>(1,0)) {
            return number(0);
        }
        int zero_count(0);
        number ans;
        while (n) {
            number temp = product(n % 10);
            for (int i = 0; i < zero_count; i++) {
                temp.digits.push_front(0);
            }
            ans.sum(temp);
            zero_count++;
            n /= 10;
        }
        return ans;
    }
    bool operator==(number const& second) {
        int n = digits.size();
        int m = second.digits.size();
        if (n != m) {
            return false;
        }
        for (int i = n; i--; ) {
            if (digits[i] != second.digits[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator<=(number const& second) {
        // 135 : {5,3,1}
        // 238 : {8,3,2}
        int n = digits.size();
        int m = second.digits.size();
        if (n != m) {
            return n < m;
        }
        for (int i = n; i--; ) {
            if (digits[i] != second.digits[i]) {
                return digits[i] < second.digits[i];
            }
        }
        return true;
    }
    static void unittests() {
        assert(number("0") == number(0));
        assert(number("1") == number(1));
        assert(number("12345") == number(12345));

        assert(number().value() == "");
        assert(number(0).value() == "0");
        assert(number(2).value() == "2");
        assert(number(10).value() == "10");
        assert(number(1234).value() == "1234");

        assert(number(0).multiply(2) == number(0));
        assert(number(0).multiply(23) == number(0));
        assert(number(1).multiply(2) == number(2));
        assert(number(1).multiply(23) == number(23));
        assert(number(2).multiply(2) == number(4));
        assert(number(2).multiply(23) == number(46));
        assert(number(23).multiply(23) == number(529));

        assert(number(0) <= number(0));
        assert(number(0) <= number(1));
        assert(number(0) <= number(1234));
        assert(!(number(2) <= number(0)));
        assert(number(2) <= number(2));
        assert(number(2) <= number(1234));
        assert(!(number(1234) <= number(123)));
        assert(number(1234) <= number(1234));
        assert(number(1234) <= number(2134));
        assert(number(1234) <= number(12345));
        assert(number(1234) <= number(54321));
    }
};

class Prime {
    int N;
    vector <int> value;
    vector <bool> isPrime;
public:
    Prime(int n) {
        N = n;
        isPrime.resize(n, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) {
                value.push_back(i);
                for (int j = 2 * i; j < n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }
    bool check(int n) {
        return isPrime[n];
    }
    vector <int> values() {
        return value;
    }
    void unittests() {
        assert(isPrime[2]);
        assert(isPrime[3]);
        assert(isPrime[13]);
        assert(value[0] == 2);
        assert(value[3] == 7);
    }
};

string solve(Prime& prime, string s) {
    number n(s);
    number ans(1);
    for (int p : prime.values()) {
        number new_ans = ans.multiply(p);
        if (new_ans <= n) {
            ans = new_ans;
        } else {
            break;
        }
    }
    return ans.value();
}

void unittests(Prime& prime) {
    prime.unittests();
    number::unittests();
    assert(solve(prime, "1") == "1");
    assert(solve(prime, "2") == "2");
    assert(solve(prime, "3") == "2");
    assert(solve(prime, "5") == "2");
    assert(solve(prime, "6") == "6");
    assert(solve(prime, "29") == "6");
    assert(solve(prime, "30") == "30");
    assert(solve(prime, "209") == "30");
    assert(solve(prime, "210") == "210");
}

int main() {
    // your code goes here
    Prime prime(150);
    unittests(prime);
    int cases = 20;
    while (cases--) {
        string s; cin >> s;
        cout << solve(prime, s) << endl;
    }
    return 0;
}
