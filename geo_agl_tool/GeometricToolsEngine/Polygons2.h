#pragma once

#ifndef GTE_POLYGONS2_HPP
#define GTE_POLYGONS2_HPP

#include "Polygon2.h"
#include "Polygons.h"
namespace gte {

	template <typename PolygonType> class Polygons2;
	using Polygons2i = Polygons2<Polygon2i>;
	using Polygons2d = Polygons2<Polygon2d>;

	template <typename PolygonType>
	class Polygons2:public Polygons<PolygonType>
	{
	public:
		Polygons2() {};
		~Polygons2() {};

		Polygons2(const std::vector<PolygonType>& pts) :Polygons<PolygonType>(pts) {}
		Polygons2(std::initializer_list<PolygonType>& pts) :Polygons<PolygonType>(pts) {}
		
	private:
	};


}

#endif // !GTE_POLYGON2_HPP

