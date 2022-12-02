#pragma once

#ifndef GTE_MATRIX_HPP
#define GTE_MATRIX_HPP

#include <algorithm>
#include <array>
#include <initializer_list>
#include "Vector.hpp"

namespace gte {

	//! 列主序矩阵
	template <typename T, size_t R,size_t C>
	class Matrix
	{
	public:
		typedef T coord_type;
		static size_t Row = R;
		static size_t Colum = C;
	public:
		Matrix() = default;
		virtual ~Matrix() = default;
		//! 列主序初始化数组
		Matrix(std::array<coord_type, R * C> const& values)
		{
			for (size_t c = 0, i = 0; c < C; ++c)
			{
				for (size_t r = 0; r < R; ++r, ++i)
				{
					mStorage[c][r] = values[i];
				}
			}
		}
		//! 列主序初始化列表
		Matrix(const std::initializer_list<std::initializer_list<coord_type>>& v)
		{
			size_t c = v.size();
			for (size_t i = 0; i < C; i++)
			{
				if (i < c)
				{
					size_t r = c[i].size();
					for (size_t j = 0; j < R; j++)
					{
						if (j < r)
						{
							mStorage[i][j] = v[i][j];
						}
						else {
							mStorage[i][j] = (coord_type)0;
						}
					}
				}else{
					for (size_t j = 0; j < R; j++)
					{
						mStorage[i][j] = (coord_type)0;
					}
				}
				
			}

		}
		inline size_t rows()const { return R; }
		inline size_t cols()const { return C; }

		inline coord_type const& operator()(int r, int c) const
		{
			return mStorage[c][r];
		}

		inline coord_type& operator()(int r, int c)
		{
			return mStorage[c][r];
		}

		inline Vector<coord_type, C> row(size_t r)const 
		{ 
			Vector<coord_type, C> v;
			for (size_t i = 0; i < C; i++)
			{
				v[i] = mStorage[i][r];
			}
			return v;
		}
		inline Vector<coord_type, R> col(size_t c)const { return Vector<coord_type, R>(mStorage[c]); }

		inline void makeZero() { std::fill_n(&mStorage[0][0], R*C, (coord_type)0); }
		inline void makeUnit() 
		{ 
			std::fill_n(&mStorage[0][0], R*C, (coord_type)0);
			size_t min = R <= C ? R, C;
			for (size_t i = 0; i < min; i++)
			{
				mStorage[i][i] = (coord_type)1;
			}
			for (size_t r = min; r < R; r++)
			{
				mStorage[min-1][r] = (coord_type)1;
			}
			for (size_t c = min; c < C; c++)
			{
				mStorage[c][min - 1] = (coord_type)1;
			}
		}
		static inline Matrix zero()
		{
			Matrix<coord_type,R,C> m;
			m.makeZero();
			return m;
		};
		static inline Matrix unit()
		{
			Matrix<coord_type, R, C> m;
			m.makeUnit();
			return m;
		}
	protected:
	
		std::array<std::array<coord_type, R>, C> mStorage;
	};

}


#endif // !GTE_MATRIX_H

