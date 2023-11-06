
#include "common.h"
#include <stdexcept>
#include <vector>
#include "algorithms.hpp"





// QuickSelect




size_t partition_select(int* v, size_t start, size_t end, Pivot_f pivotFunction) {
    size_t pivot_index = pivotFunction(v, end - start) + start;
    swap((v + pivot_index), v + end);


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



double recure_select(int* v, size_t start, size_t end, size_t find,Pivot_f pivotFunction) {
    size_t vector_size = sizeof(v) / sizeof(v[0]);

    size_t split = partition_select(v, start, end, pivotFunction);


    if (find == split + 1) {
        return *(v + split);
    }

    if (split < find) {
        return recure_select(v, split + 1, end, find, pivotFunction);
    }
    else {
        return recure_select(v, start, split - 1, find, pivotFunction);
    }
}

int quickSelect(int* v, int k, Pivot_f pivotFunction)
{
    size_t vector_size = sizeof(v) / sizeof(v[0]) - 1;
    return recure_select(v, 0, vector_size - 1, k + 1, pivotFunction);
}

// Partition

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}



size_t partition(std::vector<int>& v, size_t start, size_t end, Pivot_f pivotFunction) {

    int* elem = v.data() + start;
    size_t pivot_index = pivotFunction(elem, end - start) + start;

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



void recure_sort(std::vector<int>& v, size_t start, size_t end, Pivot_f pivotFunction) {
    if (v.empty()) {
        return;
    }
    size_t split = partition(v, start, end, pivotFunction);
    if (end - start <= 1) {
        return;
    }



    if (split + 1 < end) {
        recure_sort(v, split + 1, end, pivotFunction);
    }
    if ((split != 0) && split - 1 > start) {
        recure_sort(v, start, split - 1, pivotFunction);
    }
}




size_t deterministicMedianPivot(int* data, size_t n)
{
    quickSelect(data, n / 2, deterministicPivot);
    return n / 2;
}

size_t uniformRandomMedianPivot(int* data, size_t n)
{
    quickSelect(data, n / 2, uniformRandomPivot);
    return n / 2;
}

// --------------------
// --------------------
// --------------------

// note: the quicksort logic of applying pivot function that finds the median might
// be different as opposed to simple pivot functions (i.e. deterministicPivot,
// uniformRandomPivot), hence there are 2 implementations of quickSort to be done

void quickSortSimplePivot(std::vector<int> &v, Pivot_f pivotFunction)
{
    recure_sort(v, 0, v.size() - 1, pivotFunction);
}

void quickSortMedianPivot(std::vector<int> &v, Pivot_f pivotFunction)
{
    recure_sort(v, 0, v.size() - 1, pivotFunction);
}

// clang-format off
#include "utils/benchmarkdata.h"

// lengths of arrays to benchmark (for different combinations of pivot policy and input data)
// feel free to change the numbers or add more if necessary
const BenchmarkData benchmarksData {
    BenchmarkData::Builder{}
        .add(PivotPolicy::Deterministic, InputData::SortedArray,                {100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
        .add(PivotPolicy::Deterministic, InputData::ReversedSortedArray,        {100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
        .add(PivotPolicy::Deterministic, InputData::RandomArray,                {100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })

        .add(PivotPolicy::UniformRandom, InputData::SortedArray,                { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
        .add(PivotPolicy::UniformRandom, InputData::ReversedSortedArray,        { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
        .add(PivotPolicy::UniformRandom, InputData::RandomArray,                { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })

        .add(PivotPolicy::MedianDeterministic, InputData::SortedArray,          { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL  })
        .add(PivotPolicy::MedianDeterministic, InputData::ReversedSortedArray,  { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL  })
        .add(PivotPolicy::MedianDeterministic, InputData::RandomArray,          { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL  })

        .add(PivotPolicy::MedianUniformRandom, InputData::SortedArray,          { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
        .add(PivotPolicy::MedianUniformRandom, InputData::ReversedSortedArray,  { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
        .add(PivotPolicy::MedianUniformRandom, InputData::RandomArray,          { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL })
    .build()
};
// clang-format on

// don't touch
#include "utils/quicksort.h"
