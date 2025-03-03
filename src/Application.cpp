#include "Application.h"

#include "UIFactory.h"
#include "ApplicationCore.h"

namespace SportRoster
{

	Application::Application(const ApplicationSpecification& spec/* = ApplicationSpecification()*/)
	{
		m_appCore = std::make_unique<core::ApplicationCore>();
		m_ui = ui::UIFactory::createUI(ui::UIType::TUI, spec.width, spec.height, spec.title, *m_appCore);
	}

	void Application::run()
	{
		applicationLoop();
	}

	void Application::applicationLoop()
	{
		while (true) {
			onUpdate();
			onRender();
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