#pragma once


#ifndef GUI_GRAPHIC2_H
#define GUI_GRAPHIC2_H

#include "Graphic.h"
#include <graphics.h>		
#include <conio.h>
#include "Base.h"
#include "Sequencers.h"

namespace gui {

	class Graphic2:public Graphic
	{
	public:
		Graphic2() = default;
		~Graphic2() = default;

		void initWindow(int width, int height) override;
		void closeWindow() override;
		void showWindow() override;

		void setData(gte::Base* data, size_t size);
		void drawPolylines();
		void drawPolygons();
	private:
		gte::Base* mpData;
		size_t size;
	};
}



#endif // !GUI_GRAPHIC_H

