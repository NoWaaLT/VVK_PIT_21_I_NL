#pragma once
#include <random>
#include <chrono>

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

class RandInt {
public:
	RandInt(int low, int high) : mt{ rd() }, dist{ low, high } {};
	int operator()() { return dist(mt); }
private:
	random_device rd;
	mt19937 mt;
	uniform_int_distribution<int> dist;
};
