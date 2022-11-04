#pragma once


#ifndef GUI_GRAPHIC3_H
#define GUI_GRAPHIC3_H

#include "Graphic.h"

namespace gui {
	class Graphic3 :public Graphic
	{
	public:
		Graphic3() = default;
		~Graphic3() = default;

		void initWindow(int width, int height) override;
		void closeWindow() override;
		void showWindow() override;
	private:

	};

}


#endif // !GUI_GRAPHIC_H

