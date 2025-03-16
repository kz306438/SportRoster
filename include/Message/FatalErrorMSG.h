#ifndef FATAL_ERROR_MSG_H
#define FATAL_ERROR_MSG_H

#include "Message/Message.h"
#include "buttons.h"
#include <memory>
#include "string"

namespace msg
{

	class FatalErrorMSG : public MSG
	{
	public:
		FatalErrorMSG(std::uint16_t width, std::uint16_t height);

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
		std::uint16_t m_width{};
		std::uint16_t m_height{};
		std::uint16_t m_posX{};
		std::uint16_t m_posY{};

		std::string m_title;

	private:
		std::unique_ptr<PushButton> m_PBOK;
	};
	
} // namespace msg

#endif // FATAL_ERROR_MSG_H
