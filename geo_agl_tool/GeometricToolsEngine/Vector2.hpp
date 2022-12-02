#pragma once

#ifndef GTE_VECTOR2_HPP
#define GTE_VECTOR2_HPP

#include "Vector.hpp"

namespace gte {

	///! ģ�廯�ض����͵Ķ�ά����
	template <typename CoordType> class Vector2;
	using Vector2i = Vector2<int64_t>;
	using Vector2d = Vector2<double_t>;

	///! ��ά��������
	template <typename CoordType>
	class Vector2 : public Vector<CoordType, 2>
	{
	public:
		Vector2() = default;
		~Vector2() = default;
		Vector2(const Vector2&) = default;
		Vector2(CoordType x, CoordType y) :Vector<CoordType, 2>({x,y}) {};
		Vector2(std::initializer_list<CoordType> xy) :Vector<CoordType, 2>(xy) {};
		Vector2(const Vector<CoordType, 2>& vec) :Vector<CoordType, 2>(vec) {};

		inline const CoordType& x()const { return this->mTuple[0]; }
		inline CoordType& x() { return this->mTuple[0]; }
		inline const CoordType& y()const { return this->mTuple[1]; }
		inline CoordType& y() { return this->mTuple[1]; }


	private:

	};
	
}


#endif //GTE_POINT_HPP
