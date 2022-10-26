#pragma once

#ifndef GEOMETRIC_PRIMITIVE_H
#define GEOMETRIC_PRIMITIVE_H

#include <list>

namespace gp
{
	struct Point2d {
		int x;
		int y;
		Point2d(int a, int b) : x(a), y(b) {}
	};
	struct Segment2d {
		typedef Point2d point_type;
		point_type p0;
		point_type p1;
		Segment2d(const point_type& tp0, const point_type& tp1) :p0(tp0),p1(tp1) {}
	};
	struct Polygon2d
	{
		typedef std::list<Point2d>::const_iterator const_iterator;
		
		inline const_iterator begin() const { return polygon.begin(); }
		inline const_iterator end() const { return polygon.end(); }
		inline std::size_t size()const { return polygon.size(); }

		typedef std::list<Point2d>::iterator iterator;
		inline iterator begin() { return polygon.begin(); }
		inline iterator end() { return polygon.end(); }

		template< class InputIt >
		iterator insert(const_iterator pos, InputIt first, InputIt last) {  return polygon.insert(pos,first,last); }

		std::list<Point2d> polygon;
	};

	struct Polygons2d
	{
		typedef std::list<Polygon2d>::const_iterator const_iterator;

		inline const_iterator begin() const { return polygons.begin(); }
		inline const_iterator end() const { return polygons.end(); }
		inline std::size_t size()const { return polygons.size(); }

		typedef std::list<Polygon2d>::iterator iterator;
		inline iterator begin() { return polygons.begin(); }
		inline iterator end() { return polygons.end(); }

		void clear() { polygons.clear(); }
		std::list<Polygon2d> polygons;
	};
}
#endif // !GEOMETRIC_PRIMITIVE_H

