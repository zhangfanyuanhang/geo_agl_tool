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
	public:
		typedef  CoordType coord_type;
		static const  size_t N = Dim;
	public:
		Vector() = default;
		~Vector() = default;
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

		// Comparisons for sorted containers and geometric ordering.
		inline bool operator==(Vector const& vec) const
		{
			return mTuple == vec.mTuple;
		}

		inline bool operator!=(Vector const& vec) const
		{
			return mTuple != vec.mTuple;
		}

		inline bool operator< (Vector const& vec) const
		{
			return mTuple < vec.mTuple;
		}

		inline bool operator<=(Vector const& vec) const
		{
			return mTuple <= vec.mTuple;
		}

		inline bool operator> (Vector const& vec) const
		{
			return mTuple > vec.mTuple;
		}

		inline bool operator>=(Vector const& vec) const
		{
			return mTuple >= vec.mTuple;
		}

		// Special vectors.

	   // All components are 0.
		void makeZero()
		{
			std::fill(mTuple.begin(), mTuple.end(), (CoordType)0);
		}

		// All components are 1.
		void makeOnes()
		{
			std::fill(mTuple.begin(), mTuple.end(), (CoordType)1);
		}

		// Component d is 1, all others are zero.
		void makeUnit(int d)
		{
			std::fill(mTuple.begin(), mTuple.end(), (CoordType)0);
			if (0 <= d && d < Dim)
			{
				mTuple[d] = (CoordType)1;
			}
		}

		static Vector zero()
		{
			Vector<Dim, CoordType> v;
			v.makeZero();
			return v;
		}

		static Vector ones()
		{
			Vector<Dim, CoordType> v;
			v.makeOnes();
			return v;
		}

		static Vector unit(int d)
		{
			Vector<Dim, CoordType> v;
			v.makeUnit(d);
			return v;
		}
	protected:
		std::array<coord_type, Dim> mTuple;

	};
	
	// Unary operations.
	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim> operator+(Vector<CoordType,Dim> const& v)
	{
		return v;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim> operator-(Vector<CoordType,Dim> const& v)
	{
		Vector<CoordType,Dim> result;
		for (int i = 0; i < Dim; ++i)
		{
			result[i] = -v[i];
		}
		return result;
	}

	// Linear-algebraic operations.
	template <typename CoordType, size_t Dim>
	Vector<CoordType, Dim>& operator+=(Vector<CoordType, Dim>& v0, Vector<CoordType, Dim> const& v1)
	{
		for (int i = 0; i < Dim; ++i)
		{
			v0[i] += v1[i];
		}
		return v0;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType, Dim>& operator-=(Vector<CoordType, Dim>& v0, Vector<CoordType, Dim> const& v1)
	{
		for (int i = 0; i < Dim; ++i)
		{
			v0[i] -= v1[i];
		}
		return v0;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType, Dim>& operator*=(Vector<CoordType, Dim>& v, CoordType scalar)
	{
		for (int i = 0; i < Dim; ++i)
		{
			v[i] *= scalar;
		}
		return v;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType, Dim>& operator/=(Vector<CoordType, Dim>& v, CoordType scalar)
	{
		if (scalar != (CoordType)0)
		{
			CoordType invScalar = (CoordType)1 / scalar;
			for (int i = 0; i < Dim; ++i)
			{
				v[i] *= invScalar;
			}
		}
		else
		{
			for (int i = 0; i < Dim; ++i)
			{
				v[i] = (CoordType)0;
			}
		}
		return v;
	}
	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim> operator+(Vector<CoordType,Dim> const& v0, Vector<CoordType,Dim> const& v1)
	{
		Vector<CoordType,Dim> result = v0;
		return result += v1;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim> operator-(Vector<CoordType,Dim> const& v0, Vector<CoordType,Dim> const& v1)
	{
		Vector<CoordType,Dim> result = v0;
		return result -= v1;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim> operator*(Vector<CoordType,Dim> const& v, CoordType scalar)
	{
		Vector<CoordType,Dim> result = v;
		return result *= scalar;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim> operator*(CoordType scalar, Vector<CoordType,Dim> const& v)
	{
		Vector<CoordType,Dim> result = v;
		return result *= scalar;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim> operator/(Vector<CoordType,Dim> const& v, CoordType scalar)
	{
		Vector<CoordType,Dim> result = v;
		return result /= scalar;
	}

	// Componentwise algebraic operations.
	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim> operator*(Vector<CoordType,Dim> const& v0, Vector<CoordType,Dim> const& v1)
	{
		Vector<CoordType,Dim> result = v0;
		return result *= v1;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim> operator/(Vector<CoordType,Dim> const& v0, Vector<CoordType,Dim> const& v1)
	{
		Vector<CoordType,Dim> result = v0;
		return result /= v1;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim>& operator*=(Vector<CoordType,Dim>& v0, Vector<CoordType,Dim> const& v1)
	{
		for (int i = 0; i < Dim; ++i)
		{
			v0[i] *= v1[i];
		}
		return v0;
	}

	template <typename CoordType, size_t Dim>
	Vector<CoordType,Dim>& operator/=(Vector<CoordType,Dim>& v0, Vector<CoordType,Dim> const& v1)
	{
		for (int i = 0; i < Dim; ++i)
		{
			v0[i] /= v1[i];
		}
		return v0;
	}

	template <typename CoordType, size_t Dim>
	CoordType Dot(Vector<CoordType,Dim> const& v0, Vector<CoordType,Dim> const& v1)
	{
		CoordType dot = v0[0] * v1[0];
		for (int i = 1; i < Dim; ++i)
		{
			dot += v0[i] * v1[i];
		}
		return dot;
	}

	template <typename CoordType, size_t Dim>
	CoordType Length(Vector<CoordType,Dim> const& v, bool robust = false)
	{
		if (robust)
		{
			CoordType maxAbsComp = std::fabs(v[0]);
			for (int i = 1; i < Dim; ++i)
			{
				CoordType absComp = std::fabs(v[i]);
				if (absComp > maxAbsComp)
				{
					maxAbsComp = absComp;
				}
			}

			CoordType length;
			if (maxAbsComp > (CoordType)0)
			{
				Vector<CoordType,Dim> scaled = v / maxAbsComp;
				length = maxAbsComp * std::sqrt(Dot(scaled, scaled));
			}
			else
			{
				length = (CoordType)0;
			}
			return length;
		}
		else
		{
			return std::sqrt(Dot(v, v));
		}
	}

	template <typename CoordType, size_t Dim>
	CoordType Normalize(Vector<CoordType,Dim>& v, bool robust = false)
	{
		if (robust)
		{
			CoordType maxAbsComp = std::fabs(v[0]);
			for (int i = 1; i < Dim; ++i)
			{
				CoordType absComp = std::fabs(v[i]);
				if (absComp > maxAbsComp)
				{
					maxAbsComp = absComp;
				}
			}

			CoordType length;
			if (maxAbsComp > (CoordType)0)
			{
				v /= maxAbsComp;
				length = std::sqrt(Dot(v, v));
				v /= length;
				length *= maxAbsComp;
			}
			else
			{
				length = (CoordType)0;
				for (int i = 0; i < Dim; ++i)
				{
					v[i] = (CoordType)0;
				}
			}
			return length;
		}
		else
		{
			CoordType length = std::sqrt(Dot(v, v));
			if (length > (CoordType)0)
			{
				v /= length;
			}
			else
			{
				for (int i = 0; i < Dim; ++i)
				{
					v[i] = (CoordType)0;
				}
			}
			return length;
		}
	}
	
} //namespace gte
#endif // !GTE_VECTOR_HPP

