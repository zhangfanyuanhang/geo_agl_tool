#pragma once


#ifndef GUI_GRAPHIC_H
#define GUI_GRAPHIC_H

namespace {

	class Graphic
	{
	public:
		Graphic() = default;
		~Graphic() = default;

		virtual void initWindow(int width,int height) = 0;
		virtual void closeWindow() = 0;
		virtual void showWindow() = 0;
	protected:

		int mWindowsWidth;
		int mWindowsHeight;
	};

}


#endif // !GUI_GRAPHIC_H

