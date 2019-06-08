#pragma once

#include <stdint.h>
#include <stdexcept>

/**
 * Prime numbers iterator
**/
class prime_iterator
{
    friend class prime_range;

    public:
        /** Default constructor */
        explicit prime_iterator(bool backward = false) : _currentPrime(1)
        {
            if (backward) {
                _currentPrime = std::numeric_limits<uint64_t>::max();
            }
        }

        /**
         * @param N - total amount of numbers
         * @param backWard - for backward iterator
         */
        explicit prime_iterator(uint64_t N, bool backward = false)
            : _currentPrime(1)
        {
            if (N == 0) {
                throw std::runtime_error("Not valid value for prime iterator");
            }

            if (backward) {
                _currentPrime = N;
                iterate_forward();
            }
        }

        /** Dereference operator */
        uint64_t operator*() const { return _currentPrime; }

        /** Forward iteration step */
        prime_iterator& operator++()
        {
            iterate_forward();
            return *this;
        }

        /** Forward iteration step */
        prime_iterator& operator++(int)
        {
            iterate_forward();
            return *this;
        }

        /** Backward iteration step */
        prime_iterator& operator--()
        {
            iterate_backward();
            return *this;
        }

        /** Backward iteration step */
        prime_iterator& operator--(int)
        {
            iterate_backward();
            return *this;
        }

        /** Comparison operator */
        bool operator == (const prime_iterator &other) const
        {
            return _currentPrime == other._currentPrime;
        }

        bool operator !=(const prime_iterator &other) const
        {
            return !(*this == other);
        }

    protected:
        /** Forward iteration step. */
        void iterate_forward()
        {
            auto total = std::numeric_limits<uint64_t>::max();
            for (uint64_t i = _currentPrime + 1; i <= total; ++i) {
                if (isPrime(i)) {
                    _currentPrime = i;
                    break;
                }
            } // for
        }

        /** Backward iteration step. */
        void iterate_backward()
        {
            if (_currentPrime - 1 == 0) {
                _currentPrime = 0;
                return;
            }
            for (uint64_t i = _currentPrime - 1; i > 0; --i) {
                if (isPrime(i)) {
                    _currentPrime = i;
                    break;
                }
            } // for
        }

        /** Check if the number is prime. */
        bool isPrime(uint64_t n) const
        {
            for (uint64_t i = 2; i*i <= n; ++i) {
                if ( n % i == 0) {
                    return  false;
                }
            }
            return true;
        }
    private:
        uint64_t _currentPrime = 0;  // current prime number
};

/**
 * Prime numbers reverse iterator.
**/
class prime_riterator : public prime_iterator
{
    public:
        /** Default constructor */
        prime_riterator(bool forward = false) : prime_iterator(!forward)
        {
            iterate_backward();
        }

        explicit prime_riterator(uint64_t N, bool forward = false)
            : prime_iterator(N, !forward)
        {
            iterate_backward();
        }

        prime_riterator& operator++()
        {
            iterate_backward();
            return *this;
        }

        prime_riterator& operator++(int)
        {
            iterate_backward();
            return *this;
        }

        /** Backward iteration step */
        prime_riterator& operator--()
        {
            iterate_forward();
            return *this;
        }

        /** Backward iteration step */
        prime_riterator& operator--(int)
        {
            iterate_forward();
            return *this;
        }
};

namespace std {
template<>
struct iterator_traits<prime_iterator> {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = uint64_t;
    using difference_type = uint64_t;
};

template<>
struct iterator_traits<prime_riterator> {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = uint64_t;
    using difference_type = uint64_t;
};
}

/**
 * Prime numbers range.
**/
class prime_range
{
    public:
        explicit prime_range(uint64_t N) : _total(N)
        {
            if (N == 0) {
                throw std::runtime_error("Not valid value for prime iterator");
            }
        }
        prime_iterator begin() const { return prime_iterator(_total); }
        prime_iterator end() const { return prime_iterator(_total, true); }
        prime_riterator rbegin() const { return prime_riterator(_total); }
        prime_riterator rend() const { return prime_riterator(_total, true); }
        uint64_t total() const { return _total; }

    private:
        uint64_t _total;
};
