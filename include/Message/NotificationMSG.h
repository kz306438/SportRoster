#ifndef NOTIFICATION_MESSAGE_H
#define NOTIFICATION_MESSAGE_H

#include "Message/Message.h"
#include "buttons.h"

#include <memory>
#include <string>
namespace msg
{

	class NotificationMSG final : public MSG
	{
	public:
		NotificationMSG(std::uint16_t width, std::uint16_t height);

	public:
		void onRender() override;
		void onUpdate() override;

		void run();

	public:
		void setPosition(std::uint16_t posX, std::uint16_t posY);
		void setTitle(const std::string& title);

	private:
		void init();
		void renderAll();

	private:
		bool shouldClose;

	private:
		std::uint16_t m_width{};
		std::uint16_t m_height{};
		std::uint16_t m_posX{};
		std::uint16_t m_posY{};

		std::string m_title;

	private:
		int m_select = -1;

		std::unique_ptr<PushButton> m_PBOK;
	};

} // namespace msg

#endif // NOTIFICATION_MESSAGE_H
