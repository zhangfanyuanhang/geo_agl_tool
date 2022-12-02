#pragma once

#ifndef GTE_POLYLINE_HPP
#define GTE_POLYLINE_HPP

#include "Sequencer.hpp"

///! 顺序点连接成多折线。
namespace gte {

	template <typename PointType>
	class Polyline :public Sequencer<PointType>
	{
	public:
		using  point_type = PointType;
	public:
		Polyline() = default;
		~Polyline() = default;
		Polyline(const Polyline&) = default;

		Polyline(const std::list<point_type>& pts) :Sequencer<point_type>(pts) {}
		Polyline(const std::vector<point_type>& pts) :Sequencer<point_type>(pts) {}
		Polyline(std::initializer_list<point_type>& pts):Sequencer<point_type>(pts){}
		template <typename Iter>
		Polyline(const Iter begin, const Iter end) : Sequencer<point_type>(begin, end) {}
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
		//inline bool closure()override { return close; }
	};

}

#endif // !GTE_POLYGON2_HPP

