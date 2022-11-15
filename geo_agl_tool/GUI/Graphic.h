#pragma once


#ifndef GUI_GRAPHIC_H
#define GUI_GRAPHIC_H

#include "Base.h"

namespace gui{

	class Graphic
	{
	public:
		Graphic() = default;
		~Graphic() = default;

		virtual void initWindow(int width,int height) = 0;
		virtual void closeWindow() = 0;
		virtual void setSourceData(gte::Base* data) = 0;
		virtual void show(gte::Base* data) = 0;
	protected:

		int mWindowsWidth;
		int mWindowsHeight;

		gte::Base* mSourcePtr;
	};

}


#endif // !GUI_GRAPHIC_H

