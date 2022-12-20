
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
	mGraphicPtr->initWindow(1600, 1000);
	mGraphicPtr->setSourceData(&mPolygons);
	mGraphicPtr->show(mPolys);
	mGraphicPtr->closeWindow();
}
void MedialAxisTransform::ConstructVoronoi()
{
	//! Voronoi图
	std::vector<gte::Segment2i> segments;
	std::map<size_t,std::pair<size_t, size_t>> segm_list;//线段之间的索引
	int segm_size = 0;
	size_t start_segm=0, end_segm=0;
	boost::polygon::voronoi_builder<int64_t, boost::polygon::detail::my_voronoi_ctype_traits<int64_t>> voronoi_builder;
	size_t ply_size = mPolygons.size();
	for (size_t i = 0; i < ply_size; i++)
	{
		size_t pt_size = mPolygons[i].size();
		for (size_t j = 0; j < pt_size; j++)
		{
			
			segments.push_back({ gte::Point2i(mPolygons[i][j].x(), mPolygons[i][j].y()), gte::Point2i(mPolygons[i][(j + 1) % pt_size].x(), mPolygons[i][(j + 1) % pt_size].y()) });
			voronoi_builder.insert_segment(mPolygons[i][j].x(), mPolygons[i][j].y(), mPolygons[i][(j+1)%pt_size].x(), mPolygons[i][(j + 1) % pt_size].y());
			segm_list[segm_size] = { segm_size -1,segm_size + 1 };
			++segm_size;
		}
		end_segm = segm_size - 1;
		segm_list[start_segm].first = segm_size - 1;
		segm_list[end_segm].second = segm_size - pt_size;
		start_segm = end_segm +1;
	}
	voronoi_builder.construct(&mVoronoiDiagram);
	//
	gte::MultiPoints2i* fork_pts = new gte::MultiPoints2i;
	gte::MultiPoints2i* end_pts = new gte::MultiPoints2i;
	gte::MultiPoints2i* skl_pts = new gte::MultiPoints2i;
	gte::MultiSegments2i* branch_segms = new gte::MultiSegments2i;
	//! 骨架点。
	for (voronoi_diagram::const_vertex_iterator vertex_iter = mVoronoiDiagram.vertices().begin(); 
		vertex_iter < mVoronoiDiagram.vertices().end(); vertex_iter++)
	{
		const voronoi_vertex* vt = &*vertex_iter;
		vt->color(MAT_UNKNOWN);
		if (!mPolygons.within(gte::Point2i(vt->x(), vt->y())))
			continue;
		
		const voronoi_edge* edge = vt->incident_edge();
		if (edge->is_primary() && edge->is_finite())
		{
			size_t count(0);
			do
			{
				std::size_t index = edge->cell()->source_index();
				std::size_t category = edge->cell()->source_category();
				std::size_t twin_index = edge->twin()->cell()->source_index();
				std::size_t twin_category = edge->twin()->cell()->source_category();
				
				gte::Segment2i segm = segments[index];
				if (boost::polygon::SOURCE_CATEGORY_SEGMENT_START_POINT == category)
				{
					segm = {segments[segm_list[index].first].p0(),segments[index].p1() };
				}
				if (boost::polygon::SOURCE_CATEGORY_SEGMENT_END_POINT == category)
				{
					segm = { segments[index].p0(),segments[segm_list[index].second].p1()};
				}
				gte::Segment2i twin_segm = segments[twin_index];
				if (boost::polygon::SOURCE_CATEGORY_SEGMENT_START_POINT == twin_category)
				{
					twin_segm = { segments[segm_list[twin_index].first].p0(),segments[twin_index].p1() };
				}
				if (boost::polygon::SOURCE_CATEGORY_SEGMENT_END_POINT == twin_category)
				{
					twin_segm = { segments[twin_index].p0(),segments[segm_list[twin_index].second].p1() };
				}
				{
					double dist = boost::geometry::dot_product(segm.toVector(), twin_segm.toVector());
					if (dist < 0.0)
					{
						++count;
					}
					else {
						int64_t len = boost::geometry::cross_product(segm.toVector(), twin_segm.toVector()).length();
						double dist = boost::geometry::distance(segm, twin_segm);
						if (len == 0 && dist > 0.0)
						{
							++count;
						}
					}
					
				}
				edge = edge->rot_next();
			} while (edge != vt->incident_edge());
			if(count)
				vt->color(MAT_VERTEX_SKL);
		}
	}
	//! 骨架端点和分叉点
	for (voronoi_diagram::const_vertex_iterator vertex_iter = mVoronoiDiagram.vertices().begin()
		; vertex_iter < mVoronoiDiagram.vertices().end(); vertex_iter++)
	{
		const voronoi_vertex* vt = &*vertex_iter;
		if (MAT_UNKNOWN == vt->color())
			continue;

		const voronoi_edge* edge = vt->incident_edge();
		size_t count = 0;
		if (edge->is_primary() && edge->is_finite())
		{
			do{
				if (edge->vertex1()->color())
				{
					++count;
				}
				edge = edge->rot_next();
			} while (edge != vt->incident_edge());
		}

		if (1 == count)
		{
			vt->color(MAT_VERTEX_END);
			end_pts->push_back(gte::Point2i(vt->x(), vt->y()));
		}
		if (2 == count)
		{
			vt->color(MAT_VERTEX_SKL);
			skl_pts->push_back(gte::Point2i(vt->x(), vt->y()));
		}
		if (2 < count)
		{
			vt->color(MAT_VERTEX_FORK);
			fork_pts->push_back(gte::Point2i(vt->x(), vt->y()));
		}
	}
	//mPolys = fork_pts;
	//return ;
	//! 遍历分支
	std::map<const voronoi_vertex*, bool> vertex_flag;
	std::map<const voronoi_edge*, bool> edge_flag;
	for (voronoi_diagram::const_vertex_iterator vertex_iter = mVoronoiDiagram.vertices().begin()
		; vertex_iter < mVoronoiDiagram.vertices().end(); vertex_iter++)
	{
		const voronoi_vertex* vt = &*vertex_iter;
		if (MAT_UNKNOWN == vt->color())
			continue;
		if (vertex_flag[vt])
			continue;

		std::deque<const voronoi_vertex*> branch;
		branch.push_back(vt);
		vertex_flag[vt] = true;
		//
		while (true)
		{
			vt = branch.back();
			const voronoi_edge* edge = vt->incident_edge();
			bool have = false;
			do
			{
				if (edge->is_primary() && edge->is_finite())
				{
					const voronoi_vertex* nvt = edge->vertex1();
					if (MAT_UNKNOWN != nvt->color())
					{
						if (MAT_VERTEX_FORK == nvt->color() || MAT_VERTEX_END == nvt->color())
						{
							branch.push_back(nvt);
							have = true;
							break;
						}
						else {
							if (!vertex_flag[nvt])
							{
								branch.push_back(nvt);
								vertex_flag[nvt] = true;
								have = true;
								break;
							}
						}
					}
				}
				edge = edge->rot_next();
			} while (edge != vt->incident_edge());
			if (!have)
			{
				break;
			}
			if (branch.back() == branch.front())
			{
				break;
			}
			if (MAT_VERTEX_END == branch.back()->color() || MAT_VERTEX_FORK == branch.back()->color())
			{
				break;
			}
		}
		//
		while (true)
		{
			if (MAT_VERTEX_END == branch.front()->color() || MAT_VERTEX_FORK == branch.front()->color())
			{
				break;
			}
			if (branch.back() == branch.front())
			{
				break;
			}

			vt = branch.front();
			const voronoi_edge* edge = vt->incident_edge();
			edge_flag[edge] = true;
			bool have = false;
			do
			{
				if (edge->is_primary() && edge->is_finite())
				{
					const voronoi_vertex* nvt = edge->vertex1();
					if (MAT_UNKNOWN != nvt->color())
					{
						if (MAT_VERTEX_FORK == nvt->color() || MAT_VERTEX_END == nvt->color())
						{
							branch.push_front(nvt);
							have = true;
							break;
						}
						else {
							if (vertex_flag[nvt])
							{
								if (nvt == branch.back())
									branch.push_front(nvt);
							}
							else {
								branch.push_front(nvt);
								vertex_flag[nvt] = true;
								have = true;
								break;
							}
							
						}
					}
				}
				edge = edge->rot_next();
			} while (edge != vt->incident_edge());
			if (!have)
			{
				break;
			}
		}
		mBranchs.push_back(branch);
	}

	gte::Polylines2i* plylines = new gte::Polylines2i;
	for (size_t i = 0; i < mBranchs.size(); i++)
	{
		gte::Polyline2i plyline;
		for (size_t j = 0; j < mBranchs[i].size(); j++)
		{
			plyline.push_back(gte::Point2i(mBranchs[i][j]->x(), mBranchs[i][j]->y()));
		}
		plylines->push_back(plyline);
	}
	mPolys = plylines;
	return;
}

