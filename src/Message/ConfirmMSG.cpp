#include "Message/ConfirmMSG.h"
#include "UI/ConsoleManager.h"
#include "window.h"

namespace msg
{
	/*explicit*/ ConfirmMSG::ConfirmMSG(std::uint16_t width, std::uint16_t height, Callback callback)
		: m_width(width), m_height(height), m_callback(callback)
	{
		init();
	}

	void ConfirmMSG::onRender() /*override*/
	{
		m_PBOK->allowChanges(); m_PBOK->show();
		m_PBCancel->allowChanges(); m_PBCancel->show();
	}

	void ConfirmMSG::onUpdate() /*override*/
	{
		mouseButtonInteraction(m_PBOK.get(), m_PBCancel.get());

		if (m_select == 0) {
			m_callback(false);
			shouldClose = true;
		}
		else if (m_select == 1) {
			m_callback(true);
			shouldClose = true;
		}
	}

	void ConfirmMSG::run()
	{
		renderAll();
		while (!shouldClose)
		{
			onRender();
			onUpdate();
		}
	}

	void ConfirmMSG::setPosition(std::uint16_t posX, std::uint16_t posY) {
		m_posX = posX;
		m_posY = posY;

		m_PBOK->changePosition(m_posX + 1, m_posY + m_height - 4);
		m_PBCancel->changePosition(m_posX + m_width / 2 + 1, m_posY + m_height - 4);
	}

	void ConfirmMSG::setTitle(const std::string& title) {
		m_title = title;
	}

	void ConfirmMSG::init() {
		m_PBOK = std::make_unique<PushButton>(m_width / 2 - 1, 3, "OK", m_posX + 1, m_posY + m_height - 4);
		m_PBCancel = std::make_unique<PushButton>(m_width / 2 - 1, 3, "CANCEL", m_posX + m_width / 2 + 1, m_posY + m_height - 4);
		
		m_PBOK->connect([&]() { m_select = 1; });
		m_PBCancel->connect([&]() { m_select = 0; });

		m_PBOK->setBackgroundColor(BrightGreen);
		m_PBOK->setForegroundColor(Black);

		m_PBCancel->setBackgroundColor(BrightRed);
		m_PBCancel->setForegroundColor(Black);

		shouldClose = false;
	}

	void ConfirmMSG::renderAll()
	{
		Window dialogWindow(m_width, m_height, m_posX, m_posY);
		dialogWindow.show();

		ui::ConsoleManager::getInstance().setCursorPosition(m_width / 2 - m_title.size() / 2 + m_posX, m_posY + 1);
		std::cout << m_title;
	}

} // namespace msg