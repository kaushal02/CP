#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
template <typename T> using ordered_set =  tree<T, null_type, less<T>, \
						rb_tree_tag, tree_order_statistics_node_update>;

/// Methods available
s.insert(x)
s.erase(x) // If x is present, remove it
s.erase(s.lower_bound(x)) // Remove x or just bigger than x
s.order_of_key(x) // get 0-based index of x or just bigger than x
*s.find_by_order(i) // element access
/******************************************************************************************
*******************************************************************************************
******************************************************************************************/

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
template<class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct my_node_update {
    typedef ll metadata_type; // change
    virtual Node_CItr node_begin() const=0;
    virtual Node_CItr node_end() const=0;
    virtual ~my_node_update() {}

    void init(metadata_type &a) {
    	// update
    }
    int solve(ll k) {
        metadata_type myans;
		init(myans);

		auto it = node_begin();
        while(it != node_end()) {
            auto l = it.get_l_child();
            auto r = it.get_r_child();

            // update
            if() {
            	it = l;
            }
            else {
            	it = r;
            }
        }
        return myans; // change
    }

    void operator()(Node_Itr it, Node_CItr it_end) {
        auto l = it.get_l_child();
        auto r = it.get_r_child();
        metadata_type lt, rt;
        init(lt), init(rt);
        if(l != it_end) lt = l.get_metadata();
        if(r != it_end) rt = r.get_metadata();
        const_cast<metadata_type&>(it.get_metadata()) =
        	lt + rt; // change
    }
};
template <typename T> using TREE =  tree<T, null_type, less<T>, rb_tree_tag, my_node_update>;
