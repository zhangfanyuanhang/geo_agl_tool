#pragma once

#ifndef GTE_POLYGONS2_HPP
#define GTE_POLYGONS2_HPP

#include "Polygons.h"
#include "Polygon2.h"


//! 二维多边形区域
namespace gte {

	template <typename PointType> class Polygons2;
	using Polygons2i = Polygons2<Polygon2i>;
	using Polygons2d = Polygons2<Polygon2d>;

	template <typename PolygonType>
	class Polygons2:public Polygons<PolygonType>
	{
	public:
		typedef PolygonType polygon_type;
		using point_type = typename polygon_type::point_type;
		
		static_assert(point_type::Dim == 2, "Dimension must be 2.");
	public:
		Polygons2() = default;
		~Polygons2() = default;
		
		Polygons2(const std::list<polygon_type>& pts) :Polygons<polygon_type>(pts) {}
		Polygons2(const std::vector<polygon_type>& pts) :Polygons<polygon_type>(pts) {}
		Polygons2(std::initializer_list<polygon_type>& pts) :Polygons<polygon_type>(pts) {}
	//!重载实现
	public:
		inline const std::type_info& getType()override { return typeid(*this); }

	public:
	};


}

namespace boost {
	namespace polygon {

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
#endif // !GTE_POLYGON2_HPP

