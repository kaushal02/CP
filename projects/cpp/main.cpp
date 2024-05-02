#include <functional>
#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

int twice(int x) { return 2 * x; }
int fastInc(int x) { return x + 1; }
int slowInc(int x) {
    cout << "(sleep 2s) " << flush;
    sleep(2);
    return x + 1;
}

class LazyArray {

    vector<int> nums;
    vector<function<int(int)>> functions;
    vector<int> applyFrom;

  public:
    LazyArray(vector<int>& nums_): nums(nums_), applyFrom(nums_.size(), 0) {}

    LazyArray(vector<int>& nums_, vector<function<int(int)>>& functions_, vector<int>& applyFrom_):
        nums(nums_), functions(functions_), applyFrom(applyFrom_) {}

    LazyArray map(function<int(int)> f) {
        auto newFunctions(functions);
        newFunctions.push_back(f);
        return LazyArray(nums, newFunctions, applyFrom);
    }

    int indexOf(int val) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = applyFrom[i]; j < functions.size(); j++) {
                nums[i] = functions[j](nums[i]);
            }
            applyFrom[i] = functions.size();
            if (nums[i] == val) {
                return i;
            }
        }
        return -1;
    }
};


int main() {
    vector<int> nums({10, 20, 30, 40, 50});
    LazyArray A(nums);

    auto B = A.map(twice);
    cout << "40 is at index=" << B.indexOf(40) << " in A.twice\n";

    auto D = B.map(fastInc).map(fastInc);
    cout << "33 is at index=" << D.indexOf(33) << " in A.twice.fastInc.fastInc\n";
    cout << "22 is at index=" << D.indexOf(22) << " in A.twice.fastInc.fastInc\n";

    auto C = B.map(slowInc).map(slowInc);
    cout << "42 is at index=" << C.indexOf(42) << " in A.twice.slowInc.slowInc\n";
    cout << "22 is at index=" << C.indexOf(22) << " in A.twice.slowInc.slowInc\n";

    return 0;
}

/*

$ g++ -std=c++17 main.cpp && ./a.out

40 is at index=1 in A.twice
33 is at index=-1 in A.twice.fastInc.fastInc
22 is at index=0 in A.twice.fastInc.fastInc
42 is at index=(sleep 2s) (sleep 2s) (sleep 2s) (sleep 2s) 1 in A.twice.slowInc.slowInc
22 is at index=0 in A.twice.slowInc.slowInc

*/