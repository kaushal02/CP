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
//04# MO's algorithm: take partitions of size k = n / sqrt(q) and get O(n * sqrt(q))
//05#

inline int high(ll n) { return 63 - __builtin_clzll(n);} // location of highest set bit
#define pq(c) priority_queue<c,vector<c>,compare<c>>
template<class T> struct compare {
	bool operator()(const T& l, const T& r) const {
		return l.Y > r.Y;
	}
};
#define umap(key, val) unordered_map<key,val,hashed<key>>
template<class T> struct hashed {
	size_t operator()(T const& c) const {
		return c.X+231LL*c.Y;
	}
};

int main () {
    set <int> s; s.size(); // O(1)
    queue <int> q; q.size(); // O(1)
    v1.insert(v1.end(), all(v2)); // O(v2.size())

    isnan(d); // returns true if double 'd' is NaN
	round(), floor(), ceil(), trunc(); // 5.5-> 6, 5, 6, 5 and -5.5-> -6, -6, -5, -5
	sqrt(), cbrt(), exp(), log(), log2(), log10(); //
	frac = modf(num, &inte); // double 'num' is divided into double 'inte' and double 'frac, all having same sign
	b.count(), b.any(), b.none(), b.all(), b.flip(); // oeprations on bitset 'b'
	cin >> ws;//eat whitespaces
	c = cin.peek();//get next character, maybe EOF
	cin.putback(c); //put c in stream

    // compression
    vi c(a, a+n); sort(all(c)); uni(c);
	map<int,int> id;
	int k(0); for(auto x: c) id[x]=k++;

    return 0;
}
