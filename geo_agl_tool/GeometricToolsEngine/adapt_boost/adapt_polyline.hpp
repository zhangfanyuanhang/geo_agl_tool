#pragma once
#ifndef GTE_ADAPT_POLYLINE_HPP
#define GTE_ADAPT_POLYLINE_HPP

#include <boost/geometry.hpp>
#include <boost/polygon/polygon.hpp>

#include "..\Polyline2.h"

// Adapt gte::Polygon2i to Boost.Geometry
namespace boost {
	namespace geometry {
		namespace traits
		{
			template<> struct tag<gte::Polyline2i>
			{
				typedef linestring_tag type;
			};

		}
	}
}
// Boost.Range for gte::Polygon2i
namespace boost
{
	template <>
	struct range_iterator<gte::Polyline2i>
	{
		typedef gte::Polyline2i::iterator type;
	};

	template<>
	struct range_const_iterator<gte::Polyline2i>
	{
		typedef gte::Polyline2i::const_iterator type;
	};
	template<>
	struct range_size<gte::Polyline2i>
	{
		typedef std::size_t type;
	};
}
namespace gte {
	inline gte::Polyline2i::iterator
		range_begin(Polyline2i& ply) { return ply.begin(); }

	inline gte::Polyline2i::iterator
		range_end(Polyline2i& ply) { return ply.end(); }

	inline gte::Polyline2i::const_iterator
		range_begin(const Polyline2i& ply) { return ply.begin(); }

	inline gte::Polyline2i::const_iterator
		range_end(const Polyline2i& ply) { return ply.end(); }

	inline std::size_t range_calculate_size(const gte::Polyline2i& ply) { return ply.size(); }
}

#endif // !GTE_ADAPT_POLYLINE_HPP

