#pragma once

#ifndef GTE_CONVERTOR_H
#define GTE_CONVERTOR_H

#include "MathDefines.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Segment2.h"
#include "Polygon2.h"
#include "Polygons2.h"

namespace gte {

	inline long long convertorMM2UM(double_t x)
	{
		return static_cast<int64_t>(x*ZOOM_IN);
	}
	inline double convertorUM2MM(int64_t x)
	{
		return static_cast<double_t>(x*ZOOM_OUT);
	}
	//!
	template<typename InputType, typename OutputType>
	void pointConvertorMM2UM(const InputType& src, OutputType& dst)
	{
		size_t size = src.size();
		for (size_t i = 0; i < size; i++)
		{
			dst[i] = convertorMM2UM(src[i]);
		}
	}
	template void pointConvertorMM2UM(const Vector2d& src, Vector2i& dst);
	template void pointConvertorMM2UM(const Vector3d& src, Vector3i& dst);
	//!
	template<typename InputType, typename OutputType>
	void pointConvertorUM2MM(const InputType& src, OutputType& dst)
	{
		size_t size = src.size();
		for (size_t i = 0; i < size; i++)
		{
			dst[i] = convertorUM2MM(src[i]);
		}
	}
	template void pointConvertorUM2MM(const Vector2i& src, Vector2d& dst);
	template void pointConvertorUM2MM(const Vector3i& src, Vector3d& dst);
	//!
	template<typename InputType, typename OutputType>
	void segmentConvertorMM2UM(const InputType& src, OutputType& dst)
	{
		for (size_t i = 0; i < 2; i++)
		{
			pointConvertorMM2UM(src[i], dst[i]);
		}
	}
	template void segmentConvertorMM2UM(const Segment2d& src, Segment2i& dst);
	//!
	template<typename InputType, typename OutputType>
	void segmentConvertorUM2MM(const InputType& src, OutputType& dst)
	{
		for (size_t i = 0; i < 2; i++)
		{
			pointConvertorUM2MM(src[i], dst[i]);
		}
	}
	template void segmentConvertorUM2MM(const Segment2i& src, Segment2d& dst);

	//!
	template<typename InputType, typename OutputType>
	void polygonConvertorMM2UM(const InputType& src, OutputType& dst)
	{
		size_t size = src.size();
		dst.resize(size);
		for (size_t i = 0; i < size; i++)
		{
			pointConvertorMM2UM(src[i], dst[i]);
		}
	}
	template void polygonConvertorMM2UM(const Polygon2d& src, Polygon2i& dst);
	//!
	template<typename InputType, typename OutputType>
	void polygonConvertorUM2MM(const InputType& src, OutputType& dst)
	{
		size_t size = src.size();
		dst.resize(size);
		for (size_t i = 0; i < size; i++)
		{
			pointConvertorUM2MM(src[i], dst[i]);
		}
	}
	template void polygonConvertorUM2MM(const Polygon2i& src,Polygon2d& dst);
	//!
	template<typename InputType, typename OutputType>
	void polygonsConvertorMM2UM(const InputType& src, OutputType& dst)
	{
		size_t size = src.size();
		dst.resize(size);
		for (size_t i = 0; i < size; i++)
		{
			polygonConvertorMM2UM(src[i], dst[i]);
		}
	}
	template void polygonsConvertorMM2UM(const Polygons2d& src, Polygons2i& dst);

	//!
	template<typename InputType, typename OutputType>
	void polygonsConvertorUM2MM(const InputType& src, OutputType& dst)
	{
		size_t size = src.size();
		dst.resize(size);
		for (size_t i = 0; i < size; i++)
		{
			polygonConvertorUM2MM(src[i], dst[i]);
		}
	}
	template void polygonsConvertorUM2MM(const Polygons2i& src, Polygons2d& dst);
}


#endif // !GTE_CONVERTOR_H

