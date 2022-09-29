#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector <int>& a, int l, int r) {
    for (int i = l; i < r; i++) {
        int min_idx = i;
        for (int j = i + 1; j < r; j++) {
            if (a[j] < a[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(a[i], a[min_idx]);
        }
    }
}

int getKthElement(vector <int>& a, int l, int r, int k);

int getPivot(vector <int>& a, int l, int r) {
    if (r - l < 5) {
        selectionSort(a, l, r);
        return a[(l + r) / 2];
    }

    int lo = l, hi = l + 4, medians_idx = l;
    while (lo <= hi) {
        selectionSort(a, lo, hi);
        swap(a[medians_idx], a[(lo + hi) / 2]);
        medians_idx++;
        lo = lo + 5;
        hi = min(hi + 5, r);
    }
    return getKthElement(a, l, medians_idx - 1, (medians_idx - l) / 2);
}

int getKthElement(vector <int>& a, int l, int r, int k) {
    if (l == r) {
        return a[l];
    }
    int pivot = getPivot(a, l, r);
    int lo = l, hi = r;
    while (lo < hi) {
        if (a[lo] > pivot) {
            swap(a[lo], a[hi]);
            hi--;
        } else if (a[hi] <= pivot) {
            swap(a[lo], a[hi]);
            lo++;
        } else {
            lo++;
            hi--;
        }
    }
    // [l, lo) <= pivot
    if (k <= lo - l) {
        return getKthElement(a, l, lo - 1, k);
    } else {
        return getKthElement(a, lo, r, k - (lo - l));
    }
}

int medianOfMedian(vector <int> a) {
    int n = a.size();
    return getKthElement(a, 0, n - 1, (n + 1) / 2);
}

int main() {
    // your code goes here
    int case_count;
    cin >> case_count;
    while (case_count--) {
        int n; cin >> n;
        vector <int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        int median = medianOfMedian(arr);
        vector <int> arr_snake(n);
        int lo_index = 0, hi_index = 1, median_count = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] < median) {
                arr_snake[lo_index] = arr[i];
                lo_index += 2;
            } else if (arr[i] > median) {
                arr_snake[hi_index] = arr[i];
                hi_index += 2;
            } else {
                median_count++;
            }
        }
        while (hi_index < n) {
            arr_snake[hi_index] = median;
            hi_index += 2;
            median_count--;
        }
        while (lo_index < n) {
            arr_snake[lo_index] = median;
            lo_index += 2;
            median_count--;
        }
        for (int i = 0; i < n; i++) {
            cout << arr_snake[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}