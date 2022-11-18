
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
	void Graphic2::setSourceData(gte::Base* data)
	{
		mSourcePtr = data;
	}
	void Graphic2::show(gte::Base* data)
	{
		mDataPtr = data;
		drawAll();

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
				drawAll();
				break;
			}
		}
	}
	void Graphic2::drawAll()
	{
		cleardevice();

		drawSource();
		drawData();

	}
	///
	void Graphic2::drawSource()
	{
		setlinecolor(RGB(255, 0, 0));
		draw(mSourcePtr);
	}
	void Graphic2::drawData()
	{
		setlinecolor(RGB(255, 255, 255));
		draw(mDataPtr);
	}
	void Graphic2::draw(gte::Base* dataptr)
	{
		if (nullptr == dataptr)
			return;

		const auto& type = dataptr->getType();
		if (type == typeid(gte::Polyline2i))
		{
			gte::Polyline2i* data = (gte::Polyline2i*)dataptr;
			drawPolyline(data);
		}
		if (type == typeid(gte::Polyline2d))
		{
			gte::Polyline2d* data = (gte::Polyline2d*)dataptr;
			drawPolyline(data);
		}
		if (type == typeid(gte::Polylines2i))
		{
			gte::Polylines2i* data = (gte::Polylines2i*)dataptr;
			for (size_t j = 0; j < data->size(); ++j)
			{
				drawPolyline(&(*data)[j]);
			}
		}
		if (type == typeid(gte::Polylines2d))
		{
			gte::Polylines2d* data = (gte::Polylines2d*)dataptr;
			for (size_t j = 0; j < data->size(); ++j)
			{
				drawPolyline(&(*data)[j]);
			}
		}

		if (type == typeid(gte::Polygon2i))
		{
			gte::Polygon2i* data = (gte::Polygon2i*)dataptr;
			drawPolygon(data);
		}
		if (type == typeid(gte::Polygon2d))
		{
			gte::Polygon2d* data = (gte::Polygon2d*)dataptr;
			drawPolygon(data);
		}
		if (type == typeid(gte::Polygons2i))
		{
			gte::Polygons2i* data = (gte::Polygons2i*)dataptr;
			for (size_t j = 0; j < data->size(); ++j)
			{
				drawPolygon(&(*data)[j]);
			}
		}
		if (type == typeid(gte::Polygons2d))
		{
			gte::Polygons2d* data = (gte::Polygons2d*)dataptr;
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
		if (size)
		{
			std::vector<POINT> pts(size);
			for (size_t k = 0; k < size; ++k)
			{
				pts[k] = { (LONG)(*data)[k].x() ,(LONG)(*data)[k].y() };
			}
			polyline(&pts[0], size);
		}
		
	}
	template <typename T>
	void Graphic2::drawPolygon(T* data)
	{
		size_t size = (*data).size();
		if (size)
		{
			std::vector<POINT> pts(size);
			for (size_t k = 0; k < size; ++k)
			{
				pts[k] = { (LONG)(*data)[k].x() ,(LONG)(*data)[k].y() };
			}
			polygon(&pts[0], size);
		}
	}
	template void Graphic2::drawPolyline(gte::Polyline2i* data);
	template void Graphic2::drawPolyline(gte::Polyline2d* data);
	template void Graphic2::drawPolygon(gte::Polygon2i* data);
	template void Graphic2::drawPolygon(gte::Polygon2d* data);
}