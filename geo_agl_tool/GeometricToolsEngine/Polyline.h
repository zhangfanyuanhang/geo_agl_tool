#pragma once

#ifndef GTE_POLYLINE_H
#define GTE_POLYLINE_H

#include <vector>
#include "Sequencer.h"

namespace gte {

	template <typename PointType> class PolyLine;
	using PolyLine2i = PolyLine<Point2i>;
	using PolyLine2d = PolyLine<Point2d>;
	using PolyLine3i = PolyLine<Point3i>;
	using PolyLine3d = PolyLine<Point3d>;

	template <typename PointType>
	class PolyLine :public Sequencer<PointType>
	{
	public:
		using  point_type = typename Sequencer<PointType>::point_type;
	public:
		PolyLine() = default;
		~PolyLine() = default;

		PolyLine(const std::vector<point_type>& pts) :Squencer<point_type>(pts) {}
		PolyLine(std::initializer_list<point_type>& pts):Squencer<point_type>(pts){}

	};

}

#endif // !GTE_POLYGON2_HPP

