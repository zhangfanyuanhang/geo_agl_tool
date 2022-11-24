#pragma once

#ifndef GTE_POLYGON2_HPP
#define GTE_POLYGON2_HPP

#include "Point.h"
#include "Polygon.h"

//! 二维多边形区域
namespace gte {

	template <typename PointType> class Polygon2;
	using Polygon2i = Polygon2<Point2i>;
	using Polygon2d = Polygon2<Point2d>;

	template <typename PointType>
	class Polygon2 : public Polygon<PointType>
	{
		static_assert(PointType::Dim == 2, "Dimension must be 2.");
	public:
		typedef PointType point_type;
	public:
		Polygon2() = default;
		~Polygon2() = default;

		Polygon2(const std::vector<point_type>& pts) :Polygon<point_type>(pts) {};
		Polygon2(std::initializer_list<point_type>& pts) :Polygon<point_type>(pts) {};
		Polygon2(Polygon<point_type>& ply) :Polygon<point_type>(ply) {};
	public:
		inline const std::type_info& getType()override { return typeid(*this); }

	private:
		
	};

	
}

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

	}
}
#endif // !GTE_POLYGON2_HPP

