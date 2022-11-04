#pragma once

#ifndef GTE_POLYLINES_H
#define GTE_POLYLINES_H

#include "Sequencers.h"
#include "Polyline.h"

namespace gte {

	template <typename PointType> class Polylines;
	using PolyLines2i = Polylines<PolyLine2i>;
	using PolyLines2d = Polylines<PolyLine2d>;
	using PolyLines3i = Polylines<PolyLine3i>;
	using PolyLines3d = Polylines<PolyLine3d>;

	template <typename SequencerType>
	class Polylines :public Sequencers<SequencerType>
	{
	public:
		typedef typename Sequencers<SequencerType>::point_type point_type;
		typedef SequencerType sequencer_type;
		typedef typename std::vector<sequencer_type>::const_iterator const_iterator;
		typedef typename std::vector<sequencer_type>::iterator iterator;
	public:
		Polylines() = default;
		~Polylines() = default;

		Polylines(const std::vector<sequencer_type>& pts) :Sequencers<SequencerType>(pts) {}
		Polylines(std::initializer_list<sequencer_type>& pts) :Sequencers<SequencerType>(pts) {}
		
	};
}

#endif // !GTE_POLYGON2_HPP

