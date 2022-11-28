#pragma once

#ifndef GTE_ADAPT_POLYGONS_H
#define GTE_ADAPT_POLYGONS_H

#include <boost/geometry.hpp>
#include <boost/polygon/polygon.hpp>

#include "..\Polygons2.h"

namespace gte {
	typedef std::pair<gte::Polygons2i::iterator, gte::Polygons2i::iterator> holes_iterator;
	typedef std::pair<gte::Polygons2i::const_iterator, gte::Polygons2i::const_iterator> holes_const_iterator;
}
// Adapt gte::Polygons2i to Boost.Geometry
namespace boost {
	namespace geometry {
		namespace traits
		{
			template <>struct tag<gte::Polygons2i> { typedef polygon_tag type; };
			template<> struct ring_const_type<gte::Polygons2i> { typedef const gte::Polygon2i& type; };
			template<> struct ring_mutable_type<gte::Polygons2i> { typedef gte::Polygon2i& type; };
			template<> struct interior_const_type<gte::Polygons2i> { typedef const gte::Polygon2i type; };
			template<> struct interior_mutable_type<gte::Polygons2i> { typedef gte::Polygon2i type; };

			template<> struct exterior_ring<gte::Polygons2i>
			{
				static gte::Polygon2i& get(gte::Polygons2i& p)
				{
					return (p[0]);
				}
				static gte::Polygon2i const& get(gte::Polygons2i const& p)
				{
					return (p[0]);
				}
			};

			template<> struct interior_rings<gte::Polygons2i>
			{
				static gte::holes_iterator& get(gte::Polygons2i& p)
				{
					gte::holes_iterator aa = std::make_pair(++p.begin(), p.end());
					return aa;
				}
				static const gte::holes_const_iterator& get(gte::Polygons2i const& p)
				{
					return std::make_pair(++p.begin(), p.end());
				}
			};
		}
	}
}
namespace boost
{
	template <>
	struct range_iterator<gte::Polygons2i> { typedef gte::Polygons2i::iterator type; };

	template<>
	struct range_const_iterator<gte::Polygons2i> { typedef gte::Polygons2i::const_iterator type; };

} // namespace 'boost'


// The required Range functions. These should be defined in the same namespace
// as Ring.
namespace gte {
	inline Polygons2i::iterator range_begin(holes_iterator& r)
	{
		return r.first;
	}

	inline Polygons2i::const_iterator range_begin(holes_const_iterator& r)
	{
		return r.first;
	}

	inline Polygons2i::iterator range_end(holes_iterator& r)
	{
		return r.second;
	}

	inline Polygons2i::const_iterator range_end(holes_const_iterator& r)
	{
		return r.second;
	}
}


// Adapt gte::Polygons2i to Boost.Polygon
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
#endif // !GTE_ADAPT_POLYGONS_H

