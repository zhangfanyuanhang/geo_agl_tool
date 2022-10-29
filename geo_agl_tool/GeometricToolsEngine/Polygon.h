#pragma once

#ifndef GTE_POLYGON_HPP
#define GTE_POLYGON_HPP

#include <vector>
#include "Point.h"
namespace gte {
	template <typename PointType>
	class Polygon
	{
	public:
		typedef PointType point_type;
		typedef typename std::vector<point_type>::const_iterator const_iterator;
		typedef typename std::vector<point_type>::iterator iterator;
	public:
		Polygon() {};
		~Polygon() {};
		
		Polygon(const std::vector<point_type>& pts) :mPolygon(pts) {}
		Polygon(std::initializer_list<point_type>& pts) {
			if (size_t size = pts.size())
			{
				std::copy(pts, pts + size, mPolygon.begin());
			}
		}
		inline void add(point_type pt) { mPolygon.push_back(pt); }
		inline size_t size()const { return mPolygon.size(); }
		
		inline const point_type& operator[](size_t i)const { return mPolygon[i]; }
		inline point_type& operator[](size_t i) { return mPolygon[i]; }

		inline const_iterator begin() const { return mPolygon.begin(); }
		inline const_iterator end() const { return mPolygon.end(); }

		inline iterator begin() { return mPolygon.begin(); }
		inline iterator end() { return mPolygon.end(); }

		template< class InputIt >
		iterator insert(const_iterator pos, InputIt first, InputIt last) { return mPolygon.insert(pos, first, last); }

		inline void clear() { mPolygon.clear(); }
	private:
		std::vector<point_type> mPolygon;
	};
	
}

#endif // !GTE_POLYGON2_HPP

