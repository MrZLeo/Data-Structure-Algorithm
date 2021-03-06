#ifndef DATA_STRUCTURE_ALGORITHM_SRC_COUNTSORT_HPP
#define DATA_STRUCTURE_ALGORITHM_SRC_COUNTSORT_HPP

#include <vector>

using std::vector;

template<class T, size_t N>
void count_sort(vector<T> &arr)
{
    vector<T> temp = vector(N + 1, 0);
    for (auto v : arr) {
        temp[v]++;
    }

    for (int i = 1; i <= N; ++i) {
        temp[i] += temp[i - 1];
    }

    vector<T> res = vector(arr.size(), 0);
    // reverse order can make count sort stable:
    // last one can place the last position of this element
    // but this method cost more space(we can place element in $arr
    // directly if we don't need stability)
    for (auto v = arr.rbegin(); v != arr.rend(); ++v) {
        res[temp[*v] - 1] = *v;
        temp[*v]--;
    }
    arr = res;
}

#endif // DATA_STRUCTURE_ALGORITHM_SRC_COUNTSORT_HPP
