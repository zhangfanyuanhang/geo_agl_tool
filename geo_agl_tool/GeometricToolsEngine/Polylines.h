#pragma once

#ifndef GTE_POLYLINES_H
#define GTE_POLYLINES_H

#include "Polyline.h"

namespace gte {

	/*template <typename PointType> class Polylines;
	using PolyLines2i = Polylines<Point2i>;
	using PolyLines2d = Polylines<Point2d>;
	using PolyLines3i = Polylines<Point3i>;
	using PolyLines3d = Polylines<Point3d>;*/

	template <typename PointType>
	class Polylines :public Sequencer<PolyLine<PointType>>
	{
	public:
		typedef PointType point_type;
		typedef PolyLine<PointType> polyline_type;
	public:
		Polylines() = default;
		~Polylines() = default;

		Polylines(const std::list<polyline_type>& pts) :Sequencer<polyline_type>(pts) {}
		Polylines(const std::vector<polyline_type>& pts) :Sequencer<polyline_type>(pts) {}
		Polylines(std::initializer_list<polyline_type>& pts) :Sequencer<polyline_type>(pts) {}
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	};
}

#endif // !GTE_POLYGON2_HPP

