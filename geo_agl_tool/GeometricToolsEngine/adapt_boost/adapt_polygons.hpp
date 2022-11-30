#pragma once

#ifndef GTE_ADAPT_POLYGONS_H
#define GTE_ADAPT_POLYGONS_H

#include <boost/geometry.hpp>
#include <boost/polygon/polygon.hpp>

#include "..\Polygons2.hpp"

namespace gte {

	typedef gte::Polygons2i::iterator PolygonRingIterator;
	typedef gte::Polygons2i::const_iterator ConstPolygonRingIterator;

	class CustomPolygonRingRange
	{
		PolygonRingIterator _begin;
		PolygonRingIterator _end;

		bool isIterSet;

		ConstPolygonRingIterator _cbegin;
		ConstPolygonRingIterator _cend;

		bool isCIterSet;

	public:

		CustomPolygonRingRange(PolygonRingIterator begin, PolygonRingIterator end) : _begin(begin), _end(end), isIterSet(true) {}
		CustomPolygonRingRange(ConstPolygonRingIterator begin, ConstPolygonRingIterator end) : _cbegin(begin), _cend(end), isCIterSet(true) {}

		PolygonRingIterator begin()
		{
			assert(isIterSet);
			return _begin;
		}

		ConstPolygonRingIterator cbegin() const
		{
			assert(isCIterSet);
			return _cbegin;
		}

		PolygonRingIterator end()
		{
			assert(isIterSet);
			return _end;
		}

		ConstPolygonRingIterator cend() const
		{
			assert(isCIterSet);
			return _cend;
		}
	};

}
// Adapt gte::Polygons2i to Boost.Geometry
namespace boost {
	namespace geometry {
		namespace traits
		{
			template <>struct tag<gte::Polygons2i> { typedef polygon_tag type; };
			template<> struct ring_const_type<gte::Polygons2i> { typedef const gte::Polygon2i& type; };
			template<> struct ring_mutable_type<gte::Polygons2i> { typedef gte::Polygon2i& type; };
			template<> struct interior_const_type<gte::Polygons2i> { typedef const gte::CustomPolygonRingRange type; };
			template<> struct interior_mutable_type<gte::Polygons2i> { typedef gte::CustomPolygonRingRange type; };

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
				static gte::CustomPolygonRingRange get(gte::Polygons2i& p)
				{
					return gte::CustomPolygonRingRange(gte::PolygonRingIterator(++p.begin()), gte::PolygonRingIterator(p.end()));
				}
				static const gte::CustomPolygonRingRange get(gte::Polygons2i const& p)
				{
					return gte::CustomPolygonRingRange(gte::ConstPolygonRingIterator(++p.begin()), gte::ConstPolygonRingIterator(p.end()));
				}
			};
		}
	}
}
namespace boost
{
	template <>
	struct range_iterator<gte::CustomPolygonRingRange> { typedef gte::PolygonRingIterator type; };

	template<>
	struct range_const_iterator<gte::CustomPolygonRingRange> { typedef gte::ConstPolygonRingIterator type; };
} // namespace 'boost'


// The required Range functions. These should be defined in the same namespace
// as Ring.
namespace gte {

	inline PolygonRingIterator range_begin(CustomPolygonRingRange& r)
	{
		return r.begin();
	}

	inline ConstPolygonRingIterator range_begin(const CustomPolygonRingRange& r)
	{
		return r.cbegin();
	}

	inline PolygonRingIterator range_end(CustomPolygonRingRange& r)
	{
		return r.end();
	}

	inline ConstPolygonRingIterator range_end(const CustomPolygonRingRange& r)
	{
		return r.cend();
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

