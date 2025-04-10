#ifndef UTILS_H
#define UTILS_H

#include <optional>
#include "Player.h"
#include "Team.h"

namespace core
{

	namespace utils
	{
		using PlayerDataList = std::vector<std::string>; ///< A list of strings representing player data.
		using TeamDataList = std::vector<std::string>; ///< A list of strings representing team data.

		/**
		 * @brief Finds the first element in the range [first, last) that is not less than the given value.
		 *
		 * This function implements a binary search using a one-sided comparator.
		 * It returns an iterator pointing to the first element in the range for which
		 * `!comp(*it, value)` is true (i.e., the first element that is not less than `value`).
		 *
		 * The comparator must define a strict weak ordering, typically through a "less than" comparison.
		 *
		 * @tparam ForwardIt Forward iterator type (must meet the requirements of ForwardIterator).
		 * @tparam T Type of the searched value.
		 * @tparam Compare Type of the comparison function object, satisfying the form comp(a, b) == a < b.
		 *
		 * @param first Iterator to the beginning of the range.
		 * @param last Iterator to the end of the range.
		 * @param value Value to compare the elements to.
		 * @param comp Comparison function that returns true if the first argument is less than the second.
		 * @return Iterator pointing to the first element not less than value, or last if all elements are less.
		 */

		template<class ForwardIt, class T, class Compare>
		[[nodiscard]] constexpr ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
		{
			using category = typename std::iterator_traits<ForwardIt>::iterator_category;
			static_assert(std::is_base_of_v<std::forward_iterator_tag, category>,
				"lower_bound requires at least forward iterators");

			using difference_type = typename std::iterator_traits<ForwardIt>::difference_type;

			difference_type count = std::distance(first, last);
			ForwardIt it;

			while (count > 0) {
				difference_type step = count / 2;
				it = first;
				std::advance(it, step);

				if (comp(*it, value)) {
					first = std::next(it);
					count -= step + 1;
				}
				else {
					count = step;
				}
			}
			return first;
		}


		/**
		 * @brief Converts a Player object to a text representation.
		 *
		 * This function serializes a Player object to a list of strings.
		 *
		 * @param player The Player object to convert.
		 * @return PlayerDataList A list of strings representing the player's data.
		 */
		[[nodiscard]] PlayerDataList playerToText(const Player& player);

		/**
		 * @brief Converts a Team object to a text representation.
		 *
		 * This function serializes a Team object to a list of strings representing all players in the team.
		 *
		 * @param team The Team object to convert.
		 * @return TeamDataList A list of strings representing the team's data.
		 */
		[[nodiscard]] TeamDataList teamToText(const Team& team);

		/**
		 * @brief Converts a list of text data into a Player object.
		 *
		 * This function deserializes a list of strings into a Player object.
		 *
		 * @param dataList The list of strings representing player data.
		 * @return Player The Player object created from the given data.
		 */
		[[nodiscard]] Player textToPlayer(const PlayerDataList& dataList);

		/**
		 * @brief Converts a list of text data into a Team object.
		 *
		 * This function deserializes a list of strings into a Team object.
		 *
		 * @param teamname The name of the team.
		 * @param dataList The list of strings representing the team's data.
		 * @return Team The Team object created from the given data.
		 */
		[[nodiscard]] Team textToTeam(const std::string& teamname, const TeamDataList& dataList);

		/**
		 * @brief Adds labels to a team's data fields.
		 *
		 * This function takes a list of player data and adds labels (e.g., "Name: ", "Game Number: ")
		 * to each field, making the data more readable.
		 *
		 * @param dataList The list of strings representing raw player data.
		 * @return TeamDataList A list of labeled strings with field names prefixed.
		 */
		[[nodiscard]] TeamDataList teamToLabeledText(const TeamDataList& dataList);

		/**
		 * @brief Removes labels from a team's labeled data fields.
		 *
		 * This function reverses the effect of teamToLabeledText by stripping field names
		 * from each entry, leaving only the raw player data.
		 *
		 * @param labeledDataList The list of labeled strings.
		 * @return TeamDataList A list of raw player data without labels.
		 */
		[[nodiscard]] TeamDataList textToTeamDataList(const TeamDataList& labeledDataList);

		/**
		 * @brief Removes the ".txt" extension from the filename if present.
		 * @param filename The original filename.
		 * @return Filename without the ".txt" extension.
		 */
		[[nodiscard]] std::string removeTxtExtension(const std::string& filename);

		/**
		 * @brief Calculates the average age of all players in a team.
		 *
		 * This function computes the average age of the players in the given team.
		 *
		 * @param team The team whose players' ages will be averaged.
		 * @return double The average age of the players in the team.
		 */
		[[nodiscard]] double averageAgeOfTeam(const Team& team);

		/**
		 * @brief Calculates the average height of all players in a team.
		 *
		 * This function computes the average height of the players in the given team.
		 *
		 * @param team The team whose players' heights will be averaged.
		 * @return double The average height of the players in the team.
		 */
		[[nodiscard]] double averageHeightOfTeam(const Team& team);

		/**
		 * @brief Calculates the average weight of all players in a team.
		 *
		 * This function computes the average weight of the players in the given team.
		 *
		 * @param team The team whose players' weights will be averaged.
		 * @return double The average weight of the players in the team.
		 */
		[[nodiscard]] double averageWeightOfTeam(const Team& team);


	} // namespace utils

} // namespace core

#endif // UTILS_H
