#pragma once

#ifndef GTE_POLYGON2_HPP
#define GTE_POLYGON2_HPP

#include "Point.h"
#include "Polygon.h"
namespace gte {

	template <typename PointType> class Polygon2;
	using Polygon2i = Polygon2<Point2i>;
	using Polygon2d = Polygon2<Point2d>;

	template <typename PointType>
	class Polygon2 : public Polygon<PointType>
	{
	public:
		Polygon2() = default;
		~Polygon2() = default;

		Polygon2(const std::vector<PointType>& pts) :Polygon<PointType>(pts) {};
		Polygon2(std::initializer_list<PointType>& pts) :Polygon<PointType>(pts) {};
		Polygon2(Polygon<PointType>& ply) :Polygon<PointType>(ply) {};
	private:
		
	};

	
}

#endif // !GTE_POLYGON2_HPP

