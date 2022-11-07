#pragma once

#ifndef GTE_POLYGON2_HPP
#define GTE_POLYGON2_HPP

#include "Point.h"
#include "Polygon.h"

//! 二维多边形区域
namespace gte {

	template <typename PointType> class Polygon2;
	using Polygon2i = Polygon2<Point2i>;
	using Polygon2d = Polygon2<Point2d>;

	template <typename PointType>
	class Polygon2 : public Polygon<PointType>
	{
		static_assert(PointType::N == 2, "Dimension must be 2.");
	public:
		typedef PointType point_type;
	public:
		Polygon2() = default;
		~Polygon2() = default;

		Polygon2(const std::vector<point_type>& pts) :Polygon<point_type>(pts) {};
		Polygon2(std::initializer_list<point_type>& pts) :Polygon<point_type>(pts) {};
		Polygon2(Polygon<point_type>& ply) :Polygon<point_type>(ply) {};
	public:
		inline const std::type_info& getType()override { return typeid(*this); }

	private:
		
	};

	
}

#endif // !GTE_POLYGON2_HPP

