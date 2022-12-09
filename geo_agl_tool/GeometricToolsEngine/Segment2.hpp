#pragma once

#ifndef GTE_SEGMENT2_HPP
#define GTE_SEGMENT2_HPP

#include "Point.hpp"
#include "Segment.hpp"

namespace gte {

	///! 模板化特定类型的二维线段
	template <typename CoordType> class Segment2;
	using Segment2i = Segment2<int64_t>;
	using Segment2d = Segment2<double_t>;

	///! 二维线段定义
	template <typename CoordType>
	class Segment2 :public Segment<Point2<CoordType>>
	{
	public:
		typedef Point2<CoordType> point_type;
	public:
		Segment2() = default;
		~Segment2() = default;
		Segment2(const Segment2&) = default;
		Segment2(const point_type& pt0, const point_type& pt1):Segment<point_type>(pt0,pt1){}
		Segment2(std::initializer_list<point_type> segm):Segment<point_type>(segm) {}

		Segment2(const Segment<point_type>& segm) :Segment<point_type>(segm) {}
	};
}

#endif // !GTE_SEGMENT_H

