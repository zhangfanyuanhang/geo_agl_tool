
#include "Vector.h"

namespace gte {

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

}//namespace gte