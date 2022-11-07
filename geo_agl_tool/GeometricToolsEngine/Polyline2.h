#pragma once

#ifndef GTE_POLYLINE2_H
#define GTE_POLYLINE2_H

#include "Point.h"
#include "Polyline.h"

namespace gte {

	template <typename PointType> class PolyLine2;
	using PolyLine2i = PolyLine2<Point2i>;
	using PolyLine2d = PolyLine2<Point2d>;

	template <typename PointType>
	class PolyLine2 :public PolyLine<PointType>
	{
		static_assert(PointType::N == 2, "Dimension must be 2.");
	public:
		using  point_type = PointType;
	public:
		PolyLine2() = default;
		~PolyLine2() = default;

		PolyLine2(const std::list<point_type>& pts) :Sequencer<point_type>(pts) {}
		PolyLine2(const std::vector<point_type>& pts) :Sequencer<point_type>(pts) {}
		PolyLine2(std::initializer_list<point_type>& pts) :Sequencer<point_type>(pts) {}

	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	};

}

#endif // !GTE_POLYGON2_HPP

