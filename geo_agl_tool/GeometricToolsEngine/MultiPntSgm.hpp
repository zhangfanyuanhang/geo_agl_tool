#pragma once

#ifndef GTE_MULTIPNTSGM_HPP
#define GTE_MULTIPNTSGM_HPP

#include "MathDefines.h"
#include "Sequencer.hpp"
#include "Point.hpp"
#include "Segment2.hpp"

///! 点结构数据，使用代数几何里面的向量数据结构
///! 点的意义和向量的意义一致。
namespace gte {
	
	using MultiPoints2i = Sequencer<Point2i>;
	using MultiPoints2d = Sequencer<Point2d>;
	using MultiSegments2i = Sequencer<Segment2i>;
	using MultiSegments2d = Sequencer<Segment2d>;

}

#endif //GTE_MULTIPNTSGM_HPP
