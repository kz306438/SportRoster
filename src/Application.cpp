#include "Application.h"

#include "UI/UIFactory.h"
#include "Core/ApplicationCore.h"
#include "UI/ConsoleManager.h"

namespace SportRoster
{

	/*explicit*/ Application::Application(const ApplicationSpecification& spec/* = ApplicationSpecification()*/)
	{
		m_appCore = std::make_shared<core::ApplicationCore>();
		m_ui = ui::UIFactory::createUI(ui::UIType::TUI, spec.width, spec.height, spec.title, *m_appCore);
	}

	void Application::run()
	{
		applicationLoop();
	}

	void Application::applicationLoop()
	{
		while (true) {
			onRender();
			onUpdate();
		}
	}

	void Application::onUpdate()
	{
		m_ui->onUpdate();
	}

	void Application::onRender()
	{
		m_ui->onRender();
	}

} // namespace SportRoster