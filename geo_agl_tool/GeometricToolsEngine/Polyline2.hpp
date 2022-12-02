#pragma once

#ifndef GTE_POLYLINE2_HPP
#define GTE_POLYLINE2_HPP

#include "Point.hpp"
#include "Polyline.hpp"
#include "Polygon2.hpp"


///! 二维多折线
namespace gte {

	///! 模板化特定类型的二维多折线
	template <typename CoordType> class Polyline2;
	using Polyline2i = Polyline2<int64_t>;
	using Polyline2d = Polyline2<double_t>;

	///! 二维多折线定义
	template <typename CoordType>
	class Polyline2 :public Polyline<Point2<CoordType>>
	{
	public:
		typedef Point2<CoordType> point_type;

	public:
		Polyline2() = default;
		~Polyline2() = default;
		Polyline2(const Polyline2&) = default;

		Polyline2(const std::list<point_type>& pts) :Polyline<point_type>(pts) {}
		Polyline2(const std::vector<point_type>& pts) :Polyline<point_type>(pts) {}
		Polyline2(std::initializer_list<point_type>& pts) :Polyline<point_type>(pts) {}
		template <typename Iter>
		Polyline2(const Iter begin, const Iter end) : Polyline<point_type>(begin, end) {}
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	};
}



#endif // !GTE_POLYGON2_HPP

