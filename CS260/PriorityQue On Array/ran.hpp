#ifndef RN_H
#define RN_H
#include <random>

std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_int_distribution<uint64_t> dis(0, UINT64_MAX);
std::uniform_int_distribution<int> idis(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
#endif