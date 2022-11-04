
#include "MedialAxisTransform.h"
#include "../easyx_show.h"

MedialAxisTransform::MedialAxisTransform(const gte::Polygons2i& plys):mPolygons(plys)
{
}

MedialAxisTransform::~MedialAxisTransform()
{
}
void MedialAxisTransform::ConstructVoronoi(std::vector<gte::Point2i>& pts)
{
	std::vector<gte::Segment2i> segms;
	mPolygons.Segments(&segms);
	boost::polygon::voronoi_builder<int64_t, boost::polygon::detail::my_voronoi_ctype_traits<int64_t>> voronoi_builder;
	
	for (auto iter = segms.begin(); iter != segms.end(); ++iter)
	{
		voronoi_builder.insert_segment(iter->p0().x(), iter->p0().y(), iter->p1().x(), iter->p1().y());
	}
	voronoi_builder.construct(&mVoronoiDiagram);
	///Voronoi±ß
//	EasyXShow2D easyx_show;
//	easyx_show.setWindows();
	//easyx_show.polygons(umPlys);
//	easyx_show.polylines(mat_pts);
	

	voronoi_diagram::const_edge_iterator edge_iter = mVoronoiDiagram.edges().begin();
	for (; edge_iter != mVoronoiDiagram.edges().end(); ++edge_iter)
	{
		if (edge_iter->is_primary())
		{
			if (edge_iter->vertex0())
			{
				int64_t x = edge_iter->vertex0()->x();
				int64_t y = edge_iter->vertex0()->y();
				pts.push_back({ x,y });
			}
		}
		;
	}
	//easyx_show.show();
	//easyx_show.polygons(plys);
	//easyx_show.closeWindows();
	/*const voronoi_diagram::edge_type *cur_edge = &*edge_iter;
	const voronoi_diagram::edge_type *nex_edge;
	while (true)
	{
		if (cur_edge->vertex0())
		{
			int64_t x = cur_edge->vertex0()->x();
			int64_t y = cur_edge->vertex0()->y();
			pts.push_back({ x,y });
		}

		const voronoi_diagram::edge_type *nex_edge = cur_edge->next();
		if (nullptr == nex_edge)
			break;
		if (nex_edge == &*edge_iter)
		{
			break;
		}
		cur_edge = nex_edge;
	}*/
	
}
