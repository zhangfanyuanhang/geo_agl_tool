#pragma once

#ifndef GTE_POLYLINES_HPP
#define GTE_POLYLINES_HPP

#include "Polyline.hpp"

///! 多折线集合
namespace gte {

	template <typename PolylineType>
	class Polylines :public Sequencer<PolylineType>
	{
	public:
		typedef PolylineType polyline_type;
		using point_type = typename polyline_type::point_type;
	public:
		Polylines() = default;
		~Polylines() = default;
		Polylines(const Polylines&) = default;
		Polylines(const std::list<polyline_type>& pts) :Sequencer<polyline_type>(pts) {}
		Polylines(const std::vector<polyline_type>& pts) :Sequencer<polyline_type>(pts) {}
		Polylines(std::initializer_list<polyline_type>& pts) :Sequencer<polyline_type>(pts) {}
	public:
		inline const std::type_info& getType()override { return typeid(*this); }
	};
}

#endif // !GTE_POLYLINES_HPP

