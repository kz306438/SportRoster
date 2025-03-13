#ifndef EDIT_BOX_H
#define EDIT_BOX_H

#include <vector>
#include <string>
#include <memory>

#include "GUI.h"

namespace ui
{
	
	class EditBox
	{
	public:
		EditBox(std::uint16_t width,
			std::uint16_t height,
			std::uint16_t posX,
			std::uint16_t posY);


	private:
		std::vector<std::string> m_currentContent;

	private:

		std::uint16_t m_height;    // Height of the edit box (in lines)
		std::uint16_t m_width;     // Width of the edit box (in characters)
		std::uint16_t m_positionX; // X position of the edit box on the console
		std::uint16_t m_positionY; // Y position of the edit box on the console
	};

} // namespace ui

#endif // EDIT_BOX_H
