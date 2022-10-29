#pragma once

#ifndef GTE_POINT_HPP
#define GTE_POINT_HPP

#include "Vector2.h"
#include "Vector3.h"

namespace gte {

	using Point2i = Vector2<long>;
	using Point2d = Vector2<double>;

	using Point3i = Vector3<long>;
	using Point3d = Vector3<double>;

	/*template<typename PointType1, typename PointType2>
	void convertPointMM2UM(const PointType1& pti, PointType2& ptd)
	{
		static_assert(PointType1::dim == PointType2::dim)
		;
	}
	template<typename PointType1, typename PointType2>
	void convertPointUM2MM(const PointType1& pti, PointType2& ptd)
	{
		;
	}*/
}


#endif //GTE_POINT_HPP