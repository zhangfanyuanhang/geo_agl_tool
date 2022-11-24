#pragma once

#ifndef GTE_SEGMENT2_H
#define GTE_SEGMENT2_H

#include "Point.h"
#include "Segment.h"

namespace gte {
	template <typename PointType> class Segment2;
	using Segment2i = Segment2<Point2i>;
	using Segment2d = Segment2<Point2d>;

	template <typename PointType>
	class Segment2:public Segment<PointType>
	{
	public:
		Segment2() = default;
		~Segment2() = default;
		Segment2(const PointType& pt0, const PointType& pt1):Segment<PointType>(pt0, pt1){};
		Segment2(Segment<PointType>& segm):Segment<PointType>(segm) {};

	private:
	};

}

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

#endif // !GTE_SEGMENT_H

