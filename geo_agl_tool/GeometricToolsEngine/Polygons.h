#pragma once

#ifndef GTE_POLYGONS_H
#define GTE_POLYGONS_H

#include "Sequencer.h"
#include "Polygon.h"

//! ������鹹��һ������ͨ���׵Ķ��������
//! ��һ�������Ϊ�����������������Ϊ��ʱ�롣
//! ���������Ϊ�����������������Ϊ˳ʱ�롣
namespace gte {

	template <typename PolygonType>
	class Polygons :public Sequencer< PolygonType >
	{
	public:
		typedef PolygonType polygon_type;
		using point_type = typename polygon_type::point_type;
		//typedef PointType point_type;

	public:
		Polygons() = default;
		~Polygons() = default;
		Polygons(const std::list<polygon_type>& pts) :Sequencer<polygon_type>(pts) {}
		Polygons(const std::vector<polygon_type>& pts) :Sequencer<polygon_type>(pts) {}
		Polygons(std::initializer_list<polygon_type>& pts) :Sequencer<polygon_type>(pts) {}

	//! ����ʵ��
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	public:
		//! ��Գư�Χ�У�ֻȡ��һ�������
		void AABB(BoundingBox<point_type>& aabb) { this->mData[0].AABB(aabb); }

		//! ת�����߶Σ������������ӳ��߶�
		template <typename DestIt>
		void Segments(DestIt* iter) {
			std::for_each(this->mData.begin(), this->mData.end(),
				[&iter](polygon_type& ply) {ply.Segments(iter); });

		}
	};
}

#endif // !GTE_POLYGON2_HPP

