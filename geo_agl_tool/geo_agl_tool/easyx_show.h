#pragma once

#ifndef EASYX_SHOW_H
#define EASYX_SHOW_H

#include <graphics.h>		
#include <conio.h>
#include <vector>


class EasyXShow2D
{
public:
	EasyXShow2D() {};
	~EasyXShow2D() {};

	template <typename Polygons>
	void polygons(const Polygons &polygons);
	void show();
	void setWindows(unsigned int width = 1000, unsigned int height = 1000);
	void closeWindows();
	
private:
	void showPolygons();
	std::vector<std::vector<POINT>> mPolygons;
};


#endif // !EASYX_SHOW_H

