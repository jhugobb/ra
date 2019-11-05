#include <set>
#include <random>
#include <iostream>
#include <fstream>
#include <chrono>
#include <bitset>
#include <algorithm>

using namespace std;

const size_t N_BITS = 16;
const size_t N_EXPERIMENTS = 1000;
const size_t N_STRINGS = 8000;

template <size_t N>
bool IsDominated(std::bitset<N> &a, std::bitset<N> &b)
{

    for (size_t i = 0; i < N; i++)
    {
        if (b[i] < a[i])
            return false;
    }

    return true;
}

struct classcomp
{
    template <std::size_t N>
    bool operator()(const bitset<N> *lhs, const bitset<N> *rhs) const;
};

template <std::size_t N>
inline bool classcomp::operator()(const bitset<N> *lhs, const bitset<N> *rhs) const
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

void writeMAX_StoFile(std::vector<std::bitset<N_BITS>> out, std::ofstream f) {

}

int main(int argc, char **argv)
{

    std::cout << "Number of bits: " << N_BITS << std::endl;
    std::cout << "Number of experiments: " << N_EXPERIMENTS << std::endl;
    std::cout << "Number of Strings in each Set: " << N_STRINGS << std::endl;

    std::ofstream f;
    f.open("results.txt");

    std::multiset<bitset<N_BITS> *, classcomp> S_set;

    random_device rd;
    mt19937 mersenne_generator(rd());           // mt19937 is a standard mersenne_twister_engine
    uniform_int_distribution<size_t> uni(1, 2); // guaranteed unbiased

    int n_ones = 0;
    std::vector<int> results;
    std::vector<std::bitset<N_BITS>> output;
    for (unsigned int k = 0; k < N_EXPERIMENTS; k++)
    {
        output.clear();
        S_set.clear();
        f << "Experiment " << k << ":" << std::endl;
        bool i_chose_one = false;

        for (unsigned int i = 0; i < N_STRINGS; i++)
        {
            bitset<N_BITS> *s_member = new bitset<N_BITS>;
            for (unsigned int j = 0; j < N_BITS; j++)
            {
                int curr = uni(mersenne_generator) / 2;
                s_member->set(j, curr);
            }
            S_set.insert(s_member);

            if (s_member->all())
            {
                i_chose_one = true;
                n_ones++;
                break;
            }
        }

        unsigned int count = 0;
        if (!i_chose_one)
        {
            auto end = std::prev(S_set.end());

            bitset<N_BITS> *a;
            bitset<N_BITS> *b;
            bool is_dominated;
            for (auto it_i = S_set.begin(); it_i != end; ++it_i)
            {
                a = *it_i;
                is_dominated = false;
                for (auto it_j = std::next(it_i); it_j != S_set.end(); ++it_j)
                {
                    b = *it_j;
                    if (IsDominated(*a, *b))
                    {
                        is_dominated = true;
                        break;
                    }
                }
                if (!is_dominated)
                {
                    count++;
                    output.push_back(*a);
                }
            }
        } else {
            count++;
            output.push_back(std::bitset<N_BITS>().flip());
        }
        // std::cout << "Max value on the set: " << *(*--S_set.end()) << endl;
        // std::cout << "Number of dominant bitsets: " << count <<  << \irflush;
        std::cout << k << '\r' << flush;

        std::string tmp;
        for (uint i = 0; i < output.size(); i++) {
            tmp = output[i].to_string<char,std::string::traits_type,std::string::allocator_type>();
            f << tmp << std::endl;
        }
        f << std::endl;
        results.push_back(count);
    }
    f.close();
    std::sort(results.begin(), results.end());

    std::cout << "Median of the experiment: ";
    std::cout << results[results.size() / 2] << endl;

    std::cout << "Number of times we chose 1's: " << n_ones << endl;

#ifdef _WIN32
    system("pause");
#endif // _WIN32

    return 0;
}