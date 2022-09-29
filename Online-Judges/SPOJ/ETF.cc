#include <iostream>
#include <vector>
using namespace std;
const int N = 1E6 + 6;
vector <int> prime_factors[N];
int totient[N];
void pre() {
    for (int i = 2; i < N; i++) {
        if (prime_factors[i].empty()) {
            prime_factors[i].push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                prime_factors[j].push_back(i);
            }
        }
    }
    totient[1] = 1;
    for (int i = 2; i < N; i++) {
        totient[i] = i;
        for (int factor : prime_factors[i]) {
            totient[i] /= factor;
            totient[i] *= factor - 1;
        }
    }
}

int main() {
    // your code goes here
    pre();
    int cases;
    cin >> cases;
    while (cases--) {
        int n; cin >> n;
        cout << totient[n] << '\n';
    }
    return 0;
}