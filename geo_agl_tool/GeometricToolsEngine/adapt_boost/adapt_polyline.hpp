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
			// adapt gte::Polygon2i for Boost.Geometry
			template<> struct tag<gte::Polyline2i>
			{
				typedef linestring_tag type;
			};
			template <> struct clear<gte::Polyline2i>
			{
				static inline void apply(gte::Polyline2i& data)
				{
					data.clear();
				}
			};
			template <> struct push_back<gte::Polyline2i>
			{
				static inline void apply(gte::Polyline2i& data, gte::Polyline2i::point_type& pt)
				{
					data.push_back(pt);
				}
			};
			template <> struct resize<gte::Polyline2i>
			{
				static inline void apply(gte::Polyline2i& data, std::size_t new_size)
				{
					data.resize(new_size);
				}
			};
			// adapt gte::Polygon2d for Boost.Geometry
			template<> struct tag<gte::Polyline2d>
			{
				typedef ring_tag type;
			};
			template <> struct clear<gte::Polyline2d>
			{
				static inline void apply(gte::Polyline2d& data)
				{
					data.clear();
				}
			};
			template <> struct push_back<gte::Polyline2d>
			{
				static inline void apply(gte::Polyline2d& data, gte::Polyline2d::point_type& pt)
				{
					data.push_back(pt);
				}
			};
			template <> struct resize<gte::Polyline2d>
			{
				static inline void apply(gte::Polyline2d& data, std::size_t new_size)
				{
					data.resize(new_size);
				}
			};
		}
	}
}
// Boost.Range for gte::Polygon2i
namespace boost
{
	// adapt gte::Polygon2i for Boost.Range
	template<> struct range_mutable_iterator<gte::Polyline2i>
	{
		typedef gte::Polyline2i::iterator type;
	};
	template<> struct range_const_iterator<gte::Polyline2i>
	{
		typedef gte::Polyline2i::const_iterator type;
	};
	template<> struct range_size<gte::Polyline2i>
	{
		typedef std::size_t type;
	};
	// adapt gte::Polygon2d for Boost.Range
	template<> struct range_mutable_iterator<gte::Polyline2d>
	{
		typedef gte::Polyline2d::iterator type;
	};
	template<> struct range_const_iterator<gte::Polyline2d>
	{
		typedef gte::Polyline2d::const_iterator type;
	};
	template<> struct range_size<gte::Polyline2d>
	{
		typedef std::size_t type;
	};
}
namespace gte {
	// adapt gte::Polygon2i for Boost.Range
	inline gte::Polyline2i::iterator range_begin(gte::Polyline2i& ply) { return ply.begin(); }
	inline gte::Polyline2i::iterator range_end(gte::Polyline2i& ply) { return ply.end(); }
	inline gte::Polyline2i::const_iterator range_begin(const gte::Polyline2i& ply) { return ply.begin(); }
	inline gte::Polyline2i::const_iterator range_end(const gte::Polyline2i& ply) { return ply.end(); }
	inline std::size_t range_calculate_size(const gte::Polyline2i& ply) { return ply.size(); }
	// adapt gte::Polygon2d for Boost.Range
	inline gte::Polyline2d::iterator range_begin(gte::Polyline2d& ply) { return ply.begin(); }
	inline gte::Polyline2d::iterator range_end(gte::Polyline2d& ply) { return ply.end(); }
	inline gte::Polyline2d::const_iterator range_begin(const gte::Polyline2d& ply) { return ply.begin(); }
	inline gte::Polyline2d::const_iterator range_end(const gte::Polyline2d& ply) { return ply.end(); }
	inline std::size_t range_calculate_size(const gte::Polyline2d& ply) { return ply.size(); }
}

#endif // !GTE_ADAPT_POLYLINE_HPP

