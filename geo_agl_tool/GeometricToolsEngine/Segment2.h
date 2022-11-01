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
	private:
	};

}


#endif // !GTE_SEGMENT_H

