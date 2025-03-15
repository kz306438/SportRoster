#ifndef MESSAGE_H
#define MESSAGE_H

namespace msg
{

	/**
	 * @brief Base class for messages.
	 */
	class MSG
	{
	public:
		/**
		 * @brief Virtual destructor.
		 */
		virtual ~MSG() = default;

	public:
		/**
		 * @brief Handles rendering logic.
		 */
		virtual void onRender() = 0;

		/**
		 * @brief Handles update logic.
		 */
		virtual void onUpdate() = 0;
	};

} // namespace msg

#endif // MESSAGE_H
