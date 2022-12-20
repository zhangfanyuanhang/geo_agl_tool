#pragma once

#ifndef GTE_VECTOR_HPP
#define GTE_VECTOR_HPP

#include <algorithm>
#include <array>
#include <initializer_list>

///! 代数几何里面的向量结构。
///! 模板化向量的维数和数据类型。
namespace gte {

	template <typename T,size_t N>
	class Vector
	{
	public:
		typedef  T coord_type;
		static const  size_t Dim = N;
	public:
		//! 构造函数。
		Vector() = default;
		Vector(const Vector&) = default;
		Vector(std::array<coord_type, N> const& values) :mTuple(values) {}
		Vector(std::initializer_list<coord_type> values)
		{
			size_t const num = values.size();
			if (N == num)
			{
				std::copy(values.begin(), values.end(), mTuple.begin());
			}
			else if (N > num)
			{
				std::copy(values.begin(), values.end(), mTuple.begin());
				std::fill(mTuple.begin() + num, mTuple.end(), (coord_type)0);
			}
			else // N < num
			{
				std::copy(values.begin(), values.begin() + N, mTuple.begin());
			}
		}
		Vector(coord_type* values,size_t n){ std::copy(values, values+n, mTuple.begin()); }

		//! 析构函数。
		virtual ~Vector() = default;
		//! 向量数据。
		inline std::array<coord_type, N> data()const { return mTuple; }
		//! 向量维数。
		inline size_t size() const{return N;}
		//! 向量长度。
		//! robust 是否使用鲁棒性计算。
		coord_type length(bool robust = false)const;
		//! 单位向量。
		//! robust 是否使用鲁棒性计算。
		Vector normalize(bool robust)const;
		//! 访问运算符重载，没有越界检查。
		inline coord_type const& operator[](size_t i) const{return mTuple[i];}
		inline coord_type& operator[](size_t i){return mTuple[i];}

		//! 比较运算符重载，适用有序的向量。
		inline bool operator==(Vector const& vec) const{return mTuple == vec.mTuple;}
		inline bool operator!=(Vector const& vec) const{return mTuple != vec.mTuple;}
		inline bool operator< (Vector const& vec) const{return mTuple < vec.mTuple;}
		inline bool operator<=(Vector const& vec) const{return mTuple <= vec.mTuple;}
		inline bool operator> (Vector const& vec) const{return mTuple > vec.mTuple;}
		inline bool operator>=(Vector const& vec) const{return mTuple >= vec.mTuple;}

	    //! 零向量,所有元素都是0。
		void makeZero()
		{
			std::fill(mTuple.begin(), mTuple.end(), (T)0);
		}
		//! 1向量，所有元素都是1。
		void makeOnes()
		{
			std::fill(mTuple.begin(), mTuple.end(), (T)1);
		}
		//! 1向量，前d个元素是1，后面的元素都是0。
		void makeOnes(int d)
		{
			std::fill(mTuple.begin(), mTuple.end(), (T)0);
			if (0 <= d && d < N)
			{
				mTuple[d] = (T)1;
			}
		}
		//! 类的静态函数，创建零向量
		static Vector zero()
		{
			Vector<N, T> v;
			v.makeZero();
			return v;
		}
		//! 类的静态函数，创建1向量
		static Vector ones()
		{
			Vector<N, T> v;
			v.makeOnes();
			return v;
		}
		//! 类的静态函数，创建1向量
		static Vector unit(int d)
		{
			Vector<N, T> v;
			v.makeOnes(d);
			return v;
		}
	protected:
		std::array<coord_type, N> mTuple;

	};
	
	//! 一元算术运算符重载。
	template <typename T, size_t N>
	Vector<T,N> operator+(Vector<T,N> const& v)
	{
		return v;
	}
	template <typename T, size_t N>
	Vector<T,N> operator-(Vector<T,N> const& v)
	{
		Vector<T,N> result;
		for (int i = 0; i < N; ++i)
		{
			result[i] = -v[i];
		}
		return result;
	}

	//! 二元算术运算符重载。
	template <typename T, size_t N>
	Vector<T, N>& operator+=(Vector<T, N>& v0, Vector<T, N> const& v1)
	{
		for (int i = 0; i < N; ++i)
		{
			v0[i] += v1[i];
		}
		return v0;
	}

