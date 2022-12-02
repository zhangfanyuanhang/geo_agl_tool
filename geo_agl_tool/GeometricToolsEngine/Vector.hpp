#pragma once

#ifndef GTE_VECTOR_HPP
#define GTE_VECTOR_HPP

#include <algorithm>
#include <array>
#include <initializer_list>

///! ������������������ṹ��
///! ģ�廯������ά�����������͡�
namespace gte {

	template <typename T,size_t N>
	class Vector
	{
	public:
		typedef  T coord_type;
		static const  size_t Dim = N;
	public:
		//! ���캯����
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

		//! ����������
		virtual ~Vector() = default;
		//! �������ݡ�
		inline std::array<coord_type, N> data()const { return mTuple; }
		//! ����ά����
		inline size_t size() const{return N;}
		//! �������ȡ�
		//! robust �Ƿ�ʹ��³���Լ��㡣
		coord_type length(bool robust = false)const;
		//! ��λ������
		//! robust �Ƿ�ʹ��³���Լ��㡣
		Vector normalize(bool robust)const;
		//! ������������أ�û��Խ���顣
		inline coord_type const& operator[](size_t i) const{return mTuple[i];}
		inline coord_type& operator[](size_t i){return mTuple[i];}

		//! �Ƚ���������أ����������������
		inline bool operator==(Vector const& vec) const{return mTuple == vec.mTuple;}
		inline bool operator!=(Vector const& vec) const{return mTuple != vec.mTuple;}
		inline bool operator< (Vector const& vec) const{return mTuple < vec.mTuple;}
		inline bool operator<=(Vector const& vec) const{return mTuple <= vec.mTuple;}
		inline bool operator> (Vector const& vec) const{return mTuple > vec.mTuple;}
		inline bool operator>=(Vector const& vec) const{return mTuple >= vec.mTuple;}

	    //! ������,����Ԫ�ض���0��
		void makeZero()
		{
			std::fill(mTuple.begin(), mTuple.end(), (T)0);
		}
		//! 1����������Ԫ�ض���1��
		void makeOnes()
		{
			std::fill(mTuple.begin(), mTuple.end(), (T)1);
		}
		//! 1������ǰd��Ԫ����1�������Ԫ�ض���0��
		void makeOnes(int d)
		{
			std::fill(mTuple.begin(), mTuple.end(), (T)0);
			if (0 <= d && d < N)
			{
				mTuple[d] = (T)1;
			}
		}
		//! ��ľ�̬����������������
		static Vector zero()
		{
			Vector<N, T> v;
			v.makeZero();
			return v;
		}
		//! ��ľ�̬����������1����
		static Vector ones()
		{
			Vector<N, T> v;
			v.makeOnes();
			return v;
		}
		//! ��ľ�̬����������1����
		static Vector unit(int d)
		{
			Vector<N, T> v;
			v.makeOnes(d);
			return v;
		}
	protected:
		std::array<coord_type, N> mTuple;

	};
	
	//! һԪ������������ء�
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

	//! ��Ԫ������������ء�
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
	//! ���������ˡ����ˡ�
	template <typename T, size_t N>
	Vector<T, N>& operator*=(Vector<T, N>& v, T scalar)
	{
		for (int i = 0; i < N; ++i)
		{
			v[i] *= scalar;
		}
		return v;
	}
	//! ������������������
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

	//�������˷�����ӦԪ����ˡ�
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
	//��������������ӦԪ�������
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
	//! ���������
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
	
} //namespace gte
#endif // !GTE_VECTOR_HPP

