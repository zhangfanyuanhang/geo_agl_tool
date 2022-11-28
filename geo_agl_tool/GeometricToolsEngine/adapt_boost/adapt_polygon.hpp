#pragma once

#ifndef GTE_ADAPT_POLYGON_HPP
#define GTE_ADAPT_POLYGON_HPP

#include <boost/geometry.hpp>
#include <boost/polygon/polygon.hpp>

#include "..\Polygon2.h"
/// ----------------------------------------------------------------------------

// Adapt gte::Polygon2i to Boost.Geometry
// Adaption: implement iterator and range-extension, and register with Boost.Geometry

namespace boost {
	namespace geometry {
		namespace traits
		{
			// adapt gte::Polygon2i for Boost.Geometry
			template<> struct tag<gte::Polygon2i>
			{
				typedef ring_tag type;
			};
			template <> struct clear<gte::Polygon2i>
			{
				static inline void apply(gte::Polygon2i& data)
				{
					data.clear();
				}
			};
			template <> struct push_back<gte::Polygon2i>
			{
				static inline void apply(gte::Polygon2i& data, gte::Polygon2i::point_type& pt)
				{
					data.push_back(pt);
				}
			};
			template <> struct resize<gte::Polygon2i>
			{
				static inline void apply(gte::Polygon2i& data, std::size_t new_size)
				{
					data.resize(new_size);
				}
			};
			// adapt gte::Polygon2d for Boost.Geometry
			template<> struct tag<gte::Polygon2d>
			{
				typedef ring_tag type;
			};
			template <> struct clear<gte::Polygon2d>
			{
				static inline void apply(gte::Polygon2d& data)
				{
					data.clear();
				}
			};
			template <> struct push_back<gte::Polygon2d>
			{
				static inline void apply(gte::Polygon2d& data, gte::Polygon2d::point_type& pt)
				{
					data.push_back(pt);
				}
			};
			template <> struct resize<gte::Polygon2d>
			{
				static inline void apply(gte::Polygon2d& data, std::size_t new_size)
				{
					data.resize(new_size);
				}
			};
		}
	}
}
// Boost.Range
namespace boost
{
	// adapt gte::Polygon2i for Boost.Range
	template<> struct range_mutable_iterator<gte::Polygon2i>
	{
		typedef gte::Polygon2i::iterator type;
	};
	template<> struct range_const_iterator<gte::Polygon2i>
	{
		typedef gte::Polygon2i::const_iterator type;
	};
	template<> struct range_size<gte::Polygon2i>
	{
		typedef std::size_t type;
	};
	// adapt gte::Polygon2d for Boost.Range
	template<> struct range_mutable_iterator<gte::Polygon2d>
	{
		typedef gte::Polygon2d::iterator type;
	};
	template<> struct range_const_iterator<gte::Polygon2d>
	{
		typedef gte::Polygon2d::const_iterator type;
	};
	template<> struct range_size<gte::Polygon2d>
	{
		typedef std::size_t type;
	};
}
// Boost.Range
namespace gte {
	// adapt gte::Polygon2i for Boost.Range
	inline gte::Polygon2i::iterator range_begin(gte::Polygon2i& ply) { return ply.begin(); }
	inline gte::Polygon2i::iterator range_end(gte::Polygon2i& ply) { return ply.end(); }
	inline gte::Polygon2i::const_iterator range_begin(const gte::Polygon2i& ply) { return ply.begin(); }
	inline gte::Polygon2i::const_iterator range_end(const gte::Polygon2i& ply) { return ply.end(); }
	inline std::size_t range_calculate_size(const gte::Polygon2i& ply) { return ply.size(); }
	// adapt gte::Polygon2d for Boost.Range
	inline gte::Polygon2d::iterator range_begin(gte::Polygon2d& ply) { return ply.begin(); }
	inline gte::Polygon2d::iterator range_end(gte::Polygon2d& ply) { return ply.end(); }
	inline gte::Polygon2d::const_iterator range_begin(const gte::Polygon2d& ply) { return ply.begin(); }
	inline gte::Polygon2d::const_iterator range_end(const gte::Polygon2d& ply) { return ply.end(); }
	inline std::size_t range_calculate_size(const gte::Polygon2d& ply) { return ply.size(); }
}


/// --------------------------------------------------------------
// Adapt gte::Polygon2i to Boost.Polygon
namespace boost {
	namespace polygon {
		//first register Polygon as a polygon_concept type
		template <>
		struct geometry_concept<gte::Polygon2i> { typedef polygon_concept type; };

		template <>
		struct polygon_traits<gte::Polygon2i> {
			typedef int64_t coordinate_type;
			typedef gte::Polygon2i::const_iterator iterator_type;
			typedef gte::Polygon2i point_type;
			// Get the begin iterator
			static inline iterator_type begin_points(const gte::Polygon2i& t) {
				return t.begin();
			}

			// Get the end iterator
			static inline iterator_type end_points(const gte::Polygon2i& t) {
				return t.end();
			}

			// Get the number of sides of the polygon
			static inline std::size_t size(const gte::Polygon2i& t) {
				return t.size();
			}

			// Get the winding direction of the polygon
			static inline winding_direction winding(const gte::Polygon2i& t) {
				return unknown_winding;
			}
		};

		template <>
		struct polygon_mutable_traits<gte::Polygon2i> {
			//expects stl style iterators
			template <typename iT>
			static inline gte::Polygon2i& set_points(gte::Polygon2i& t,
				iT input_begin, iT input_end) {
				t.clear();
				t.insert(t.end(), input_begin, input_end);
				return t;
			}

		};

		//
		template <>
		struct geometry_concept<gte::Polygon2d> { typedef polygon_concept type; };

		template <>
		struct polygon_traits<gte::Polygon2d> {
			typedef int64_t coordinate_type;
			typedef gte::Polygon2d::const_iterator iterator_type;
			typedef gte::Polygon2d point_type;
			// Get the begin iterator
			static inline iterator_type begin_points(const gte::Polygon2d& t) {
				return t.begin();
			}

			// Get the end iterator
			static inline iterator_type end_points(const gte::Polygon2d& t) {
				return t.end();
			}

			// Get the number of sides of the polygon
			static inline std::size_t size(const gte::Polygon2d& t) {
				return t.size();
			}

			// Get the winding direction of the polygon
			static inline winding_direction winding(const gte::Polygon2d& t) {
				return unknown_winding;
			}
		};

		template <>
		struct polygon_mutable_traits<gte::Polygon2d> {
			//expects stl style iterators
			template <typename iT>
			static inline gte::Polygon2d& set_points(gte::Polygon2d& t,
				iT input_begin, iT input_end) {
				t.clear();
				t.insert(t.end(), input_begin, input_end);
				return t;
			}

		};
	}
}
#endif // !GTE_ADAPT_POLYGON_HPP

