#pragma once


#ifndef GUI_GRAPHIC2_H
#define GUI_GRAPHIC2_H

#include "Graphic.h"
#include <graphics.h>		
#include <conio.h>
#include "Base.h"

namespace gui {

	class Graphic2:public Graphic
	{
	public:
		Graphic2() = default;
		~Graphic2() = default;

		void initWindow(int width, int height) override;
		void closeWindow() override;
		void showWindow() override;

		void setData(gte::Base* data);
		void drawPolylines();
		void drawPolygons();

		template <typename T>
		void drawPolyline(T* data);

		template <typename T>
		void drawPolygon(T* data);
	private:
		gte::Base* mDataPtr = nullptr;
		size_t mSize = 0;
	};
}



#endif // !GUI_GRAPHIC_H

