
#include "MedialAxisTransform.h"
#include "Graphic2.h"
#include "Polylines2.h"
#include "Polyline2.h"

MedialAxisTransform::MedialAxisTransform(const gte::Polygons2i& plys):mPolygons(plys)
{
	mGraphicPtr = new gui::Graphic2();
}

MedialAxisTransform::~MedialAxisTransform()
{
	if (nullptr != mGraphicPtr)
	{
		delete mGraphicPtr;
		mGraphicPtr = nullptr;
	}
	if (nullptr != mPolys)
	{
		delete mPolys;
		mPolys = nullptr;
	}
}
void  MedialAxisTransform::show()
{
	mGraphicPtr->initWindow(1000, 1000);
	mGraphicPtr->show(mPolys);
	mGraphicPtr->closeWindow();
}
void MedialAxisTransform::ConstructVoronoi()
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
	gte::Polygon2i tmpply;
	//std::vector<gte::Point2i> pts;
	gte::Polylines2i* polylines = new gte::Polylines2i;
	voronoi_diagram::const_edge_iterator edge_iter = mVoronoiDiagram.edges().begin();
	const voronoi_cell* cell;
	const voronoi_edge* edge;
	for (; edge_iter != mVoronoiDiagram.edges().end(); ++edge_iter)
	{
		if (edge_iter->is_primary() && edge_iter->is_finite())
		{
			gte::Polyline2i polyline;
			/*if (edge_iter->vertex0() && edge_iter->vertex1())
			{
				int64_t x = edge_iter->vertex0()->x();
				int64_t y = edge_iter->vertex0()->y();
				polyline.push_back({ (int64_t)edge_iter->vertex0()->x(),(int64_t)edge_iter->vertex0()->y() });
				polyline.push_back({ (int64_t)edge_iter->vertex1()->x(),(int64_t)edge_iter->vertex1()->y() });
			}*/
			cell = edge_iter->cell();
			if (cell)
			{
				edge = cell->incident_edge();
				do
				{
					if (edge->vertex0() && edge->vertex1())
					{
						int64_t x = edge->vertex0()->x();
						int64_t y = edge->vertex0()->y();
						gte::Point2i pt0({ x,y });
						gte::Point2i pt1({ x,y });
						if (boost::polygon::contains(mPolygons[0], pt0)&& boost::polygon::contains(mPolygons[0], pt1)
							&& !boost::polygon::contains(mPolygons[1], pt0) && !boost::polygon::contains(mPolygons[1], pt1))
						{
							polyline.push_back(pt0);
							polyline.push_back(pt1);
						}
					}
					edge = edge->next();
				} while (edge && edge != cell->incident_edge());
				polylines->push_back(polyline);
				//break;
			}
			
		}
		
	}
	mPolys = polylines;

	
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
