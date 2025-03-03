#ifndef MENU_H
#define MENU_H

namespace menu
{

	class Menu
	{
	public:
		virtual ~Menu() = default;

	public:
		virtual void onRender() = 0;
		virtual void onUpdate() = 0;
	};

} // namespace menu

#endif // MENU_H

