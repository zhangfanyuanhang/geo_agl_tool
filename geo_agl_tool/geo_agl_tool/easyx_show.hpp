#pragma once

#ifndef EASYX_SHOW_H
#define EASYX_SHOW_H

#include <graphics.h>		
#include <conio.h>


class EasyXShow2D
{
public:
	EasyXShow2D() {};
	~EasyXShow2D() {};

	template <typename Polygons>
	void polygons(const Polygons &polygons);

	void setWindows(unsigned int width = 1000, unsigned int height = 1000);
	void closeWindows();
private:
	
};

template <typename Polygons>
void EasyXShow2D::polygons(const Polygons &polygons)
{
	for (size_t i = 0; i < polygons.size(); i++)
	{
		size_t pt_size = polygons[i].size();
		POINT* pts = new POINT[pt_size];
		for (size_t j = 0; j < pt_size; ++j)
		{
			pts[j] = POINT({ (LONG)polygons[i][j].x(), (LONG)polygons[i][j].y() });
		}
		if (0 == i)
			setlinecolor(RED);
		else
			setlinecolor(YELLOW);
		polygon(pts, pt_size);
		delete[]pts;
	}
}

#endif // !EASYX_SHOW_H

