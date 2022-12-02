#pragma once

#ifndef GTE_SEGMENT_HPP
#define GTE_SEGMENT_HPP

#include <array>

namespace gte {

	template <typename PointType>
	class Segment
	{
	public:
		typedef PointType point_type;
	public:
		Segment() = default;
		~Segment() = default;
		Segment(const Segment&) = default;
		Segment(const point_type& pt0, const point_type& pt1){
			mPoints[0] = pt0;
			mPoints[1] = pt1;
		}
		Segment(std::initializer_list<point_type> segm) {
			std::copy(segm.begin(), segm.end(), mPoints.begin());
		}

		inline const point_type& p0()const { return mPoints[0]; }
		inline point_type& p0() { return mPoints[0]; }

		inline const point_type& p1()const { return mPoints[1]; }
		inline point_type& p1() { return mPoints[1]; }

		inline const point_type& operator[](size_t i)const { return mPoints[i]; }
		inline point_type& operator[](size_t i) { return mPoints[i]; }

		inline point_type toVector()const { return mPoints[1]- mPoints[0]; }
	private:
		std::array<point_type,2> mPoints;
	};
}



#endif // !GTE_SEGMENT_H

