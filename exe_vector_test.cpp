#include <vector>
#include <algorithm>
#include <numeric>
#include <nh3api/core.hpp>

template<typename VectorType>
static VectorType& initialize(VectorType& vec)
{
    // 1. initialize a vector of 100 ints
    vec.resize(100);

    // 2. fill it with numbers from 0 to 99
    std::iota(vec.begin(), vec.end(), 0);

    auto middle = vec.cbegin() + (vec.size() / 2);

    // 3. create two separate vectors half a size 
    // then initialize them from the two halves of the initial vector
    VectorType vec2(vec.cbegin(), middle);
    VectorType vec3(middle, vec.cend());

    // 4. clear and invalidate middle iterator
    vec.clear();
    vec.reserve(100);

    // 5. shuffle two halves
    auto last = vec.insert(vec.begin(), vec2.cbegin(), vec2.cend());
    vec.insert(last, vec3.cbegin(), vec3.cend());

    middle = vec.cbegin() + (vec.size() / 2);

    assert(vec.size() == 100);
    assert(std::is_sorted(vec.cbegin(), middle)
        && std::is_sorted(middle, vec.cend()));

    // 6. shuffle again, assume that the whole vector is sorted now
    auto middle2 = vec.begin() + (vec.size() / 2);
    std::swap_ranges(vec.begin(), middle2, middle2);
    assert(std::is_sorted(vec.cbegin(), vec.cend()));

    return vec;

}

static bool isPrime(int number)
{
    if (number < 2) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    for (int i = 3; (i * i) <= number; i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}

// returns a sorted vector of 100 integers from 0 to 99 but without primes
template<typename VectorType>
static VectorType& erasePrimes(VectorType& vec)
{
    const auto pred = [](int number) -> bool { return isPrime(number); };

    [[maybe_unused]]
    const size_t initialSize = vec.size();
    // 1. check if there was primes before
    [[maybe_unused]]
    const int initialNumPrimes = std::count_if(vec.cbegin(), vec.cend(), pred);
    assert(initialNumPrimes > 0);

    // 2. erase primes using remove-erase idiom
    vec.erase(std::remove_if(vec.begin(), vec.end(), pred), vec.end());

    // 3. check if there are no primes left
    [[maybe_unused]]
    int numPrimes = std::count_if(vec.cbegin(), vec.cend(), pred);
    assert(numPrimes == 0);

    // 4. ensure that vector's erase didn't erase anything but primes
    assert(vec.size() == initialSize - initialNumPrimes);

    return vec;
}

void exe_vector_test()
{
    std::vector<int> std_vec{};
    exe_vector<int> exe_vec{};

    const auto& transformed1 = erasePrimes(initialize(std_vec));
    const auto& transformed2 = erasePrimes(initialize(exe_vec));
    if (std::equal(transformed1.cbegin(), transformed1.cend(),
        transformed2.cbegin(), transformed2.cend()))
        NormalDialog("Test successful!");
    else
        NormalDialog("Something Failed...");
}
