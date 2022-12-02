#pragma once

#ifndef MAT_MEDIAL_AXIS_TRANSFORM_H
#define MAT_MEDIAL_AXIS_TRANSFORM_H

#include "GeometricToolsEngine.h"
#include "boost/polygon/voronoi.hpp"

#include "Graphic.h"

namespace boost {
	namespace polygon {
		namespace detail {
			template <typename T>
			struct my_voronoi_ctype_traits;

			template <>
			struct my_voronoi_ctype_traits<int64_t> {
				typedef int64_t int_type;
				typedef int64_t int_x2_type;
				typedef uint64_t uint_x2_type;
				typedef extended_int<128> big_int_type;
				typedef double_t fpt_type;
				typedef extended_exponent_fpt<fpt_type> efpt_type;
				typedef ulp_comparison<fpt_type> ulp_cmp_type;
				typedef type_converter_fpt to_fpt_converter_type;
				typedef type_converter_efpt to_efpt_converter_type;
			};
		}
	}
}
class MedialAxisTransform
{
	using voronoi_diagram = boost::polygon::voronoi_diagram<double_t>;
	using voronoi_cell = boost::polygon::voronoi_cell<double_t>;
	using voronoi_edge = boost::polygon::voronoi_edge<double_t>;
	using voronoi_vertex = boost::polygon::voronoi_vertex<double_t>;
	using source_category = boost::polygon::SourceCategory;

	enum MATType {
		MAT_UNKNOWN = 0,
		MAT_EDGE_SKL = 1,
		MAT_EDGE_SKL_FORK = 2,

		MAT_EDGE_SKL_BRANCH = 10,
	};
	struct MATHalfEdge;
	struct MATVertex {
		MATHalfEdge * he;
		voronoi_vertex* mVertex;
	};
	struct MATEdge {
		MATHalfEdge * he;
		std::deque<voronoi_edge*> mEdge;
	};
	struct MATHalfEdge {
		MATHalfEdge * next;
		MATHalfEdge * pre;
		MATHalfEdge * twin;
		MATVertex * origin;
		MATEdge * edge;
	};
public:
	MedialAxisTransform(const gte::Polygons2i& plys);
	~MedialAxisTransform();

	void ConstructVoronoi();
	void show();

private:
	void travelInCell(const voronoi_edge* src,std::deque<const voronoi_edge*>& dst);
	size_t countMATEdge(const voronoi_edge* src);
	bool backNextTravel(const voronoi_edge* src, std::deque<const voronoi_edge*>& dst);
	bool frontPrevTravel(const voronoi_edge* src, std::deque<const voronoi_edge*>& dst);
	bool isConnect(const voronoi_edge* src, const voronoi_edge* dst);
	void connectCellMATEdge(std::deque<std::deque<const voronoi_edge*>>& src, std::deque<std::deque<const voronoi_edge*>>& dst);
private:
	voronoi_diagram mVoronoiDiagram;
private:
	gte::Polygons2i mPolygons;
	std::vector<gte::Point2i> mMATPoints;

	gui::Graphic* mGraphicPtr;
	gte::PolyBase* mPolys;

	std::vector<MATHalfEdge *> halfEdges;
	std::vector<MATVertex *> vertices;
	std::vector<MATEdge *> edges;
};


#endif // !MAT_MEDIAL_AXIS_TRANSFORM_H

