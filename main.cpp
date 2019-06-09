#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include "prime_range.h"

using namespace std;

std::vector<bool> prime_numbers;
void generate_prime(unsigned int n)
{
    prime_numbers.resize(n+1, true);
    for (unsigned int i=2; i*i <= n; i++) {
        if (prime_numbers[i]){
            for (unsigned int j = i*i; j <= n; j += i) {
                prime_numbers[j] = false;
            }
        }
    }
}

int main()
{
    const int primes_count = 500;

    generate_prime(primes_count);
    for (int i=1; i<primes_count; i++) {
        if (prime_numbers[i]) {
            cout << i << ", ";
        }
    }

    cout <<"\n\n";

    prime_range range(primes_count);
    for (auto p : range) {
        cout << p << ", ";
    }

    cout << " \n\nbackward: \n";

    for (auto itr = std::rbegin(range);
              itr != std::rend(range);
              itr++)
    {
        cout << *itr << ", ";
    }

    cout <<"\n\n";

    prime_range range2(primes_count);
    auto itr_start = range2.begin();
    auto itr_end = range2.end();

    itr_start++;
    itr_start++;

    itr_end--;
    itr_end--;

    auto [v_min, v_max] = std::minmax_element(itr_start, itr_end);
    cout << "v_min: " << *v_min << ", v_max: " << *v_max << "\n";

    auto d = std::distance(itr_start, itr_end);
    cout << "distance: " << d;

    cout << "\n\n";
    cout << "back inserter: \n";

    std::vector<uint64_t> elements;
    std::copy(itr_start, itr_end, back_inserter(elements));
    std::for_each(elements.begin(), elements.end(), [](uint64_t v) { cout << v << ", ";});

    return 0;
}
