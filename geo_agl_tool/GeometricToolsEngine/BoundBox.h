#pragma once

#ifndef GTE_BOUND_BOX_H
#define GTE_BOUND_BOX_H


#include "Point.h"

namespace gte {

	template <typename T>
	class BoundingBox
	{
	public:
		T mMinPoint;
		T mMaxPoint;
	};

	template<typename PointType>
	void AxiallyAlignedBoundingBox(const PointType* points, size_t size, BoundingBox<PointType>& aabb)
	{
		if (points && size > 0)
		{
			aabb.mMinPoint = points[0];
			aabb.mMaxPoint = aabb.mMinPoint;
			for (int j = 1; j < size; ++j)
			{
				PointType const& vec = points[j];
				for (int i = 0; i < PointType::Dim; ++i)
				{
					if (vec[i] < aabb.mMinPoint[i])
					{
						aabb.mMinPoint[i] = vec[i];
					}
					else if (vec[i] > aabb.mMaxPoint[i])
					{
						aabb.mMaxPoint[i] = vec[i];
					}
				}
			}
		}
	}

	template<typename PointType>
	void ObjectOrientedBoundingBox() {}
}


#endif // !GTE_BOUND_BOX_H
