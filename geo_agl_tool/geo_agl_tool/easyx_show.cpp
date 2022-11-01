
#include "easyx_show.h"
#include "Polygons2.h"
#include "Polygon2.h"

void EasyXShow2D::setWindows(unsigned int width, unsigned int height) {
	initgraph(width, height);
	//默认值在左上角
	setorigin(width*0.5, height*0.5);
}
void EasyXShow2D::closeWindows() {
	closegraph();
}

void EasyXShow2D::show()
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
			showPolygons();
			break;
		}
	}
}
void EasyXShow2D::showPolygons()
{
	cleardevice();
	for (size_t i = 0; i < mPolygons.size(); i++)
	{
		if (0 == i)
			setlinecolor(RED);
		else
			setlinecolor(YELLOW);
		polygon(&mPolygons[i][0], mPolygons[i].size());
	}
}
template <typename Polygons>
void EasyXShow2D::polygons(const Polygons &polygons)
{
	mPolygons.resize(polygons.size());
	for (size_t i = 0; i < polygons.size(); i++)
	{
		size_t pt_size = polygons[i].size();
		mPolygons[i].resize(pt_size);
		//POINT* pts = new POINT[pt_size];
		for (size_t j = 0; j < pt_size; ++j)
		{
			mPolygons[i][j] = POINT({ (LONG)polygons[i][j].x(), (LONG)polygons[i][j].y() });
		}

		//delete[]pts;
	}
}

template void EasyXShow2D::polygons(const gte::Polygons2i &polygons);
template void EasyXShow2D::polygons(const gte::Polygons2d &polygons);