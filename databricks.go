// To execute Go code, please declare a func main() in a package "main"
/*
# Python
a = LazyArray([10,20,30,40,50])
times_two = lambda x : x*2
assert(a.map(times_two).index_of(40) == 1)
assert(a.map(times_two).index_of(40) == 1)

x = a.map(times_two).map(f2)
x.index_of(20)
x.index_of(30)

// map(f) 
*/

package main

import "fmt"

type LazyArray struct {
	arr []int
	// func -> last index
	funcs []func(int) int
	appliedTillIndex []int
}

func NewLazyArray(arr []int) *LazyArray {
	return &LazyArray{
		arr: arr,
	}
}

func (l *LazyArray) myMap(f func(int) int) *LazyArray {
	newArr := make([]int, len(l.arr))
	for i, val := range l.arr {
		newArr[i] = val
	}
	lNew := &LazyArray{
    arr: newArr,
		funcs: append(l.funcs, f),
		appliedTillIndex: append(l.appliedTillIndex, -1),
  }
	return lNew
}

func (l *LazyArray) indexOf(val int) int {
	ind := -1
	for i:=0; i<len(l.arr); i++ {
		// apply all fn on ith element
		for j, f := range l.funcs {
			// is jth fn applied on i
			if l.appliedTillIndex[j] >= i {
				continue
			}
			// apply
			modified := f(l.arr[i])
			// store
			l.arr[i] = modified
			l.appliedTillIndex[j] = i
		}

		// check
		if l.arr[i] == val {
			ind = i
			break
		}
	}

	return ind
}

/*
map after indexOf
*/

/*
a := NewLazyArray([]int{10,20,30,40,50}).map(time_consuming_lambda)
a.indexof(xxx) // * 1million times

b := a.map(fast_lambda)
// do something for b
*/

func main() {
  l := NewLazyArray([]int{10,20,30,40,50})
	// x := l.myMap(func(x int)int {return x*2}).indexOf(40)//.myMap(..)
	// fmt.Println(x)
	// x = l.myMap(func(x int)int {return x*2}).indexOf(40)
	// fmt.Println(x)
	// x = l.myMap(func(x int)int {return x*2}).myMap(func(x int)int {return x*2}).indexOf(40)
	// fmt.Println(x)

	y := l.myMap(func(x int)int {return x*2})
	// fmt.Println(y.indexOf(40))
	z := y.myMap(func(x int)int {return x*2})
	// fmt.Println(z.indexOf(40))
	fmt.Println(z.indexOf(90))
	w := z.myMap(func(x int)int {return x+10})
	fmt.Println(w.indexOf(90))

	// fmt.Println(l.indexOf(90))
	// l.myMap(func(x int)int {return x-10})
	// fmt.Println(l.indexOf(90))
}
