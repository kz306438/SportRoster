#ifndef TUI_H
#define TUI_H

#include "UI.h"

namespace ui
{

	class TUI : public UI
	{
	public:
		void onRender() override;
		void onUpdate() override;
	};

} // namespace ui

#endif // TUI_H
