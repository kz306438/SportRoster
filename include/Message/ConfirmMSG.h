#ifndef CONFIRM_MSG_H
#define CONFIRM_MSG_H

#include <string>
#include "Message/Message.h"
#include "buttons.h"

namespace msg
{
	using Callback = std::function<void(bool)>;

	class ConfirmMSG final : public MSG
	{
	public:
		explicit ConfirmMSG(std::uint16_t width, std::uint16_t height, Callback callback);


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
		Callback m_callback;
	
	private:
		int m_select = -1;

		std::unique_ptr<PushButton> m_PBOK;
		std::unique_ptr<PushButton> m_PBCancel;
	};

} // namespace msg

#endif // CONFIRM_MSG_H