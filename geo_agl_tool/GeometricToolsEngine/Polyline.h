#pragma once

#ifndef GTE_POLYLINE_H
#define GTE_POLYLINE_H

#include "Point.h"
#include "Sequencer.h"

namespace gte {

	/*template <typename PointType> class PolyLine;
	using PolyLine2i = PolyLine<Point2i>;
	using PolyLine2d = PolyLine<Point2d>;
	using PolyLine3i = PolyLine<Point3i>;
	using PolyLine3d = PolyLine<Point3d>;*/

	template <typename PointType>
	class PolyLine :public Sequencer<PointType>
	{
	public:
		using  point_type = PointType;
	public:
		PolyLine() = default;
		~PolyLine() = default;

		PolyLine(const std::list<point_type>& pts) :Sequencer<point_type>(pts) {}
		PolyLine(const std::vector<point_type>& pts) :Sequencer<point_type>(pts) {}
		PolyLine(std::initializer_list<point_type>& pts):Sequencer<point_type>(pts){}

	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	};

}

#endif // !GTE_POLYGON2_HPP

