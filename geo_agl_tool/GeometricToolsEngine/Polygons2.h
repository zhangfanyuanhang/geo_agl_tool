#pragma once

#ifndef GTE_POLYGONS2_HPP
#define GTE_POLYGONS2_HPP

#include "Polygons.h"


//! 二维多边形区域
namespace gte {

	template <typename PointType> class Polygons2;
	using Polygons2i = Polygons2<Point2i>;
	using Polygons2d = Polygons2<Point2d>;

	template <typename PointType>
	class Polygons2:public Polygons<PointType>
	{
		static_assert(PointType::N == 2,"Dimension must be 2.");
	public:
		typedef PointType point_type;
		using polygon_type = typename Polygons<PointType>::polygon_type;
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

