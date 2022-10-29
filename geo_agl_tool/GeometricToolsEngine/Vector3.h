#pragma once

#ifndef GTE_VECTOR3_HPP
#define GTE_VECTOR3_HPP

#include "Vector.h"

namespace gte {

	template <typename CoordType> class Vector3;
	using Vector3i = Vector3<long>;
	using Vector3d = Vector3<double>;

	template <typename CoordType>
	class Vector3 : public Vector<CoordType, 3>
	{
	public:	
		Vector3() :Vector<CoordType, 3>() {};
		~Vector3() {};
		Vector3(CoordType x, CoordType y, CoordType z) :Vector<CoordType, 3>({x,y,z}) {};
		Vector3(std::initializer_list<CoordType> xyz) :Vector<CoordType, 3>(xyz) {};

		inline const CoordType& x()const { return (*this)[0]; }
		inline CoordType& x() { return (*this)[0]; }
		inline const CoordType& y()const { return (*this)[1]; }
		inline CoordType& y() { return (*this)[1]; }
		inline const CoordType& z()const { return (*this)[2]; }
		inline CoordType& z() { return (*this)[2]; }
	private:

	};

	using Vector3d = Vector3<double>;

}


#endif //GTE_POINT_HPP
