#pragma once

#ifndef GTE_POLYGON_HPP
#define GTE_POLYGON_HPP

#include "Sequencer.hpp"
#include "BoundBox.hpp"
#include "Segment.hpp"

///! ˳��㹹�ɶ���μ򵥶��������
namespace gte {
	template <typename PointType>
	class Polygon:public Sequencer<PointType>
	{
	public:
		typedef  PointType point_type;
	public:
		Polygon() = default;
		~Polygon() = default;

		Polygon(const std::list<point_type>& pts) :Sequencer<point_type>(pts) {}
		Polygon(const std::vector<point_type>& pts) :Sequencer<point_type>(pts) {}
		Polygon(const std::initializer_list<point_type>& pts):Sequencer<point_type> (pts){}

	//! ����ʵ��	
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	public:	
		//! ��Գ�����Χ��
		void AABB(BoundingBox<point_type>& aabb) { AxiallyAlignedBoundingBox(&(*this)[0], this->size(), aabb); }
		//! ���ڵ����ӳ��߶�
		template <typename DestIt>
		void Segments(DestIt* iter) {
			size_t size = this->size();
			size_t j = 0;
			for (size_t i = 0; i < size; i++)
			{
				j = (i + 1) % size;
				//Segment<point_type> segm((*this)[i], (*this)[j]);
				iter->push_back({ (*this)[i], (*this)[j] });
			};
		};
		//�����ڶ�����ڲ�
		//inline bool within(const point_type& pt) { return boost::geometry::within(*this, pt); }
	};
	
}

#endif // !GTE_POLYGON2_HPP

