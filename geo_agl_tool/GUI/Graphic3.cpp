
#include "Graphic3.h"


namespace gui {

	void Graphic3::initWindow(int width, int height)
	{
		mWindowsWidth = width;
		mWindowsHeight = height;

	}
	void Graphic3::closeWindow()
	{
	}
	void Graphic3::setSourceData(gte::PolyBase* data)
	{
		mSourcePtr = data;
	}
	void Graphic3::show(gte::PolyBase* data)
	{

	}

}