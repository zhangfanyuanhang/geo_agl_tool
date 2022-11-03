#pragma once

#ifndef GTE_POLYGONS_HPP
#define GTE_POLYGONS_HPP

#include "Polygon.h"

namespace gte {

	template <typename PolygonType>
	class Polygons
	{
	public:
		typedef typename PolygonType::point_type point_type;
		typedef PolygonType polygon_type;
		typedef typename std::vector<polygon_type>::const_iterator const_iterator;
		typedef typename std::vector<polygon_type>::iterator iterator;
	public:
		Polygons() = default;
		~Polygons() = default;
		
		Polygons(const std::vector<polygon_type>& pts) :mPolygons(pts) {}
		Polygons(std::initializer_list<polygon_type>& pts) {
			if (size_t size = pts.size())
			{
				std::copy(pts, pts + size, mPolygons.begin());
			}
		}
		inline void add(polygon_type ply) { mPolygons.push_back(ply); }
		inline size_t size()const { return mPolygons.size(); }
		inline void resize(size_t size) { mPolygons.resize(size); }

		inline const polygon_type& operator[](size_t i)const { return mPolygons[i]; }
		inline polygon_type& operator[](size_t i) { return mPolygons[i]; }

		inline const_iterator begin() const { return mPolygons.begin(); }
		inline const_iterator end() const { return mPolygons.end(); }

		inline iterator begin() { return mPolygons.begin(); }
		inline iterator end() { return mPolygons.end(); }

		template< class InputIt >
		iterator insert(const_iterator pos, InputIt first, InputIt last) { return mPolygons.insert(pos, first, last); }

		inline void clear() { mPolygons.clear(); }

		void AABB(BoundingBox<point_type>& aabb) { mPolygons[0].AABB(aabb);}
		
		template <typename DestIt>
		void Segments(DestIt* iter) {
			std::for_each(mPolygons.begin(), mPolygons.end(), 
				[&iter](polygon_type& ply) {ply.Segments(iter); });
			
		}
	private:
		std::vector<polygon_type> mPolygons;
	};
}

#endif // !GTE_POLYGON2_HPP

