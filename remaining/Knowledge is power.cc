#include <bits/stdc++.h>
using namespace std;

/*
 * OPERATOR PRECEDENCE king to slave
 * comma                    ,
 * compound assignment  RL  o=
 * direct assignment    RL  =
 * ternary conditional  RL  ?:
 * logical or               ||      aka "or"
 * logical and              &&      aka "and"
 * bitwise or               |
 * bitwise exclusive or     ^
 * bitwise and              &
 * relational operator      == !=
 * relational operator      > >= < <=
 * bitwise ls/rs            >> <<
 * mathematical             + -
 * mathematical             * / %
 * not/prefix change    RL  ! ~ +n -n ++n --n
 * suffix change            n++ n--
 * scope resolution         ::
 */

//01# binary_search() goes right for False, and vice-versa
//02# stl containers has a max_size() of 1e8 at least and can be accessed till even in main()
//03# T a[] is not stl and it can be globally expanded till 1GB but only up to 1MB inside a function
//04# MO's algorithm: take size of partition k = n / sqrt(q) and get O(n * sqrt(q))
//05# 

#define pq(ctype...) priority_queue < ctype, vector < ctype >, compare < ctype > >
template <class T >
struct compare {
    bool operator()(const T& l, const T& r) const {
        return ; // Put the logic
    }
};

#define umap(key, val) unordered_map<key,val,hashed<key>>
template <typename Container>
struct hashed {
    size_t operator()(Container const& c) const {
        return c.X + 15641LL * c.Y; // Some custom way to hash the container
    }
};

inline int high(ll n) {
    // Maximum 'b' satisfying (1<<b) <= n
    if(n < 1) return 0;
    return 63 - __builtin_clzll(n);
}

int main () {
    set <int> s; s.size(); // O(1)
    queue <int> q; q.size(); // O(1)
    v1.insert(v1.end(), all(v2)); // O(v2.size())
    return 0;
}
