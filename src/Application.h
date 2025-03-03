#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include "UI.h"
#include "ApplicationCore.h"

namespace SportRoster
{
	struct ApplicationSpecification
	{
		std::uint16_t width = 120;
		std::uint16_t height = 30;
		std::string title = "SportRoster";
	};

	class Application
	{
	public:
		explicit Application(const ApplicationSpecification& spec = ApplicationSpecification());
	
	public: 
		void run();

	private:
		void applicationLoop();

		void onUpdate();
		void onRender();

	private:
		std::unique_ptr<ui::UI> m_ui;
		std::unique_ptr<core::ApplicationCore> m_appCore;
	};

} // namespace core

#endif // APPLICATION_H
