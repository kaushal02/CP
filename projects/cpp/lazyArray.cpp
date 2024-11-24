#include <functional>
#include <iostream>
#include <unistd.h>
#include <vector>

template <typename T>
class LazyArray {
    typedef std::vector<T> nums_t;
    typedef std::vector<int> applyFrom_t;
    typedef std::function<T(T)> function_t;
    typedef std::vector<function_t> functions_t;

  public:
    LazyArray(nums_t& nums): nums_(nums), applyFrom_(nums.size(), 0) {}

    LazyArray(nums_t& nums, functions_t& functions, applyFrom_t& applyFrom):
        nums_(nums), functions_(functions), applyFrom_(applyFrom) {}

    LazyArray map(function_t f) {
        auto newFunctions(functions_);
        newFunctions.push_back(f);
        return LazyArray(nums_, newFunctions, applyFrom_);
    }

    int indexOf(T val) {
        for (int i = 0; i < nums_.size(); i++) {
            for (int j = applyFrom_[i]; j < functions_.size(); j++) {
                nums_[i] = functions_[j](nums_[i]);
            }
            applyFrom_[i] = functions_.size();
            if (nums_[i] == val) {
                return i;
            }
        }
        return -1;
    }

  private:
    nums_t nums_;
    functions_t functions_;
    applyFrom_t applyFrom_;
};


int main() {
    std::vector<int> nums({10, 20, 30, 40, 50});
    LazyArray<int> A(nums);

    auto twice = [](int x) { return 2 * x; };
    auto fastInc = [](int x) { return x + 1; };
    auto slowInc = [](int x) {
        std::cout << "(sleep 2s) " << std::flush;
        sleep(2);
        return x + 1;
    };

    auto B = A.map(twice);
    std::cout << "40 is at index=" << B.indexOf(40) << " in A.twice\n";

    auto D = B.map(fastInc).map(fastInc);
    std::cout << "33 is at index=" << D.indexOf(33) << " in A.twice.fastInc.fastInc\n";
    std::cout << "22 is at index=" << D.indexOf(22) << " in A.twice.fastInc.fastInc\n";

    auto C = B.map(slowInc).map(slowInc);
    std::cout << "42 is at index=" << C.indexOf(42) << " in A.twice.slowInc.slowInc\n";
    std::cout << "22 is at index=" << C.indexOf(22) << " in A.twice.slowInc.slowInc\n";

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
