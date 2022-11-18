#pragma once

#ifndef GTE_POLYLINE2_H
#define GTE_POLYLINE2_H

#include "Point.h"
#include "Polyline.h"

namespace gte {

	template <typename PointType> class Polyline2;
	using Polyline2i = Polyline2<Point2i>;
	using Polyline2d = Polyline2<Point2d>;

	template <typename PointType>
	class Polyline2 :public Polyline<PointType>
	{
		static_assert(PointType::Dim == 2, "Dimension must be 2.");
	public:
		using  point_type = PointType;
	public:
		Polyline2() = default;
		~Polyline2() = default;

		Polyline2(const std::list<point_type>& pts) :Sequencer<point_type>(pts) {}
		Polyline2(const std::vector<point_type>& pts) :Sequencer<point_type>(pts) {}
		Polyline2(std::initializer_list<point_type>& pts) :Sequencer<point_type>(pts) {}

	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	};

}

#endif // !GTE_POLYGON2_HPP

