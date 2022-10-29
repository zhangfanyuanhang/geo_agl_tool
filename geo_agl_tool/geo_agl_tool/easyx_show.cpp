
#include "easyx_show.hpp"

void EasyXShow2D::setWindows(unsigned int width, unsigned int height) {
	initgraph(width, height);
	//默认值在左上角
	setorigin(width*0.5, height*0.5);
}
void EasyXShow2D::closeWindows() {
	_getch();
	closegraph();
}