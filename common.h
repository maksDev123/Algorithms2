#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>
// --------------------
// --------------------
// Common pivot functions that will be reused across multiple tasks
// --------------------
// --------------------

using Pivot_f = size_t (*)(int *, size_t);

/**
 * @brief function that selects pivot deterministically (e.g. first element)
 *
 * @param data - pointer to the part of array
 * @param n - number of elements in (sub)array pointed to by @p data
 *
 * Constraints (should hold in quickSelect(...) and quickSortSimplePivot(...)
 * implementations)
 *      1. @p data is not nullptr
 *      2. @p n > 0
 *
 * @return size_t index of pivot element (should be in range [0; n - 1])
 */

size_t deterministicPivot(int *data, size_t n)
{
    return n;
}

/**
 * @brief function that selects pivot uniformly at random
 *
 * @param data - pointer to the part of array
 * @param n - number of elements in (sub)array pointed to by @p data
 *
 * Constraints (should hold in quickSelect(...) and quickSortSimplePivot(...)
 * implementations)
 *      1. @p data is not nullptr
 *      2. @p n > 0
 *
 * @return size_t index of pivot element (should be in range [0; n - 1])
 */
size_t uniformRandomPivot(int * data, size_t n)
{   
    if (n == 0) {
        return 0;
    }
    int range = n;
    int num = rand() % range;
    return num;
}

// --------------------
// --------------------
// Utility enums (don't touch)
// --------------------
// --------------------

enum class PivotPolicy
{
    Deterministic,
    UniformRandom,
    MedianDeterministic,
    MedianUniformRandom
};

enum class InputData
{
    SortedArray,
    ReversedSortedArray,
    RandomArray
};

#include <ostream>
std::ostream &operator<<(std::ostream &, PivotPolicy);
std::ostream &operator<<(std::ostream &, InputData);
#include "utils/common_impl.h"
