#pragma once

#ifndef GTE_POLYLINES2_H
#define GTE_POLYLINES2_H

#include "Polylines.h"

namespace gte {

	template <typename PointType> class Polylines2;
	using PolyLines2i = Polylines2<Point2i>;
	using PolyLines2d = Polylines2<Point2d>;

	template <typename PointType>
	class Polylines2 :public Polylines<PointType>
	{
		static_assert(PointType::N == 2, "Dimension must be 2.");
	public:
		typedef PointType point_type;
		using polyline_type = typename Polylines<PointType>::polyline_type;
	public:
		Polylines2() = default;
		~Polylines2() = default;

		Polylines2(const std::list<polyline_type>& pts) :Polylines<polyline_type>(pts) {}
		Polylines2(const std::vector<polyline_type>& pts) :Polylines<polyline_type>(pts) {}
		Polylines2(std::initializer_list<polyline_type>& pts) :Polylines<polyline_type>(pts) {}
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	};
}

#endif // !GTE_POLYGON2_HPP

