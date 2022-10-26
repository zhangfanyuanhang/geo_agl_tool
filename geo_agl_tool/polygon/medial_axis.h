#pragma once

#ifndef POLYGON_MEDIAL_AXIS_H
#define POLYGON_MEDIAL_AXIS_H

#include <geometric_primitive.h>
#include <boost/polygon/polygon.hpp>


using gp::Point2d;
using gp::Segment2d;
using gp::Polygon2d;
using gp::Polygons2d;

namespace boost {
	namespace polygon {
		template <>
		struct geometry_concept<Point2d> { typedef point_concept type; };

		template <>
		struct point_traits<Point2d> {
			typedef int coordinate_type;

			static inline coordinate_type get(const Point2d& point, orientation_2d orient) {
				return (orient == HORIZONTAL) ? point.x : point.y;
			}
		};
		template <>
		struct point_mutable_traits<Point2d> {
			typedef int coordinate_type;

			static inline void set(Point2d& point, orientation_2d orient, int value) {
				if (orient == HORIZONTAL)
					point.x = value;
				else
					point.y = value;
			}
			static inline Point2d construct(int x_value, int y_value) {
				return Point2d(x_value, y_value);
			}
		};

		template <>
		struct geometry_concept<Segment2d> { typedef segment_concept type; };
		template <>
		struct segment_traits<Segment2d> {
			typedef typename int coordinate_type;
			typedef typename Segment2d::point_type point_type;

			static inline point_type get(const Segment2d& segment, direction_1d dir) {
				return dir.to_int() ? segment.p1 : segment.p0;
			}
		};

		template <>
		struct segment_mutable_traits<Segment2d> {
			typedef typename int coordinate_type;
			typedef typename Segment2d::point_type point_type;

			static inline void set(Segment2d& segment, direction_1d dir, const point_type& point) {
				if (dir.to_int())
				{
					segment.p1 = point;
				}
				else {
					segment.p0 = point;
				}
			}

			static inline Segment2d construct(const point_type& low, const point_type& high) {
				return Segment2d(low, high);
			}
		};

		//first register Polygon as a polygon_concept type
		template <>
		struct geometry_concept<Polygon2d> { typedef polygon_concept type; };

		template <>
		struct polygon_traits<Polygon2d> {
			typedef int coordinate_type;
			typedef Polygon2d::const_iterator iterator_type;
			typedef Point2d point_type;
			// Get the begin iterator
			static inline iterator_type begin_points(const Polygon2d& t) {
				return t.begin();
			}

			// Get the end iterator
			static inline iterator_type end_points(const Polygon2d& t) {
				return t.end();
			}

			// Get the number of sides of the polygon
			static inline std::size_t size(const Polygon2d& t) {
				return t.size();
			}

			// Get the winding direction of the polygon
			static inline winding_direction winding(const Polygon2d& t) {
				return unknown_winding;
			}
		};

		template <>
		struct polygon_mutable_traits<Polygon2d> {
			//expects stl style iterators
			template <typename iT>
			static inline Polygon2d& set_points(Polygon2d& t,
				iT input_begin, iT input_end) {
				t.clear();
				t.insert(t.end(), input_begin, input_end);
				return t;
			}

		};

		template <>
		struct geometry_concept<Polygons2d> { typedef polygon_set_concept type; };

		//next we map to the concept through traits
		template <>
		struct polygon_set_traits<Polygons2d> {
			typedef int coordinate_type;
			typedef Polygons2d::const_iterator iterator_type;
			typedef Polygons2d operator_arg_type;
			
			static inline iterator_type begin(const Polygons2d& polygon_set) {
				return polygon_set.begin();
			}

			static inline iterator_type end(const Polygons2d& polygon_set) {
				return polygon_set.end();
			}

			//don't worry about these, just return false from them
			static inline bool clean(const Polygons2d& polygon_set) { return false; }
			static inline bool sorted(const Polygons2d& polygon_set) { return false; }
		};

		template <>
		struct polygon_set_mutable_traits<Polygons2d> {
			template <typename input_iterator_type>
			static inline void set(Polygons2d& polygon_set, input_iterator_type input_begin, input_iterator_type input_end) {
				polygon_set.clear();
				//this is kind of cheesy. I am copying the unknown input geometry
				//into my own polygon set and then calling get to populate the
				//deque
				polygon_set_data<int> ps;
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

