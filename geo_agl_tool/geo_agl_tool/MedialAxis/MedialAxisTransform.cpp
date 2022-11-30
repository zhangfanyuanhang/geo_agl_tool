
#include "MedialAxisTransform.h"
#include "Graphic2.h"

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
	mGraphicPtr->setSourceData(&mPolygons);
	mGraphicPtr->show(mPolys);
	mGraphicPtr->closeWindow();
}
void MedialAxisTransform::ConstructVoronoi()
{
	std::vector<gte::Segment2i> segments;
	boost::polygon::voronoi_builder<int64_t, boost::polygon::detail::my_voronoi_ctype_traits<int64_t>> voronoi_builder;
	size_t ply_size = mPolygons.size();
	for (size_t i = 0; i < ply_size; i++)
	{
		size_t pt_size = mPolygons[i].size();
		for (size_t j = 0; j < pt_size; j++)
		{
			segments.push_back({ gte::Point2i(mPolygons[i][j].x(), mPolygons[i][j].y()), gte::Point2i(mPolygons[i][(j + 1) % pt_size].x(), mPolygons[i][(j + 1) % pt_size].y()) });
			voronoi_builder.insert_segment(mPolygons[i][j].x(), mPolygons[i][j].y(), mPolygons[i][(j+1)%pt_size].x(), mPolygons[i][(j + 1) % pt_size].y());
		}
	}
	voronoi_builder.construct(&mVoronoiDiagram);
	///Voronoi±ß
	voronoi_diagram::const_edge_iterator edge_iter = mVoronoiDiagram.edges().begin();
	for (; edge_iter != mVoronoiDiagram.edges().end(); ++edge_iter)
	{
		edge_iter->color(0);
		if (edge_iter->is_primary() && edge_iter->is_finite())
		{
			std::size_t index = edge_iter->cell()->source_index();
			std::size_t twin_index = edge_iter->twin()->cell()->source_index();
			if (boost::geometry::distance(segments[index], segments[twin_index]) > gte::ZOOM_IN)
			{
				const voronoi_vertex* vertex0 = edge_iter->vertex0();
				const voronoi_vertex* vertex1 = edge_iter->vertex1();
				gte::Point2i pt0(vertex0->x(), vertex0->y());
				gte::Point2i pt1(vertex1->x(), vertex1->y());
				if (mPolygons.within(pt0) && mPolygons.within(pt1))
				{
					edge_iter->color(1);
				}
			}
		}
	}
	gte::Polylines2i* polylines = new gte::Polylines2i;
	edge_iter = mVoronoiDiagram.edges().begin();
	std::map<const voronoi_edge*, bool> flag;
	for (; edge_iter != mVoronoiDiagram.edges().end(); ++edge_iter)
	{
		if (flag[&*edge_iter] || flag[&*edge_iter->twin()])
			continue;

		if (1 == edge_iter->color())
		{
			std::deque<const voronoi_edge*> edges;
			flag[&*edge_iter] = true;
			edges.push_back(&*edge_iter);
			while (true)
			{
				const voronoi_edge* cur_edge = edges.front();
				const voronoi_edge* next_edge = NULL;
				int count = 0;
				do {
					cur_edge = cur_edge->rot_prev();
					if (1 == cur_edge->color())
					{
						++count;
						if (!flag[cur_edge] && !flag[cur_edge->twin()])
							next_edge = cur_edge;
					}
				} while (cur_edge != edges.front());
				if (2 == count)
				{
					if (NULL == next_edge || next_edge == edges.back())
						break;
					edges.push_front(next_edge->twin());
					flag[edges.front()] = true;
					flag[edges.front()->twin()] = true;
				}
				else {
					break;
				}
			}
			while (true)
			{
				const voronoi_edge* cur_edge = edges.back();
				const voronoi_edge* next_edge = NULL;
				int count = 0;
				do {
					cur_edge = cur_edge->rot_next();
					if (1 == cur_edge->color())
					{
						++count;
						if (!flag[cur_edge] && !flag[cur_edge->twin()])
							next_edge = cur_edge;
					}
				} while (cur_edge != edges.back());
				if (2 == count)
				{
					if (NULL == next_edge || next_edge == edges.front())
						break;
					edges.push_back(next_edge);
					flag[edges.back()] = true;
					flag[edges.back()->twin()] = true;
					
				}
				else {
					break;
				}
			}
			gte::Polyline2i polyline;
			size_t edges_size = edges.size();
			for (size_t k = 0; k < edges_size; k++)
			{
				gte::Point2i pt0(edges[k]->vertex0()->x(), edges[k]->vertex0()->y());
				if(polyline.empty())
					polyline.push_back(pt0);
				else {
					if (polyline.back() != pt0)
						polyline.push_back(pt0);

				}
				gte::Point2i pt1(edges[k]->vertex1()->x(), edges[k]->vertex1()->y());
				if (polyline.back() != pt1)
					polyline.push_back(pt1);
			}
			if(polyline.size())
				polylines->push_back(polyline);
			
		}
	}
	mPolys = polylines;
}
