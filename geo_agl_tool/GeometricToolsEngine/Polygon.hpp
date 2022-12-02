#pragma once

#ifndef GTE_POLYGON_HPP
#define GTE_POLYGON_HPP

#include "Sequencer.hpp"
#include "BoundBox.hpp"
#include "Segment.hpp"

///! 顺序点构成多边形简单多边形区域
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

	//! 重载实现	
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	public:	
		//! 轴对称最大包围盒
		void AABB(BoundingBox<point_type>& aabb) { AxiallyAlignedBoundingBox(&(*this)[0], this->size(), aabb); }
		//! 相邻点连接成线段
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
		//！点在多边形内部
		//inline bool within(const point_type& pt) { return boost::geometry::within(*this, pt); }
	};
	
}

#endif // !GTE_POLYGON2_HPP

