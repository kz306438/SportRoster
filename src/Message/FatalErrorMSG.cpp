#include "Message/FatalErrorMSG.h"

#include "UI/ConsoleManager.h"
#include "window.h"

namespace msg
{

	msg::FatalErrorMSG::FatalErrorMSG(std::uint16_t width, std::uint16_t height)
		: m_width(width), m_height(height)
	{
		init();
	}

	void FatalErrorMSG::onRender()
	{
		m_PBOK->allowChanges(); m_PBOK->show();
	}

	void FatalErrorMSG::onUpdate()
	{
		mouseButtonInteraction(m_PBOK.get());
	}

	void FatalErrorMSG::run()
	{
		renderAll();

		while (true)
		{
			onRender();
			onUpdate();
		}
	}

	void FatalErrorMSG::setPosition(std::uint16_t posX, std::uint16_t posY) {
		m_posX = posX;
		m_posY = posY;

		m_PBOK->changePosition(m_posX + m_width / 2 - 1, m_posY + m_height - 4);
	}

	void FatalErrorMSG::setTitle(const std::string& title) {
		m_title = title;
	}

	void FatalErrorMSG::init() {
		m_PBOK = std::make_unique<PushButton>(m_width / 2 - 1, 3, "OK", m_posX + m_width / 2 - 1, m_posY + m_height - 4);
		m_PBOK->setBackgroundColor(White);
		m_PBOK->setForegroundColor(Black);
		m_PBOK->connect([&]() { exit(0); });
	}

	void FatalErrorMSG::renderAll()
	{
		Window errorWindow(m_width, m_height, m_posX, m_posY);
		errorWindow.addWindowName("fatal error", 1, 0);
		errorWindow.show();

		ui::ConsoleManager::getInstance().setCursorPosition(m_width / 2 - int(m_title.size() / 2) + m_posX, m_posY + 1);
		std::cout << m_title;
	}

} // namespace msg