#ifndef SORT_H
#define SORT_H

#include <iterator>
#include <utility>
#include <algorithm>

namespace core::utils
{

	/**
	 * @brief Performs quicksort on a range using iterators and a custom comparator.
	 * @tparam RandomIt Iterator type (must be random-access).
	 * @tparam Compare Comparator type.
	 * @param first Iterator to the beginning of the range.
	 * @param last Iterator to the end of the range.
	 * @param comp Comparator for element comparison.
	 */
	template <typename RandomIt, typename Compare = std::less<>()>
	void quicksort(RandomIt first, RandomIt last, Compare comp) {
		if (first >= last) return;

		auto pivot = *std::next(first, std::distance(first, last) / 2);
		RandomIt left = first, right = last - 1;

		while (left <= right) {
			while (comp(*left, pivot)) ++left;
			while (comp(pivot, *right)) --right;
			if (left <= right) {
				std::iter_swap(left, right);
				++left;
				--right;
			}
		}

		if (first < right) quicksort(first, right + 1, comp);
		if (left < last) quicksort(left, last, comp);
	}

	/**
    * @brief Performs selection sort on a range using iterators and a custom comparator.
    * @tparam ForwardIt Iterator type (must be forward-accessible).
    * @tparam Compare Comparator type.
    * @param first Iterator to the beginning of the range.
    * @param last Iterator to the end of the range.
    * @param comp Comparator for element comparison.
    */
	template <typename ForwardIt, typename Compare = std::less<>()>
	void selectionSort(ForwardIt first, ForwardIt last, Compare comp = std::less<>()) {
		for (ForwardIt it = first; it != last; ++it) {
			ForwardIt minIt = it;
			for (ForwardIt jt = std::next(it); jt != last; ++jt) {
				if (comp(*jt, *minIt)) {
					minIt = jt;
				}
			}
			if (minIt != it) {
				std::iter_swap(it, minIt);
			}
		}
	}

} // namespace core::utils
	
#endif // SORT_H