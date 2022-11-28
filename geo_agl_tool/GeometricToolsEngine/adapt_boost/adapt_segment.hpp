#pragma once

#ifndef GTE_ADAPT_SEGMENT_HPP
#define GTE_ADAPT_SEGMENT_HPP

#include <boost/geometry.hpp>
#include <boost/polygon/polygon.hpp>

#include "..\Segment2.h"
/// ------------------------------------------
// Adapt gte::Segment2i to Boost.Geometry
namespace boost {
	namespace geometry {
		namespace traits
		{
			template <>struct tag<gte::Segment2i>
			{
				typedef segment_tag type;
			};

			template <>struct point_type<gte::Segment2i>
			{
				typedef gte::Segment2i::point_type type;
			};

			template <std::size_t Dimension>
			struct indexed_access<gte::Segment2i, 0, Dimension>
			{
				typedef gte::Segment2i segment_type;
				typedef typename gte::Segment2i::point_type::coord_type coordinate_type;

				static constexpr coordinate_type get(segment_type const& s)
				{
					return geometry::get<Dimension>(s.p0());
				}

				static void set(segment_type& s, coordinate_type const& value)
				{
					geometry::set<Dimension>(s.p0(), value);
				}
			};
			template <std::size_t Dimension>
			struct indexed_access<gte::Segment2i, 1, Dimension>
			{
				typedef gte::Segment2i segment_type;
				typedef typename gte::Segment2i::point_type::coord_type coordinate_type;

				static constexpr coordinate_type get(segment_type const& s)
				{
					return geometry::get<Dimension>(s.p1());
				}

				static void set(segment_type& s, coordinate_type const& value)
				{
					geometry::set<Dimension>(s.p1(), value);
				}
			};
		}
	}
}
// Adapt gte::Segment2i to Boost.Polygon
namespace boost {
	namespace polygon {
		template <>
		struct geometry_concept<gte::Segment2i> { typedef segment_concept type; };
		template <>
		struct segment_traits<gte::Segment2i> {
			typedef typename int64_t coordinate_type;
			typedef typename gte::Segment2i::point_type point_type;

			static inline point_type get(const gte::Segment2i& segment, direction_1d dir) {
				return dir.to_int() ? segment.p1() : segment.p0();
			}
		};

		template <>
		struct segment_mutable_traits<gte::Segment2i> {
			typedef typename int64_t coordinate_type;
			typedef typename gte::Segment2i::point_type point_type;

			static inline void set(gte::Segment2i& segment, direction_1d dir, const point_type& point) {
				if (dir.to_int())
				{
					segment.p1() = point;
				}
				else {
					segment.p0() = point;
				}
			}

			static inline gte::Segment2i construct(const point_type& low, const point_type& high) {
				return gte::Segment2i(low, high);
			}
		};
	}
}
#endif // !GTE_ADAPT_SEGMENT_HPP

