#pragma once

#ifndef GTE_POLYGONS2_HPP
#define GTE_POLYGONS2_HPP

#include "Polygons.h"
#include "Polygon2.h"


//! 二维多边形区域
namespace gte {

	template <typename PointType> class Polygons2;
	using Polygons2i = Polygons2<Polygon2i>;
	using Polygons2d = Polygons2<Polygon2d>;

	template <typename PolygonType>
	class Polygons2:public Polygons<PolygonType>
	{
	public:
		typedef PolygonType polygon_type;
		using point_type = typename polygon_type::point_type;
		
		static_assert(point_type::N == 2, "Dimension must be 2.");
	public:
		Polygons2() = default;
		~Polygons2() = default;
		
		Polygons2(const std::list<polygon_type>& pts) :Polygons<polygon_type>(pts) {}
		Polygons2(const std::vector<polygon_type>& pts) :Polygons<polygon_type>(pts) {}
		Polygons2(std::initializer_list<polygon_type>& pts) :Polygons<polygon_type>(pts) {}
	//!重载实现
	public:
		inline const std::type_info& getType()override { return typeid(*this); }

	public:
	};


}

#endif // !GTE_POLYGON2_HPP

