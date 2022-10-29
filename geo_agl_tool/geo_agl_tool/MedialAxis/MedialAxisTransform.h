#pragma once

#ifndef MAT_MEDIAL_AXIS_TRANSFORM_H
#define MAT_MEDIAL_AXIS_TRANSFORM_H

#include "Polygons2.h"

class MedialAxisTransform
{
public:
	MedialAxisTransform(const gte::Polygons2i& plys);
	~MedialAxisTransform();

private:
	gte::Polygons2i mPolygons;
};


#endif // !MAT_MEDIAL_AXIS_TRANSFORM_H

