#include <stdexcept>
#include <utility>
#include <vector>

/**
 * @brief deterministic algorithm for calculating min/max value in the given vector
 *
 * @param v - vector to find min/max value in
 *
 * Constraints:
 *      1. @p v is not empty
 *      2. first element of the returned pair should be <= than the second element
 *      3. no constraints on the values inside @p v
 *
 * @return std::pair<int, int> pair of min and max elements of @p v
 */
std::pair<int, int> minMaxElement(const std::vector<int> &v)
{   

    size_t size_v = v.size();
    if (size_v == 1) {
        return std::make_pair(v[0], v[0]);
    }
    int max;
    int min;

    if (v[0] > v[1]) {
        max = v[0];
        min = v[1];
    }
    else {
        max = v[1];
        min = v[0];
    }
    for (size_t i = 2; i < size_v; i++) {
        if (v[i] > max) {
            max = v[i];
        }
        if (v[i] < min) {
            min = v[i];
        }
    }
    return std::make_pair(min, max);
}

// lengths of vectors to benchmark (feel free to change)
const std::vector<long long> Ns{ 100, 200, 300, 400, 500, 600, 700};

// don't touch
#include "utils/min-max-element.h"
