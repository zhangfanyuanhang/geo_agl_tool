#pragma once

#ifndef GTE_POLYLINE_H
#define GTE_POLYLINE_H

#include "Point.h"
#include "Sequencer.h"

namespace gte {

	template <typename PointType>
	class Polyline :public Sequencer<PointType>
	{
	public:
		using  point_type = PointType;
	public:
		Polyline() = default;
		~Polyline() = default;

		Polyline(const std::list<point_type>& pts) :Sequencer<point_type>(pts) {}
		Polyline(const std::vector<point_type>& pts) :Sequencer<point_type>(pts) {}
		Polyline(std::initializer_list<point_type>& pts):Sequencer<point_type>(pts){}

	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	};

}

#endif // !GTE_POLYGON2_HPP

