#pragma once


#ifndef GUI_GRAPHIC2_H
#define GUI_GRAPHIC2_H

#include "Graphic.h"
#include "graphics.h"	
#include <conio.h>
#include "GeometricToolsEngine.h"

namespace gui {

	class Graphic2:public Graphic
	{
	public:
		Graphic2() = default;
		~Graphic2() = default;

		void initWindow(int width, int height) override;
		void closeWindow() override;
		void setSourceData(gte::PolyBase* data) override;

		void show(gte::PolyBase* data)override;
		
	private:

		void drawAll();

		void drawSource();
		void drawData();

		void draw(gte::PolyBase* dataptr);

		template <typename T>
		void drawPolyline(T* data);

		template <typename T>
		void drawPolygon(T* data);

		template <typename T>
		void drawPoint(T* data);

		template <typename T>
		void drawSegment(T* data);
	private:
		gte::PolyBase* mDataPtr = nullptr;
	};
}



#endif // !GUI_GRAPHIC_H

