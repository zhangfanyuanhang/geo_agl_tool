#pragma once

#ifndef GTE_POLYLINES2_HPP
#define GTE_POLYLINES2_HPP

#include "Polylines.hpp"
#include "Polyline2.hpp"
///! ��ά�����߼���
namespace gte {

	///! ģ�廯�ض����͵Ķ�ά������
	template<typename CoordType> class Polylines2;
	using Polylines2i = Polylines2<int64_t>;
	using Polylines2d = Polylines2<double_t>;

	///! ��ά�����߼��϶���
	template<typename CoordType>
	class Polylines2 :public Polylines<Polyline2<CoordType>>
	{
	public:
		typedef Polyline2<CoordType> polyline_type;
	public:
	public:
		Polylines2() = default;
		~Polylines2() = default;
		Polylines2(const Polylines2&) = default;
		Polylines2(const std::list<polyline_type>& pts) :Polylines<polyline_type>(pts) {}
		Polylines2(const std::vector<polyline_type>& pts) :Polylines<polyline_type>(pts) {}
		Polylines2(std::initializer_list<polyline_type>& pts) :Polylines<polyline_type>(pts) {}
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	};
}

#endif // !GTE_POLYGON2_HPP

