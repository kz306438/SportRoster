#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include "UI.h"
#include "IApplicationCore.h"

namespace SportRoster
{
	struct Specifications
	{

	} specifications;

	class Application
	{
	public:
		explicit Application(const Specifications& spec = specifications);
	
		void onUpdate();
		void onRender();

	private:
		std::unique_ptr<ui::UI> m_ui;
		std::unique_ptr<core::IApplicationCore> m_appCore;
	};

} // namespace core

#endif // APPLICATION_H
