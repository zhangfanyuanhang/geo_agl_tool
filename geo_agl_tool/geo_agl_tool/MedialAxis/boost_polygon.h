#pragma once

#ifndef MAT_BOOST_POLYGON_H
#define MAT_BOOST_POLYGON_H

#include "Point.h"
#include "Segment2.h"
#include "Polygon2.h"
#include "Polygons2.h"

#include <boost/polygon/polygon.hpp>

namespace boost {
	namespace polygon {
		template <>
		struct geometry_concept<gte::Point2i> { typedef point_concept type; };

		template <>
		struct point_traits<gte::Point2i> {
			typedef int64_t coordinate_type;

			static inline coordinate_type get(const gte::Point2i& point, orientation_2d orient) {
				return (orient == HORIZONTAL) ? point.x() : point.y();
			}
		};
		template <>
		struct point_mutable_traits<gte::Point2i> {
			typedef int64_t coordinate_type;

			static inline void set(gte::Point2i& point, orientation_2d orient, int value) {
				if (orient == HORIZONTAL)
					point.x() = value;
				else
					point.y() = value;
			}
			static inline gte::Point2i construct(int x_value, int y_value) {
				return gte::Point2i(x_value, y_value);
			}
		};

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

		template <>
		struct geometry_concept<gte::Polygons2i> { typedef polygon_set_concept type; };

		//next we map to the concept through traits
		template <>
		struct polygon_set_traits<gte::Polygons2i> {
			typedef int64_t coordinate_type;
			typedef gte::Polygons2i::const_iterator iterator_type;
			typedef gte::Polygons2i operator_arg_type;
			
			static inline iterator_type begin(const gte::Polygons2i& polygon_set) {
				return polygon_set.begin();
			}

			static inline iterator_type end(const gte::Polygons2i& polygon_set) {
				return polygon_set.end();
			}

			//don't worry about these, just return false from them
			static inline bool clean(const gte::Polygons2i& polygon_set) { return false; }
			static inline bool sorted(const gte::Polygons2i& polygon_set) { return false; }
		};

		template <>
		struct polygon_set_mutable_traits<gte::Polygons2i> {
			template <typename input_iterator_type>
			static inline void set(gte::Polygons2i& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
				polygon_set.clear();
				//this is kind of cheesy. I am copying the unknown input geometry
				//into my own polygon set and then calling get to populate the
				//deque
				polygon_set_data<int64_t> ps;
				ps.insert(input_begin, input_end);
				ps.get(polygon_set);
				//if you had your own odd-ball polygon set you would probably have
				//to iterate through each polygon at this point and do something
				//extra
			}
		};
	}
}


#endif // !POLYGON_MEDIAL_AXIS_H

