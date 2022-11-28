#pragma once


#ifndef GUI_GRAPHIC_H
#define GUI_GRAPHIC_H

#include "PolyBase.h"

namespace gui{

	class Graphic
	{
	public:
		Graphic() = default;
		~Graphic() = default;

		virtual void initWindow(int width,int height) = 0;
		virtual void closeWindow() = 0;
		virtual void setSourceData(gte::PolyBase* data) = 0;
		virtual void show(gte::PolyBase* data) = 0;
	protected:

		int mWindowsWidth;
		int mWindowsHeight;

		gte::PolyBase* mSourcePtr;
	};

}


#endif // !GUI_GRAPHIC_H

