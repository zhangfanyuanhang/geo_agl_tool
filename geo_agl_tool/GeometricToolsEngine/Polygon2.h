#pragma once

#ifndef GTE_POLYGON2_HPP
#define GTE_POLYGON2_HPP

#include "Point.h"
#include "Polygon.h"

//! 二维多边形区域
namespace gte {

	using Polygon2i = Polygon<Point2i>;
	using Polygon2d = Polygon<Point2d>;

}

#endif // !GTE_POLYGON2_HPP

