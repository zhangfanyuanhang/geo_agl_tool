#pragma once

#ifndef GTE_POLYGONS_H
#define GTE_POLYGONS_H

#include "Sequencer.h"
#include "Polygon.h"

//! 多边形组构成一个简单连通带孔的多边形区域。
//! 第一个多边形为区域的外轮廓，方向为逆时针。
//! 其它多边形为区域的内轮廓，方向为顺时针。
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

	//! 重载实现
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	public:
		//! 轴对称包围盒，只取第一个多边形
		void AABB(BoundingBox<point_type>& aabb) { this->mData[0].AABB(aabb); }

		//! 转化成线段，相邻两点连接成线段
		template <typename DestIt>
		void Segments(DestIt* iter) {
			std::for_each(this->mData.begin(), this->mData.end(),
				[&iter](polygon_type& ply) {ply.Segments(iter); });

		}
	};
}

#endif // !GTE_POLYGON2_HPP

