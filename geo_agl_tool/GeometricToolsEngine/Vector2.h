#pragma once

#ifndef GTE_VECTOR2_HPP
#define GTE_VECTOR2_HPP

#include "Vector.h"

namespace gte {

	template <typename CoordType> class Vector2;
	using Vector2i = Vector2<int64_t>;
	using Vector2d = Vector2<double_t>;


	template <typename CoordType>
	class Vector2 : public Vector<CoordType, 2>
	{
	public:
		Vector2() = default;
		~Vector2() = default;
		Vector2(CoordType x, CoordType y) :Vector<CoordType, 2>({x,y}) {};
		Vector2(std::initializer_list<CoordType> xy) :Vector<CoordType, 2>(xy) {};

		inline const CoordType& x()const { return (*this)[0]; }
		inline CoordType& x() { return (*this)[0]; }
		inline const CoordType& y()const { return (*this)[1]; }
		inline CoordType& y() { return (*this)[1]; }
	private:

	};

	
	
}


#endif //GTE_POINT_HPP
