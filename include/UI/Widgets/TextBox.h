#ifndef WIDGET_TEXT_BOX
#define WIDGET_TEXT_BOX

#include <memory>
#include "buttons.h"
namespace ui::widgets
{

	using Content = std::vector<std::string>;

	class TextBox
	{
	public:
		TextBox(std::uint16_t width, std::uint16_t height);
		TextBox(std::uint16_t width, std::uint16_t height, std::uint16_t posX, std::uint16_t posY);

	public:
		void onRender();
		void onUpdate();
	
		void renderAll();

		[[nodiscard]] std::unique_ptr<PushButton>& getUpButton();
		[[nodiscard]] std::unique_ptr<PushButton>& getDownButton();

	public:
		void setContent(const Content& content);
		void displayText();
	
	public:
		void moveUp();
		void moveDown();

	private:
		void init();

	private:
		static const int MIN_ELEMENT_WIDTH = 3;
		static const int MIN_ELEMENT_HEIGHT = 3;

	protected:
		int m_shift{};

	protected:
		std::uint16_t m_width{};
		std::uint16_t m_height{};
		std::uint16_t m_posX{};
		std::uint16_t m_posY{};

	protected:
		Content m_content;

	private:
		std::unique_ptr<PushButton> m_PBUp;
		std::unique_ptr<PushButton> m_PBDown;
	};

} // namespace ui::widgets

#endif // WIDGET_TEXT_BOX
