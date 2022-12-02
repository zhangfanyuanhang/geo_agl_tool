#pragma once

#ifndef GTE_VECTOR3_HPP
#define GTE_VECTOR3_HPP

#include "Vector.hpp"

namespace gte {
	///! 模板化特定类型的三维向量
	template <typename CoordType> class Vector3;
	using Vector3i = Vector3<int64_t>;
	using Vector3d = Vector3<double_t>;
	
	///! 三维向量定义
	template <typename CoordType>
	class Vector3 : public Vector<CoordType, 3>
	{
	public:	
		Vector3() = default;
		~Vector3() = default;
		Vector3(const Vector3&) = default;
		Vector3(CoordType x, CoordType y, CoordType z) :Vector<CoordType, 3>({x,y,z}) {};
		Vector3(std::initializer_list<CoordType> xyz) :Vector<CoordType, 3>(xyz) {};
		Vector3(Vector<CoordType, 3>& vec) :Vector<CoordType, 3>(vec) {};

		inline const CoordType& x()const { return this->mTuple[0]; }
		inline CoordType& x() { return this->mTuple[0]; }
		inline const CoordType& y()const { return this->mTuple[1]; }
		inline CoordType& y() { return this->mTuple[1]; }
		inline const CoordType& z()const { return this->mTuple[2]; }
		inline CoordType& z() { return this->mTuple[2]; }
	private:

	};
	//! 向量叉积，只适用3维。
	template <typename T>
	T Cross(T const& v0, T const& v1)
	{
		static_assert(T::Dim == 3,"Dimension must be 3.");

		T result;
		result.makeZero();
		result[0] = v0[1] * v1[2] - v0[2] * v1[1];
		result[1] = v0[2] * v1[0] - v0[0] * v1[2];
		result[2] = v0[0] * v1[1] - v0[1] * v1[0];
		return result;
	}

	//template Vector3i Cross(Vector3i const& v0, Vector3i const& v1);
	//template Vector3d Cross(Vector3d const& v0, Vector3d const& v1);
}


#endif //GTE_POINT_HPP
