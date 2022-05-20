#include <vector>

#pragma once

template<class T>
int SearchMaxSequenceIdenticalCharacters(const std::vector<T>& v) {
	if (v.empty())
		return 0;

	int max = 0, count = 1;

	for (int i = 0; i < v.size()-1; i++) {
		if (v[i] == v[i + 1]) {
			count++;
		}
		else {
			max < count ? max = count : count = 1;
		}
	}
	if (max < count)
		return count;
	return max;
}

template<class T>
int SearchMaxEven(const std::vector<T>& v) {
	if (v.empty())
		return -1;

	unsigned int id = -1;
	T max = v[0];
	for (auto i = 0; i < v.size(); i++) {
		if (v[i] % 2 == 0) {
			id = i;
			break;
		}
	}
	for (auto i = id; i < v.size(); i++) {
		if (v[i] % 2 == 0 && max < v[i]) {
			max = v[i];
			id = i;
		}
	}
	return id;
}

template <typename T>
std::vector<T> binary(const std::vector<T>& vec, const T value)
{
	int left_side = 0, right_side = vec.size() - 1, mid;
	while (vec[left_side] < value && vec[right_side] > value)
	{
		mid = left_side + (right_side - left_side) * (value - vec[left_side]) / (vec[right_side] - vec[left_side]);
		if (value < vec[mid])
		{
			right_side = mid - 1;
		}
		else if (value > vec[mid])
		{
			left_side = mid + 1;
		}
		else
		{
			auto it = vec.begin();
			std::advance(it, mid);;
			return it;
		}
	}
	return vec.end();
}

template<class T>
void Shift(std::vector<T>& v) 
{
	T temp = v[v.size() - 1];
	for (int i = v.size() - 1; i > 0; i--) 
		v[i] = v[i - 1];
	v[0] = temp;
}