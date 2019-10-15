#include <set>
#include <random>
#include <iostream>
#include <chrono>
#include <bitset>

using namespace std;


template<size_t N>
bool IsDominated(std::bitset<N>& a, std::bitset<N>& b) {

    for (size_t i = 0; i < N; i++) {
        if (b[i] < a[i]) return false;
    }

    return true;
}

struct classcomp
{
    template <std::size_t N>
    bool operator ()(const bitset<N>* lhs, const bitset<N>* rhs) const;
};

template <std::size_t N>
inline bool classcomp::operator()(const bitset<N>* lhs, const bitset<N>* rhs) const
{
    return *lhs < *rhs;
}

template <std::size_t N>
bool operator<(const std::bitset<N> &x, const std::bitset<N> &y)
{
    for (int i = N - 1; i >= 0; i--)
    {
        if (x[i] ^ y[i])
            return y[i];
    }
    return false;
}

int main(int argc, char **argv)
{

    const size_t N_debug = 500;

    std::multiset<bitset<N_debug>*, classcomp> S_set;

    random_device rd;

    mt19937 mersenne_generator(rd()); // mt19937 is a standard mersenne_twister_engine

    uniform_int_distribution<size_t> uni(0, 1); // guaranteed unbiased
    int curr;
    bitset<N_debug> *s_member;
    for (unsigned int i = 0; i < 5000; i++)
    {
        s_member = new bitset<N_debug>;
        for (unsigned int j = 0; j < N_debug; j++)
        {
            curr = uni(mersenne_generator);
            s_member->set(j, curr);
        }
        S_set.insert(s_member);
    }

    unsigned int count = 1;
    auto end = std::prev(S_set.end());

    bitset<N_debug>* a;
    bitset<N_debug>* b;
    bool is_dominated;
    for (auto it_i=S_set.begin(); it_i!=end; ++it_i) {
        a = *it_i;
        is_dominated = false;
        for (auto it_j=std::next(it_i); it_j!=S_set.end(); ++it_j) {
            b = *it_j;
            if (IsDominated(*a,*b)) {
                is_dominated = true;
                break;
            }
        }
        if (!is_dominated) {
            count++;
        }
    }

    cout << "Min value on the set: " << *(*S_set.begin()) << endl;
    cout << "Max value on the set: " << *(*--S_set.end()) << endl;
    cout << "Number of dominant bitsets: " << count << endl;

    // cout << (*min_s < *max_s) << endl;

    return 0;
}