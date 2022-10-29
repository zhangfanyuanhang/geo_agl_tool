#pragma once

#ifndef GTE_VECTOR_HPP
#define GTE_VECTOR_HPP

#include <algorithm>
#include <array>
#include <initializer_list>

namespace gte {

	template <typename CoordType,size_t Dim>
	class Vector
	{
		typedef  CoordType coord_type;
	public:
		Vector() = default;
		~Vector() {};
		Vector(std::array<coord_type, Dim> const& values):mTuple(values)
		{
		}
		Vector(std::initializer_list<coord_type> values)
		{
			size_t const num = values.size();
			if (Dim == num)
			{
				std::copy(values.begin(), values.end(), mTuple.begin());
			}
			else if (Dim > num)
			{
				std::copy(values.begin(), values.end(), mTuple.begin());
				std::fill(mTuple.begin() + num, mTuple.end(), (coord_type)0);
			}
			else // Dim < num
			{
				std::copy(values.begin(), values.begin() + Dim, mTuple.begin());
			}
		}
		
		inline std::array<coord_type, Dim> data()const { return mTuple; }
		inline size_t size() const
		{
			return Dim;
		}

		inline coord_type const& operator[](size_t i) const
		{
			return mTuple[i];
		}

		inline coord_type& operator[](size_t i)
		{
			return mTuple[i];
		}

	protected:
		std::array<coord_type, Dim> mTuple;

	};
	
	
} //namespace gte
#endif // !GTE_VECTOR_HPP