	template <typename T, size_t N>
	Vector<T, N>& operator-=(Vector<T, N>& v0, Vector<T, N> const& v1)
	{
		for (int i = 0; i < N; ++i)
		{
			v0[i] -= v1[i];
		}
		return v0;
	}
	//! 向量标量乘、数乘。
	template <typename T, size_t N>
	Vector<T, N>& operator*=(Vector<T, N>& v, T scalar)
	{
		for (int i = 0; i < N; ++i)
		{
			v[i] *= scalar;
		}
		return v;
	}
	//! 向量标量除、数除。
	template <typename T, size_t N>
	Vector<T, N>& operator/=(Vector<T, N>& v, T scalar)
	{
		if (scalar != (T)0)
		{
			T invScalar = (T)1 / scalar;
			for (int i = 0; i < N; ++i)
			{
				v[i] *= invScalar;
			}
		}
		else
		{
			for (int i = 0; i < N; ++i)
			{
				v[i] = (T)0;
			}
		}
		return v;
	}
	template <typename T, size_t N>
	Vector<T,N> operator+(Vector<T,N> const& v0, Vector<T,N> const& v1)
	{
		Vector<T,N> result = v0;
		return result += v1;
	}

	template <typename T, size_t N>
	Vector<T,N> operator-(Vector<T,N> const& v0, Vector<T,N> const& v1)
	{
		Vector<T,N> result = v0;
		return result -= v1;
	}

	template <typename T, size_t N>
	Vector<T,N> operator*(Vector<T,N> const& v, T scalar)
	{
		Vector<T,N> result = v;
		return result *= scalar;
	}

	template <typename T, size_t N>
	Vector<T,N> operator*(T scalar, Vector<T,N> const& v)
	{
		Vector<T,N> result = v;
		return result *= scalar;
	}

	template <typename T, size_t N>
	Vector<T,N> operator/(Vector<T,N> const& v, T scalar)
	{
		Vector<T,N> result = v;
		return result /= scalar;
	}

	//！向量乘法，对应元素相乘。
	template <typename T, size_t N>
	Vector<T,N> operator*(Vector<T,N> const& v0, Vector<T,N> const& v1)
	{
		Vector<T,N> result = v0;
		return result *= v1;
	}
	template <typename T, size_t N>
	Vector<T, N>& operator*=(Vector<T, N>& v0, Vector<T, N> const& v1)
	{
		for (int i = 0; i < N; ++i)
		{
			v0[i] *= v1[i];
		}
		return v0;
	}
	//！向量除法，对应元素相除。
	template <typename T, size_t N>
	Vector<T,N> operator/(Vector<T,N> const& v0, Vector<T,N> const& v1)
	{
		Vector<T,N> result = v0;
		return result /= v1;
	}
	template <typename T, size_t N>
	Vector<T,N>& operator/=(Vector<T,N>& v0, Vector<T,N> const& v1)
	{
		for (int i = 0; i < N; ++i)
		{
			v0[i] /= v1[i];
		}
		return v0;
	}
	//! 向量点积。
	template <typename T, size_t N>
	T Dot(Vector<T,N> const& v0, Vector<T,N> const& v1)
	{
		T dot = v0[0] * v1[0];
		for (int i = 1; i < N; ++i)
		{
			dot += v0[i] * v1[i];
		}
		return dot;
	}
	

	//!
	template <typename T, size_t N>
	T  Vector<T, N>::length(bool robust)const
	{
		const Vector<T, N>& v = *this;
		if (robust)
		{
			T maxAbsComp = std::fabs(v[0]);
			for (int i = 1; i < N; ++i)
			{
				T absComp = std::fabs(v[i]);
				if (absComp > maxAbsComp)
				{
					maxAbsComp = absComp;
				}
			}

			T length;
			if (maxAbsComp > (T)0)
			{
				Vector<T, N> scaled = v / maxAbsComp;
				length = maxAbsComp * std::sqrt(Dot(scaled, scaled));
			}
			else
			{
				length = (T)0;
			}
			return length;
		}
		else
		{
			return std::sqrt(Dot(v, v));
		}
	}
	template <typename T, size_t N>
	Vector<T, N> Vector<T, N>::normalize(bool robust)const
	{
		Vector<T, N> v = *this;
		if (robust)
		{
			T maxAbsComp = std::fabs(v[0]);
			for (int i = 1; i < N; ++i)
			{
				T absComp = std::fabs(v[i]);
				if (absComp > maxAbsComp)
				{
					maxAbsComp = absComp;
				}
			}

			T length;
			if (maxAbsComp > (T)0)
			{
				v /= maxAbsComp;
				length = std::sqrt(Dot(v, v));
				v /= length;
				length *= maxAbsComp;
			}
			else
			{
				length = (T)0;
				for (int i = 0; i < N; ++i)
				{
					v[i] = (T)0;
				}
			}
		}
		else
		{
			T length = std::sqrt(Dot(v, v));
			if (length > (T)0)
			{
				v /= length;
			}
			else
			{
				for (int i = 0; i < N; ++i)
				{
					v[i] = (T)0;
				}
			}
		}
		return v;
	}
} //namespace gte
#endif // !GTE_VECTOR_HPP

