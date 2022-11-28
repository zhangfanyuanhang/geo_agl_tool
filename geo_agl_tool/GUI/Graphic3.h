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
		void setSourceData(gte::PolyBase* data) override;
		void show(gte::PolyBase* data)override;
	private:
		gte::PolyBase* mDataPtr = nullptr;
	};

}


#endif // !GUI_GRAPHIC_H

