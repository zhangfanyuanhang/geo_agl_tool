
#include "Graphic2.h"
#include "Polylines2.h"
#include "Polyline2.h"
#include "Polygons2.h"
#include "Polygon2.h"

namespace gui {


	void Graphic2::initWindow(int width, int height)
	{
		mWindowsWidth = width;
		mWindowsHeight = height;

		initgraph(mWindowsWidth, mWindowsHeight);
		//Ĭ��ֵ�����Ͻ�
		setorigin(mWindowsWidth*0.5, mWindowsHeight*0.5);
	}
	void Graphic2::closeWindow()
	{
		closegraph();
	}

	void Graphic2::showWindow()
	{
		ExMessage msg;
		float zoom = 0;
		while (true)
		{
			msg = getmessage(EX_MOUSE);
			switch (msg.message)
			{
			case WM_MOUSEMOVE:
				break;
			case WM_LBUTTONDOWN:
				break;

			case WM_KEYDOWN:
				break;
			case WM_MOUSEWHEEL:
				zoom += msg.wheel / 120 * 0.001;
				setaspectratio(zoom, zoom);
				break;
			}
		}
	}
	void Graphic2::setData(gte::Base* data)
	{
		mDataPtr = data;
	}
	void Graphic2::drawPolylines()
	{
		if (nullptr == mDataPtr)
			return;

		const auto& type = mDataPtr->getType();
		if (type == typeid(gte::PolyLines2i))
		{
			gte::PolyLines2i* data = (gte::PolyLines2i*)mDataPtr;
			for (size_t j = 0; j < data->size(); ++j)
			{
				drawPolyline(&(*data)[j]);
			}
		}
		if (type == typeid(gte::PolyLines2d))
		{
			gte::PolyLines2d* data = (gte::PolyLines2d*)mDataPtr;
			for (size_t j = 0; j < data->size(); ++j)
			{
				drawPolyline(&(*data)[j]);
			}
		}
	}
	void Graphic2::drawPolygons()
	{
		if (nullptr == mDataPtr)
			return;

		const auto& type = mDataPtr->getType();
		if (type == typeid(gte::Polygons2i))
		{
			gte::Polygons2i* data = (gte::Polygons2i*)mDataPtr;
			for (size_t j = 0; j < data->size(); ++j)
			{
				drawPolygon(&(*data)[j]);
			}
		}
		if (type == typeid(gte::Polygons2d))
		{
			gte::Polygons2d* data = (gte::Polygons2d*)mDataPtr;
			for (size_t j = 0; j < data->size(); ++j)
			{
				drawPolygon(&(*data)[j]);
			}
		}
	}

	template <typename T>
	void Graphic2::drawPolyline(T* data)
	{
		size_t size = (*data).size();
		std::vector<POINT> pts(size);
		for (size_t k = 0; k < size; ++k)
		{
			pts[k] = { (LONG)(*data)[k].x() ,(LONG)(*data)[k].y() };
		}
		polyline(&pts[0], size);
	}
	template <typename T>
	void Graphic2::drawPolygon(T* data)
	{
		size_t size = (*data).size();
		std::vector<POINT> pts(size);
		for (size_t k = 0; k < size; ++k)
		{
			pts[k] = { (LONG)(*data)[k].x() ,(LONG)(*data)[k].y() };
		}
		polygon(&pts[0], size);
	}
	template void Graphic2::drawPolyline(gte::PolyLine2i* data);
	template void Graphic2::drawPolyline(gte::PolyLine2d* data);
	template void Graphic2::drawPolygon(gte::Polygon2i* data);
	template void Graphic2::drawPolygon(gte::Polygon2d* data);
}