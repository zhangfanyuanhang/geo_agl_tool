#pragma once

#ifndef MAT_MEDIAL_AXIS_TRANSFORM_H
#define MAT_MEDIAL_AXIS_TRANSFORM_H

#include "Polygons2.h"
#include "boost_polygon.h"
#include "boost/polygon/voronoi.hpp"

using boost::polygon::voronoi_builder;
using boost::polygon::voronoi_diagram;

class MedialAxisTransform
{
	
public:
	MedialAxisTransform(const gte::Polygons2i& plys);
	~MedialAxisTransform();

	void ConstructVoronoi();
private:
	gte::Polygons2i mPolygons;
};


#endif // !MAT_MEDIAL_AXIS_TRANSFORM_H

