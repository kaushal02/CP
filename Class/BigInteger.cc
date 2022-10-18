#include <algorithm>
#include <deque>

class BigInteger {
    // this += add
    void sum(BigInteger& add) {
        BigInteger ans;
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

    // this * d where d in [0,9]
    BigInteger multiplyHelper(int d) {
        BigInteger ans;
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
    BigInteger() {}
    BigInteger(int n) {
        if (!n) {
            digits.push_back(0);
            return;
        }
        while (n) {
            digits.push_back(n % 10);
            n /= 10;
        }
    }
    BigInteger(string value) {
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
        if (ans.empty()) {
            ans = "0";
        }
        return ans;
    }

    // this * n
    BigInteger multiply(int n) {
        if (value() == "0") {
            return BigInteger(0);
        }
        int zero_count(0);
        BigInteger ans;
        while (n) {
            BigInteger temp = multiplyHelper(n % 10);
            for (int i = 0; i < zero_count; i++) {
                temp.digits.push_front(0);
            }
            ans.sum(temp);
            zero_count++;
            n /= 10;
        }
        return ans;
    }
    bool operator==(BigInteger const& second) {
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
    bool operator<=(BigInteger const& second) {
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
        assert(BigInteger("0") == BigInteger(0));
        assert(BigInteger("1") == BigInteger(1));
        assert(BigInteger("12345") == BigInteger(12345));

        assert(BigInteger().value() == "");
        assert(BigInteger(0).value() == "0");
        assert(BigInteger(2).value() == "2");
        assert(BigInteger(10).value() == "10");
        assert(BigInteger(1234).value() == "1234");

        assert(BigInteger(0).multiply(2) == BigInteger(0));
        assert(BigInteger(0).multiply(23) == BigInteger(0));
        assert(BigInteger(1).multiply(2) == BigInteger(2));
        assert(BigInteger(1).multiply(23) == BigInteger(23));
        assert(BigInteger(2).multiply(2) == BigInteger(4));
        assert(BigInteger(2).multiply(23) == BigInteger(46));
        assert(BigInteger(23).multiply(23) == BigInteger(529));

        assert(BigInteger(0) <= BigInteger(0));
        assert(BigInteger(0) <= BigInteger(1));
        assert(BigInteger(0) <= BigInteger(1234));
        assert(!(BigInteger(2) <= BigInteger(0)));
        assert(BigInteger(2) <= BigInteger(2));
        assert(BigInteger(2) <= BigInteger(1234));
        assert(!(BigInteger(1234) <= BigInteger(123)));
        assert(BigInteger(1234) <= BigInteger(1234));
        assert(BigInteger(1234) <= BigInteger(2134));
        assert(BigInteger(1234) <= BigInteger(12345));
        assert(BigInteger(1234) <= BigInteger(54321));
    }
};
