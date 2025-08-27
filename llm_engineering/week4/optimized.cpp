#include <iostream>
#include <vector>
#include <limits>
#include <chrono>

using namespace std;

// LCG function as a class to encapsulate state
class LCG {
    uint64_t value;
    static constexpr uint64_t a = 1664525;
    static constexpr uint64_t c = 1013904223;
    static constexpr uint64_t m = 4294967296; // 2^32

public:
    LCG(uint64_t seed) : value(seed) {}

    uint64_t next() {
        value = (a * value + c) % m;
        return value;
    }
};

int64_t max_subarray_sum(int n, uint64_t seed, int min_val, int max_val) {
    LCG lcg(seed);
    vector<int> random_numbers(n);
    for (int i = 0; i < n; ++i) {
        random_numbers[i] = static_cast<int>(lcg.next() % (max_val - min_val + 1)) + min_val;
    }

    int64_t max_sum = numeric_limits<int64_t>::min();
    for (int i = 0; i < n; ++i) {
        int64_t current_sum = 0;
        for (int j = i; j < n; ++j) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
}

int64_t total_max_subarray_sum(int n, uint64_t initial_seed, int min_val, int max_val) {
    int64_t total_sum = 0;
    LCG lcg(initial_seed);
    for (int i = 0; i < 20; ++i) {
        total_sum += max_subarray_sum(n, lcg.next(), min_val, max_val);
    }
    return total_sum;
}

int main() {
    int n = 10000;
    uint64_t initial_seed = 42;
    int min_val = -10;
    int max_val = 10;

    auto start_time = chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = chrono::high_resolution_clock::now();

    chrono::duration<double> execution_time = end_time - start_time;
    cout << "Total Maximum Subarray Sum (20 runs): " << result << endl;
    cout << "Execution Time: " << execution_time.count() << " seconds" << endl;

    return 0;
}
