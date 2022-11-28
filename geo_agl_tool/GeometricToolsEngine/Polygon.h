#pragma once

#ifndef GTE_POLYGON_H
#define GTE_POLYGON_H

#include "Sequencer.h"
#include "BoundBox.h"
#include "Segment.h"

//! ˳��㹹�ɶ���μ򵥶��������
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
		Polygon(std::initializer_list<point_type>& pts):Sequencer<point_type> (pts){}

	//! ����ʵ��	
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
		/*inline bool closure()override { return Closed; }
		inline ORDER order()override { return point_order; }*/
	public:	
		//! ��Գ�����Χ��
		void AABB(BoundingBox<point_type>& aabb) { AxiallyAlignedBoundingBox(&(*this)[0], this->size(), aabb); }
		
		template <typename DestIt>
		void Segments(DestIt* iter) {
			size_t size = this->size();
			size_t j = 0;
			for (size_t i = 0; i < size; i++)
			{
				j = (i + 1) % size;
				Segment<point_type> segm((*this)[i], (*this)[j]);
				iter->push_back(segm);
			};
		};
	//private:
	//	std::vector<point_type> mPolygon;
	};
	
}

#endif // !GTE_POLYGON2_HPP

