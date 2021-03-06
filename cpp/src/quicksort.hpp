#ifndef DATA_STRUCTURE_ALGORITHM_SRC_QUICKSORT_HPP
#define DATA_STRUCTURE_ALGORITHM_SRC_QUICKSORT_HPP

#include "insertionsort.hpp"
#include <vector>

using std::vector;

template<class T>
int partition(vector<T> &arr, int l, int r)
{
    std::swap(arr[l], arr[(random() % (r - l)) + l]);
    const int p = arr[l];
    int j = l; // [l, j] stands for arr[j] <= p
    for (int i = l + 1; i < r; ++i) {
        if (arr[i] <= p) {
            j++;
            std::swap(arr[j], arr[i]);
        }
    }

    std::swap(arr[l], arr[j]);
    return j;
}

template<class T>
int partition2(vector<T> &arr, int l, int r)
{
    std::swap(arr[l], arr[(random() % (r - l)) + l]);
    const int p = arr[l];
    int j = l + 1;
    int k = r - 1;
    while (true) {
        while (j < r && arr[j] < p)
            j++;
        while (k > l && arr[k] > p)
            k--;

        if (j > k)
            break;

        std::swap(arr[j], arr[k]);
        j++;
        k--;
    }

    std::swap(arr[l], arr[k]);
    return k;
}

template<class T>
void quicksort(vector<T> &arr, int l, int r)
{
    switch (r - l) {
    case 0:
    case 1:
        return;
    case 2:
        if (arr[l] > arr[l + 1])
            std::swap(arr[l], arr[l + 1]);
        return;
    case 3 ... 30:
        return insertion_sort(arr, l, r);
    default:
        break;
    }

    int i = partition(arr, l, r);
    quicksort(arr, l, i);
    quicksort(arr, i + 1, r);
}

template<class T>
void quicksort2ways(vector<T> &arr, int l, int r)
{
    switch (r - l) {
    case 0:
    case 1:
        return;
    case 2:
        if (arr[l] > arr[l + 1])
            std::swap(arr[l], arr[l + 1]);
        return;
    case 3 ... 30:
        return insertion_sort(arr, l, r);
    }

    int i = partition2(arr, l, r);
    quicksort2ways(arr, l, i + 1);
    quicksort2ways(arr, i + 1, r);
}

template<class T>
T find_kth(vector<T> &arr, int l, int r, int k)
{
    if (l == r)
        return arr[l];
    int q = partition(arr, l, r);
    if (q == k - 1)
        return arr[q];
    else if (q < k - 1)
        return find_kth(arr, q + 1, r, k);
    else
        return find_kth(arr, l, q - 1, k);
}

#endif // DATA_STRUCTURE_ALGORITHM_SRC_QUICKSORT_HPP
