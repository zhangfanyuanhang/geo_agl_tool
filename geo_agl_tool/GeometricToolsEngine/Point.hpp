#pragma once

#ifndef GTE_POINT_HPP
#define GTE_POINT_HPP

#include "MathDefines.h"
#include "Vector2.hpp"
#include "Vector3.hpp"

///! 点结构数据，使用代数几何里面的向量数据结构
///! 点的意义和向量的意义一致。
namespace gte {
	///! 二维点定义
	template <typename CoordType>
	using Point2 = Vector2<CoordType>;
	///! 三维点定义
	template <typename CoordType>
	using Point3 = Vector3<CoordType>;
	///! 模板化特定类型的二维点
	using Point2i = Point2<int64_t>;
	using Point2d = Point2<double_t>;
	///! 模板化特定类型的三维点
	using Point3i = Point3<int64_t>;
	using Point3d = Point3<double_t>;

}

#endif //GTE_POINT_HPP
