#pragma once

#ifndef GTE_POINT_HPP
#define GTE_POINT_HPP

#include "MathDefines.h"
#include "Vector2.hpp"
#include "Vector3.hpp"

///! ��ṹ���ݣ�ʹ�ô�������������������ݽṹ
///! ������������������һ�¡�
namespace gte {
	///! ��ά�㶨��
	template <typename CoordType>
	using Point2 = Vector2<CoordType>;
	///! ��ά�㶨��
	template <typename CoordType>
	using Point3 = Vector3<CoordType>;
	///! ģ�廯�ض����͵Ķ�ά��
	using Point2i = Point2<int64_t>;
	using Point2d = Point2<double_t>;
	///! ģ�廯�ض����͵���ά��
	using Point3i = Point3<int64_t>;
	using Point3d = Point3<double_t>;

}

#endif //GTE_POINT_HPP
