#include <set>
#include <random>
#include <iostream>
#include <chrono>
#include <bitset>

using namespace std;



template<std::size_t N>
bool operator<(const std::bitset<N>& x, const std::bitset<N>& y) {
    for (int i = N-1; i >= 0; i--) {
        if (x[i] ^ y[i]) return y[i];
    }
    return false;
}

int main(int argc, char** argv) {

  std::vector<bitset<500>> S_set;

  random_device rd;

  mt19937 mersenne_generator(rd());  // mt19937 is a standard mersenne_twister_engine

  uniform_int_distribution<size_t> uni(0,1); // guaranteed unbiased
  int curr;
  bitset<500> s_member;
  for (unsigned int i = 0; i < 5; i++) {
    for (unsigned int j = 0; j < 500; j++) {
      curr = uni(mersenne_generator);
      s_member.set(j, curr);
    }
    S_set.push_back(s_member);
  }

  bitset<500> max_s = bitset<500>(0);
  bitset<500> min_s = bitset<500>(0);
  min_s.flip();
  bitset<500> s;
  for (unsigned int i = 0; i < S_set.size(); i++) {
    s = S_set.at(i);
    if (s < min_s)
      min_s = s;
    if (max_s < s)
      max_s = s;
  }

  cout << "Min value on the set: " << max_s << endl;
  cout << "Max value on the set: " << min_s << endl;

  return 0;
}