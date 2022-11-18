#pragma once

#ifndef GTE_POLYLINES2_H
#define GTE_POLYLINES2_H

#include "Polylines.h"
#include "Polyline2.h"

namespace gte {

	template <typename PointType> class Polylines2;
	using Polylines2i = Polylines2<Polyline2i>;
	using Polylines2d = Polylines2<Polyline2d>;

	template <typename PolylineType>
	class Polylines2 :public Polylines<PolylineType>
	{
		
	public:
		typedef PolylineType polyline_type;
		using point_type = typename PolylineType::point_type;
		static_assert(point_type::Dim == 2, "Dimension must be 2.");
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

