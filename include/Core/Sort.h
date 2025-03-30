#ifndef SORT_H
#define SORT_H

#include <iterator>
#include <utility>
#include <algorithm>

namespace core::utils
{
	/// @brief Threshold for switching to insertion sort
	const int INSERTION_SORT_THRESHOLD = 16;

	/// @brief Sorts a range using insertion sort (used for small subarrays)
	/// @param first Iterator to the beginning of the range
	/// @param last Iterator to the end of the range
	/// @param comp Comparison function
	template <typename RandomIt, typename Compare>
	void insertion_sort(RandomIt first, RandomIt last, Compare comp) {
		for (RandomIt it = first + 1; it < last; ++it) {
			auto key = std::move(*it);
			RandomIt jt = it;
			while (jt > first && comp(key, *(jt - 1))) {
				*jt = std::move(*(jt - 1));
				--jt;
			}
			*jt = std::move(key);
		}
	}

	/// @brief Partitions the range around a pivot
	/// @param first Iterator to the beginning of the range
	/// @param last Iterator to the end of the range
	/// @param comp Comparison function
	/// @return Iterator pointing to the partition boundary
	template <typename RandomIt, typename Compare>
	RandomIt my_partition(RandomIt first, RandomIt last, Compare comp) {
		auto pivot = *std::next(first, std::distance(first, last) / 2);
		RandomIt left = first;
		RandomIt right = last - 1;
		while (true) {
			while (comp(*left, pivot)) ++left;
			while (comp(pivot, *right)) --right;
			if (left >= right) return right + 1;
			std::iter_swap(left, right);
			++left;
			--right;
		}
	}

	/// @brief Recursively sorts a range using quicksort
	/// @param first Iterator to the beginning of the range
	/// @param last Iterator to the end of the range
	/// @param comp Comparison function
	template <typename RandomIt, typename Compare>
	void quicksort(RandomIt first, RandomIt last, Compare comp) {
		while (std::distance(first, last) > INSERTION_SORT_THRESHOLD) {
			RandomIt pivot_pos = my_partition(first, last, comp);
			if (pivot_pos - first < last - pivot_pos) {
				quicksort(first, pivot_pos, comp);
				first = pivot_pos;
			}
			else {
				quicksort(pivot_pos, last, comp);
				last = pivot_pos;
			}
		}
		insertion_sort(first, last, comp);
	}

	/// @brief Sorts a range using quicksort with insertion sort for small subarrays
	/// @param first Iterator to the beginning of the range
	/// @param last Iterator to the end of the range
	/// @param comp Comparison function (default: std::less<>)
	template <typename RandomIt, typename Compare = std::less<>>
	void my_sort(RandomIt first, RandomIt last, Compare comp = Compare()) {
		if (first == last) return;
		quicksort(first, last, comp);
	}

} // namespace core::utils
	
#endif // SORT_H