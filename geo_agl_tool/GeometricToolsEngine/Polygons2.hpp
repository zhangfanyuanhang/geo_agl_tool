#pragma once

#ifndef GTE_POLYGONS2_H
#define GTE_POLYGONS2_H

#include "Polygons.hpp"
#include "Polygon2.hpp"


///! ��ά����μ��Ϲ��캬�п׵�����
namespace gte {

	///! ģ�廯�ض����͵ĺ��п׵Ķ�ά�����
	template <typename CoordType> class Polygons2;
	using Polygons2i = Polygons2<int64_t>;
	using Polygons2d = Polygons2<double_t>;
	
	///! ���п׵Ķ���ζ���
	template <typename CoordType>
	class Polygons2 :public Polygons<Polygon2<CoordType>>
	{
	public:
		typedef Polygon2<CoordType> polygon_type;
		using point_type = typename polygon_type::point_type;

	public:
		Polygons2() = default;
		~Polygons2() = default;
		Polygons2(const Polygons2&) = default;
		Polygons2(const std::list<polygon_type>& pts) :Polygons<polygon_type>(pts) {}
		Polygons2(const std::vector<polygon_type>& pts) :Polygons<polygon_type>(pts) {}
		Polygons2(std::initializer_list<polygon_type>& pts) :Polygons<polygon_type>(pts) {}

		//! ����ʵ��	
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	public:
		//�����ڶ�����ڲ�
		inline bool within(const point_type& pt) { return boost::geometry::within(pt,*this); }
	};
}

#endif // !GTE_POLYGON2_HPP

