
#include "easyx_show.hpp"

void EasyXShow2D::setWindows(unsigned int width, unsigned int height) {
	initgraph(width, height);
	//Ĭ��ֵ�����Ͻ�
	setorigin(width*0.5, height*0.5);
}
void EasyXShow2D::closeWindows() {
	_getch();
	closegraph();
}