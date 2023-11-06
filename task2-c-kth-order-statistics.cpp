#include <stdexcept>
#include <vector>

#include "common.h"

/**
 * @brief finds kth order statistics in the input vector @p v
 *
 * @param v
 * @param k
 * @param pivotFunction - function pointer that specifies the algorithm to select
 * pivot element. quickSelect will be tested/benchmarked with deterministicPivot
 * and uniformRandomPivot implementations from common.h
 *
 * Constraints:
 *      1. v.size() > 0
 *      2. 1 <= k <= v.size()
 *      3. pivotPolicy != nullptr (e.g. it's safe to call pivotPolicy())
 *
 * @return int - kth order statistics of the input array @p v . For example:
 *      v = [3, 2, 5, 4],     k = 2 ---> 3
 *      v = [5, 7, 6, 5],     k = 2 ---> 5
 *      v = [4, 5, 6, 0, 2],  k = 1 ---> 0
 */




void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


size_t partition(std::vector<int>& v, size_t start, size_t end, Pivot_f pivotFunction) {
    size_t pivot_index = pivotFunction(v.data(), end - start) + start;
    swap(&v[pivot_index], &v[end]);


    int pivot = v[end];

    int index_sm = start;
    for (size_t i = start; i < end; i++) {
        if (v[i] < pivot) {
            swap(&v[index_sm], &v[i]);
            index_sm += 1;
        }
    }
    swap(&v[index_sm], &v[end]);

    return index_sm;

}
// 0 1 2 3  4  5
// 0 1 5 6 10 17



double recure(std::vector<int>& v, size_t start, size_t end, size_t find, Pivot_f pivotFunction) {
    size_t vector_size = v.size();
    size_t split = partition(v, start, end, pivotFunction);


    if (find == split + 1) {
        return v[split];
    }

    if (split < find) {
        return recure(v, split + 1, end, find, pivotFunction);
    }
    else {
        return recure(v, start, split - 1, find, pivotFunction);
    }

}




int quickSelect(std::vector<int>& v, int k, Pivot_f pivotFunction)
{
    return recure(v, 0, v.size() - 1, k, pivotFunction);
}


// --------------------
// --------------------
// --------------------

// clang-format off
#include "utils/benchmarkdata.h"

// lengths of arrays to benchmark (for different combinations of pivot policy and input data)
// feel free to change the numbers or add more if necessary
const BenchmarkData benchmarksData {
    BenchmarkData::Builder{}
        .add(PivotPolicy::Deterministic, InputData::SortedArray,            { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
        .add(PivotPolicy::Deterministic, InputData::ReversedSortedArray,    { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL  })
        .add(PivotPolicy::Deterministic, InputData::RandomArray,            { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL  })
        
        .add(PivotPolicy::UniformRandom, InputData::SortedArray,            { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
        .add(PivotPolicy::UniformRandom, InputData::ReversedSortedArray,    { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
        .add(PivotPolicy::UniformRandom, InputData::RandomArray,            { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL  })
    .build()
};
// clang-format on

// don't touch
#include "utils/kth-order-statistics.h"
