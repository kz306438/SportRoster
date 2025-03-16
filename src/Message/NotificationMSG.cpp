#include "Message/NotificationMSG.h"
#include "UI/ConsoleManager.h"
#include "window.h"

namespace msg
{

	NotificationMSG::NotificationMSG(std::uint16_t width, std::uint16_t height)
		: m_width(width), m_height(height)
	{
		init();
	}

	void NotificationMSG::onRender()
	{
		m_PBOK->allowChanges(); m_PBOK->show();
	}

	void NotificationMSG::onUpdate()
	{
		mouseButtonInteraction(m_PBOK.get());

	}

	void NotificationMSG::run()
	{
		renderAll();

		while (!shouldClose)
		{
			onRender();
			onUpdate();
		}
	}

	void NotificationMSG::setPosition(std::uint16_t posX, std::uint16_t posY) {
		m_posX = posX;
		m_posY = posY;

		m_PBOK->changePosition(m_posX + m_width / 2 - 1, m_posY + m_height - 4);
	}

	void NotificationMSG::setTitle(const std::string& title) {
		m_title = title;
	}

	void NotificationMSG::init()
	{
		m_PBOK = std::make_unique<PushButton>(m_width / 2 - 1, 3, "OK", m_posX + m_width / 2 - 1, m_posY + m_height - 4);
		m_PBOK->setBackgroundColor(White);
		m_PBOK->setForegroundColor(Black);
		m_PBOK->connect([&]() { shouldClose = true; });

		shouldClose = false;
	}

	void NotificationMSG::renderAll()
	{
		Window notificationWindow(m_width, m_height, m_posX, m_posY);
		notificationWindow.addWindowName("notification", 1, 0);
		notificationWindow.show();

		ui::ConsoleManager::getInstance().setCursorPosition(m_width / 2 - m_title.size() / 2 + m_posX, m_posY + 1);
		std::cout << m_title;
	}

} // namespace msg