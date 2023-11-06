#include <stdexcept>
#include <vector>

#include "common.h"

// Note: pivot functions are not used in this source file, since
// calculation of median might required finding 2 middle elements
// in case the array length is even (and pivot functions in common.h)
// are not really designed for this

/**
 * @brief calculate median of @p v in deterministic fashion
 *
 * @param v
 *
 * Constraints:
 *      1. v.size() >= 1
 * Examples:
 *      v = [1]     ---> 1
 *      v = [1,2]   ---> 1.5
 *      v = [3,4,4] ---> 4
 *
 * @return double - median of @p v
 */
#include "algorithms.hpp"
#include <limits>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


size_t partition(std::vector<int>& v, size_t start, size_t end, bool random) {
    int pivot;
    if (random == false) {
        pivot = v[end];
    }
    else {
        int range = end - start + 1;
        int num = rand() % range + start;
        pivot = v[num];
        swap(&v[num], &v[end]);
    }

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


void recure(std::vector<int>& v, size_t start, size_t end, int& a, int& b, bool& flag1, bool& flag2, bool random) {
    size_t vector_size = v.size();
    size_t split = partition(v, start, end, random);


    if (vector_size / 2 == split) {
        a = v[split];
        flag1 = true;
        if (flag2 != false or vector_size % 2 == 1) {
            return;
        }
    }
    if (vector_size % 2 == 0 && split == ((vector_size - 1) / 2)) {
        b = v[split];
        flag2 = true;
        if (flag1 != false) {
            return;
        }
    }



    if (split < vector_size - split) {
        return recure(v, split + 1, end, a, b, flag1, flag2, random);
    }
    else {
        return recure(v, start, split - 1, a, b, flag1, flag2, random);
    }

}



double medianDeterministicPivot(std::vector<int>& v)
{
    int a = 0;
    int b = 0;

    bool flag1 = false;
    bool flag2 = false;
    recure(v, 0, v.size() - 1, a, b, flag1, flag2, false);

    if (v.size() % 2 == 0) {
        return (double)(a + b) / 2;
    }
    else {
        return a;
    }
}


/**
 * @brief calculates median of @p v by selecting pivot uniformly at random
 *
 * @param v
 *
 * Constraints:
 *      1. v.size() >= 1
 * Examples:
 *      v = [1]     ---> 1
 *      v = [1,2]   ---> 1.5
 *      v = [3,4,4] ---> 4
 *
 * @return double - median of @p v
 */
double medianUniformRandomPivot(std::vector<int> &v)
{
    int a = 0;
    int b = 0;

    bool flag1 = false;
    bool flag2 = false;

    recure(v, 0, v.size() - 1, a, b, flag1, flag2, true);

    if (v.size() % 2 == 0) {
        return (double)(a + b) / 2;
    }
    else {
        return a;
    }
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
        
        .add(PivotPolicy::UniformRandom, InputData::SortedArray,            { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL  })
        .add(PivotPolicy::UniformRandom, InputData::ReversedSortedArray,    { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL  })
        .add(PivotPolicy::UniformRandom, InputData::RandomArray,            { 100LL, 400LL,700LL, 1000LL, 1300LL, 1700LL, 2000LL  })
    .build()
};
// clang-format on

// don't touch
#include "utils/median.h"
