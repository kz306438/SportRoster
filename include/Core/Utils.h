#ifndef UTILS_H
#define UTILS_H

#include <optional>
#include "Player.h"
#include "Team.h"
#include "ApplicationCore.h"

namespace core
{

	namespace utils
	{
		/**
		 * @brief Binary search that returns an iterator to the found element or last if not found.
		 *
		 * @tparam ForwardIt Iterator type (requires at least ForwardIterator).
		 * @tparam T Type of the searched value (default: value_type from iterator).
		 * @tparam Compare Comparator function object.
		 *
		 * @param first Iterator to the beginning of the range.
		 * @param last Iterator to the end of the range.
		 * @param value Value to search for.
		 * @param comp Comparison function (default: std::less<>).
		 * @return Iterator to the found element or last if not found.
		 */
		template<class ForwardIt, class T = typename std::iterator_traits<ForwardIt>::value_type,
			class Compare = std::less<>>
			[[nodiscard]] constexpr ForwardIt binary_search(ForwardIt first, ForwardIt last, const T& value, Compare comp = Compare()) {
			using category = typename std::iterator_traits<ForwardIt>::iterator_category;
			static_assert(std::is_base_of_v<std::forward_iterator_tag, category>,
				"binary_search requires at least forward iterators");

			typename std::iterator_traits<ForwardIt>::difference_type count = std::distance(first, last);

			while (count > 0) {
				auto half = count / 2;
				ForwardIt mid = first;
				std::advance(mid, half);

				if (comp(*mid, value)) {
					first = std::next(mid);
					count -= half + 1;
				}
				else if (comp(value, *mid)) {
					count = half;
				}
				else {
					return mid;
				}
			}
			return last;
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
