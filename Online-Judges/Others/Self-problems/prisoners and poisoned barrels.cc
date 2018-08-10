/*
You are given B barrels of wine, exactly one of which is poisoned. Upon drinking
the poisoned wine, one dies within 24 hours. You have N slaves whom you are
willing to sacrifice in order to determine which barrel contains the poisoned
wine. How do you achieve this in D days?

Approach: http://qr.ae/TUI39r
PS: https://www.geeksforgeeks.org/puzzle-5-finding-the-poisoned-wine

For an easier understanding of the approach, read here: http://qr.ae/TUI391

Sample Input 1:
5 240 2

Sample Input 2:
4 1000 5

*/

#include <iostream>
#include <vector>
using namespace std;

void rmv(vector<int> &, const vector<int> &); // a-=b
void print(const vector<int> &); // [a1,a2,..]
int power(int, int); // a**n

class game {
public:
    int days;
    vector<int> barrels;
    vector<int> prisoners;
    game(int n, int d, int b) {
        days = d;
        setPoison(b);
        for(int barrel=1; barrel<=b; barrel++) barrels.push_back(barrel);
        for(int prisoner=1; prisoner<=n; prisoner++) prisoners.push_back(prisoner);
    }
    void inventory() {
        cout << "Prisoners: "; print(prisoners); cout << "\n";
        cout << "Barrels: "; print(barrels); cout << "\n\n";
    }
    void batchDrink(vector<int> prisoners, vector<int> barrels) {
        print(prisoners); cout << "drank ";
        print(barrels); cout << "\n\n";
    }
    void poisonOnce() {
        int n = prisoners.size(), m = barrels.size(), bno = 0;
        vector<int> canbarrels, deadprisoners;
        for(int mask=0; mask < (1<<n); mask++) {
            vector<int> testbarrels;
            int numtestbarrels = power(days, n-(int)__builtin_popcount(mask));
            int found=0; while(numtestbarrels--) if(bno < m) {
                testbarrels.push_back(barrels[bno++]);
                if(isPoison(testbarrels.back())) found=1;
            }
            vector<int> testprisoners;
            for(int pno=0; pno<n; pno++) if(mask>>pno&1) {
                testprisoners.push_back(prisoners[pno]);
            }
            if(found) {
                canbarrels = testbarrels;
                deadprisoners = testprisoners;
            }
            if(testbarrels.size()*testprisoners.size()) {
                if(found) cout << "DEAD ";
                batchDrink(testprisoners, testbarrels);
            }
        }
        rmv(prisoners, deadprisoners);
        barrels = canbarrels;
    }
    void findPoison() {
        do {
            cout << days << "d remaining...\n";
            inventory();
            poisonOnce();
            cout << "\n\n\n";
        } while(--days);
        cout << "Judgement Day...\n";
        cout << "Poison found: " << barrels.back() << "\n";
    }

private:
    int poison;
    void setPoison(int b) {
        srand(time(NULL));
        poison = rand()%b + 1;
    }
    bool isPoison(int barrel) {
        return barrel == poison;
    }
};

int main() {
    // Driver program to test the above code
    cout << "\nEnter the number of prisoners: ";
    int n; cin >> n;
    cout << "\nEnter the number of barrels: ";
    int b; cin >> b;
    cout << "\nEnter the number of days: ";
    int d; cin >> d;

    game(n,d,b).findPoison();
    return 0;
}

void rmv(vector<int> &a, const vector<int> &b) {
    vector<int> c;
    int i=0, j=0, m=a.size(), n=b.size();
    while(i<m and j<n) {
        if(a[i] < b[j]) c.push_back(a[i++]);
        else i++, j++;
    }
    while(i<m) c.push_back(a[i++]);
    a = c;
}
void print(const vector<int> &a) {
    int n = a.size();
    cout << "[";
    for(int i=0; i<n-1; i++) cout << a[i] << ", ";
    if(!a.empty()) cout << a.back();
    cout << "] ";
}
int power(int a, int n) {
    if(n < 1) return 1;
    int x = power(a, n/2);
    return x*x*(n%2 ? a:1);
}