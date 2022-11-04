#pragma once

#ifndef GTE_POLYGONS_H
#define GTE_POLYGONS_H

#include "Sequencers.h"

namespace gte {

	template <typename SequencerType>
	class Polygons:public Sequencers<SequencerType>
	{
	public:
		typedef typename Sequencers<SequencerType>::point_type point_type;
		typedef SequencerType sequencer_type;
		typedef typename std::vector<sequencer_type>::const_iterator const_iterator;
		typedef typename std::vector<sequencer_type>::iterator iterator;
	public:
		Polygons() = default;
		~Polygons() = default;
		
		Polygons(const std::vector<sequencer_type>& pts) :Sequencers<SequencerType>(pts) {}
		Polygons(std::initializer_list<sequencer_type>& pts) :Sequencers<SequencerType>(pts){}
		/*inline void add(sequencer_type ply) { mPolygons.push_back(ply); }
		inline size_t size()const { return mPolygons.size(); }
		inline void resize(size_t size) { mPolygons.resize(size); }

		inline const sequencer_type& operator[](size_t i)const { return mPolygons[i]; }
		inline sequencer_type& operator[](size_t i) { return mPolygons[i]; }

		inline const_iterator begin() const { return mPolygons.begin(); }
		inline const_iterator end() const { return mPolygons.end(); }

		inline iterator begin() { return mPolygons.begin(); }
		inline iterator end() { return mPolygons.end(); }

		template< class InputIt >
		iterator insert(const_iterator pos, InputIt first, InputIt last) { return mPolygons.insert(pos, first, last); }

		inline void clear() { mPolygons.clear(); }*/

		void AABB(BoundingBox<point_type>& aabb) { this->mSequencers[0].AABB(aabb);}
		
		template <typename DestIt>
		void Segments(DestIt* iter) {
			std::for_each(this->mSequencers.begin(), this->mSequencers.end(),
				[&iter](sequencer_type& ply) {ply.Segments(iter); });
			
		}
	//private:
	//	std::vector<sequencer_type> mPolygons;
	};
}

#endif // !GTE_POLYGON2_HPP

