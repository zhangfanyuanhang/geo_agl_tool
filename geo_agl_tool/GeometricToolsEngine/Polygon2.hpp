#pragma once

#ifndef GTE_POLYGON2_HPP
#define GTE_POLYGON2_HPP

#include "Point.hpp"
#include "Polygon.hpp"

///! 二维多边形构造简单封闭区域
namespace gte {
	///! 模板化特定类型的二维多边形
	template <typename CoordType> class Polygon2;
	using Polygon2i = Polygon2<int64_t>;
	using Polygon2d = Polygon2<double_t>;

	///! 二维多边形定义
	template <typename CoordType>
	class Polygon2:public Polygon<Point2<CoordType>>
	{
	public:
		typedef  Point2<CoordType> point_type;
	public:
		Polygon2() = default;
		~Polygon2() = default;
		Polygon2(const Polygon2&) = default;
		Polygon2(const std::list<point_type>& pts) :Polygon<Point2<CoordType>>(pts) {}
		Polygon2(const std::vector<point_type>& pts) :Polygon<Point2<CoordType>>(pts) {}
		Polygon2(std::initializer_list<point_type>& pts) :Polygon<Point2<CoordType>>(pts) {}

		//! 重载实现	
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	public:
		//！点在多边形内部
		inline bool within(const point_type& pt) { return boost::geometry::within(*this, pt); }
	};

}

#endif // !GTE_POLYGON2_HPP

