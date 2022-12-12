
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
	//
	gte::MultiPoints2i* fork_pts = new gte::MultiPoints2i;
	gte::MultiPoints2i* end_pts = new gte::MultiPoints2i;
	gte::MultiPoints2i* skl_pts = new gte::MultiPoints2i;
	gte::MultiSegments2i* branch_segms = new gte::MultiSegments2i;

	//! 中心点，端点和分叉点。
	size_t segm_size = segments.size();
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
				//double dist = 1.0;
				//if ((boost::polygon::SOURCE_CATEGORY_INITIAL_SEGMENT == category || boost::polygon::SOURCE_CATEGORY_REVERSE_SEGMENT == category)
				//&& (boost::polygon::SOURCE_CATEGORY_INITIAL_SEGMENT == twin_category || boost::polygon::SOURCE_CATEGORY_REVERSE_SEGMENT == twin_category))
				//{
				//	dist = boost::geometry::dot_product(segments[index].toVector(), segments[twin_index].toVector());
				//	if (dist <= 0.0)
				//	{
				//		++count;
				//	}
				//}
				//else {
				//	gte::Segment2i segm(gte::Point2i(edge->vertex0()->x(), edge->vertex0()->y()), gte::Point2i(edge->vertex1()->x(), edge->vertex1()->y()));
				//	if (boost::polygon::SOURCE_CATEGORY_INITIAL_SEGMENT == category || boost::polygon::SOURCE_CATEGORY_REVERSE_SEGMENT == category)
				//	{
				//		dist = boost::geometry::dot_product(segments[index].toVector(), segm.toVector());
				//		double len = boost::geometry::distance(segments[index].p0(), segments[index].p1()) * boost::geometry::distance(segm.p0(),segm.p1());
				//		double angle = std::abs(dist / len);
				//		if (std::abs(angle - 1.0) < 0.1)
				//		{
				//			++count;
				//		}
				//		/*gte::Point2i pt = segments[twin_index].p0();
				//		if (boost::polygon::SOURCE_CATEGORY_SEGMENT_END_POINT == twin_category)
				//			pt = segments[twin_index].p1();
				//		double d0 = boost::geometry::distance(pt,segm);
				//		double d1 = boost::geometry::distance(segments[index], segm);
				//		if (d0 == d1)
				//			++count;*/

				//		/*dist = boost::geometry::dot_product(segments[index].toVector(), segments[(twin_index + 1) % segm_size].toVector());
				//		if (dist < 0.0)
				//		{
				//			++count;
				//		}*/
				//	}
				//	if (boost::polygon::SOURCE_CATEGORY_INITIAL_SEGMENT == twin_category || boost::polygon::SOURCE_CATEGORY_REVERSE_SEGMENT == twin_category)
				//	{
				//		dist = boost::geometry::dot_product(segments[twin_index].toVector(), segm.toVector());
				//		double len = boost::geometry::distance(segments[twin_index].p0(), segments[twin_index].p1()) * boost::geometry::distance(segm.p0(), segm.p1());
				//		double angle = std::abs(dist / len);
				//		if (std::abs(angle - 1.0) < 0.1)
				//		{
				//			++count;
				//		}

				//	}
				//	if ((boost::polygon::SOURCE_CATEGORY_SEGMENT_START_POINT == category || boost::polygon::SOURCE_CATEGORY_SEGMENT_END_POINT == category)
				//		&& (boost::polygon::SOURCE_CATEGORY_SEGMENT_START_POINT == twin_category || boost::polygon::SOURCE_CATEGORY_SEGMENT_END_POINT == twin_category))
				//	{
				//		/*gte::Segment2i segm(gte::Point2i(edge->vertex0()->x(), edge->vertex0()->y()), gte::Point2i(edge->vertex1()->x(), edge->vertex1()->y()));
				//		gte::Point2i pt = segments[index].p0();
				//		if (boost::polygon::SOURCE_CATEGORY_SEGMENT_END_POINT == category)
				//			pt = segments[index].p1();
				//		gte::Point2i twin_pt = segments[twin_index].p0();
				//		if (boost::polygon::SOURCE_CATEGORY_SEGMENT_END_POINT == twin_category)
				//			twin_pt = segments[twin_index].p1();

				//		double d0 = boost::geometry::distance(pt, segm);
				//		double d1 = boost::geometry::distance(twin_pt, segm);
				//		if (std::abs(d0 - d1)<1000.0)
				//			++count;*/

				//		++count;
				//	}
				//}

				gte::Point2i pt = boost::geometry::cross_product(segments[index].toVector(), segments[twin_index].toVector());
				//double dist = boost::geometry::;
				double dist = boost::geometry::dot_product(segments[index].toVector(), segments[twin_index].toVector());
				if (dist < 0.0)
				{
					++count;
				}
				else {
					dist = boost::geometry::dot_product(segments[(index+1)% segm_size].toVector(), segments[(twin_index+1)% segm_size].toVector());
					if (dist < 0.0)
					{
						++count;
					}
					else {
						/*if (mPolygons.within(gte::Point2i(edge->vertex1()->x(), edge->vertex1()->y())))
							++count;*/
					}
				}
				
				edge = edge->rot_next();
			} while (edge != vt->incident_edge());
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
	}
	mPolys = end_pts;
	return ;
	//! 遍历分支
	std::map<const voronoi_vertex*, bool> vertex_flag;
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
						branch.push_back(nvt);
						vertex_flag[nvt] = true;
						have = true;
						break;
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
			bool have = false;
			do
			{
				if (edge->is_primary() && edge->is_finite())
				{
					const voronoi_vertex* nvt = edge->vertex1();
					if (MAT_UNKNOWN != nvt->color())
					{
						if (MAT_VERTEX_SKL == nvt->color() && vertex_flag[nvt])
						{
							;
						}
						else {
							branch.push_front(nvt);
							vertex_flag[nvt] = true;
							have = true;
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
	//! 中心线
	voronoi_diagram::const_edge_iterator edge_iter = mVoronoiDiagram.edges().begin();
	for (; edge_iter != mVoronoiDiagram.edges().end(); ++edge_iter)
	{
		edge_iter->color(MAT_UNKNOWN);
		edge_iter->cell()->color(0);
		if (edge_iter->is_primary() && edge_iter->is_finite())
		{
			std::size_t index = edge_iter->cell()->source_index();
			std::size_t twin_index = edge_iter->twin()->cell()->source_index();
			//! 对应支撑线段方向相反
			double dist = boost::geometry::dot_product(segments[index].toVector(), segments[twin_index].toVector());
			if(dist <= 0.0)
			{
				gte::Point2i pt0(edge_iter->vertex0()->x(), edge_iter->vertex0()->y());
				gte::Point2i pt1(edge_iter->vertex1()->x(), edge_iter->vertex1()->y());
				if (mPolygons.within(pt0) && mPolygons.within(pt1))
				{
					edge_iter->color(MAT_EDGE_SKL);
					edge_iter->cell()->color(1);

					edge_iter->vertex0()->color();
					/*double dist = boost::geometry::dot_product(segments[index].toVector(), segments[twin_index].toVector());
					if (dist >= 0.0)
					{
						std::cout << pt0.x() << std::endl;
					}*/
				}
			}
		}
	}
	//! 顺序中心线折线段
	gte::Polylines2i* polylines = new gte::Polylines2i;
	
	std::map<const voronoi_edge*, bool> flag;
	std::map<const voronoi_cell*, bool> cell_flag;
	std::deque<std::deque<const voronoi_edge*>> mat_tmp_edges;

	edge_iter = mVoronoiDiagram.edges().begin();
	for (; edge_iter != mVoronoiDiagram.edges().end(); ++edge_iter)
	{
		if (MAT_EDGE_SKL == edge_iter->color())
		{
			const voronoi_edge* one_edge = &*edge_iter;
			std::deque<const voronoi_edge*> edges;
			
			travelInCell(one_edge, edges);

			bool trval = false;
			do
			{
				trval = backNextTravel(edges.back(), edges);
			} while (trval);
			do
			{
				trval = frontPrevTravel(edges.front(), edges);
			} while (trval);

			for (auto edge : edges)
			{
				edge->color(0);
				edge->twin()->color(0);
			}
			mat_tmp_edges.push_back(edges);
			/*if (edges.size() > 420)
				break;*/
		}
	}
	//voronoi_diagram::const_cell_iterator cell_iter = mVoronoiDiagram.cells().begin();
	//for (; cell_iter != mVoronoiDiagram.cells().end(); ++cell_iter)
	//{
	//	if (1 == cell_iter->color())
	//	{
	//		if (cell_flag[&*cell_iter])
	//			continue;
	//		//! cell的第一个骨架边
	//		const voronoi_edge* one_edge = NULL;
	//		const voronoi_edge* edge = cell_iter->incident_edge();
	//		do {
	//			if (MAT_EDGE_SKL == edge->color())
	//			{
	//				one_edge = edge;
	//				break;
	//			}
	//			edge = edge->next();
	//		} while (edge != cell_iter->incident_edge());
	//		
	//		//! 同cell内的其它顺序骨架边
	//		if (NULL == one_edge)
	//			continue;
	//		std::deque<const voronoi_edge*> edges;
	//		travelInCell(one_edge, edges);

	//		/*bool trval = false;
	//		do
	//		{
	//			trval = backNextTravel(edges.back(), edges);
	//		} while (trval);
	//		do
	//		{
	//			trval = frontPrevTravel(edges.front(), edges);
	//		} while (trval);*/
	//		for (auto edge : edges)
	//		{
	//			edge->color(0);
	//			edge->twin()->color(0);
	//			cell_flag[edge->cell()] = true;
	//			cell_flag[edge->twin()->cell()] = true;
	//		}
	//		mat_tmp_edges.push_back(edges);
	//	}
	//}

	std::deque<std::deque<const voronoi_edge*>> mat_edges= mat_tmp_edges;
	//connectCellMATEdge(mat_tmp_edges, mat_edges);

	for (size_t i = 0; i < mat_edges.size(); i++)
	{
		if (i != 0)
			continue;

		gte::Polyline2i polyline;
		size_t edges_size = mat_edges[i].size();
		for (size_t k = 0; k < edges_size; k++)
		{
			gte::Point2i pt0(mat_edges[i][k]->vertex0()->x(), mat_edges[i][k]->vertex0()->y());
			if (polyline.empty())
				polyline.push_back(pt0);
			else {
				if (polyline.back() != pt0)
					polyline.push_back(pt0);
			}
			gte::Point2i pt1(mat_edges[i][k]->vertex1()->x(), mat_edges[i][k]->vertex1()->y());
			if (polyline.back() != pt1)
				polyline.push_back(pt1);
		}
		if (polyline.size())
			polylines->push_back(polyline);
	}
	
/*
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
						if (!flag[cur_edge])
							next_edge = cur_edge;
					}
				} while (cur_edge != edges.front());
				if (2 == count)
				{
					if (NULL == next_edge || next_edge->twin() == edges.back())
						break;
					edges.push_front(next_edge->twin());
					flag[edges.front()] = true;
					//flag[edges.front()->twin()] = true;
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
						if (!flag[cur_edge])
							next_edge = cur_edge;
					}
				} while (cur_edge != edges.back());
				if (2 == count)
				{
					if (NULL == next_edge || next_edge == edges.front())
						break;
					edges.push_back(next_edge);
					flag[edges.back()] = true;
					//flag[edges.back()->twin()] = true;
					
				}
				else {
					break;
				}
			}
			mat_tmp_edges.push_back(edges);
			////
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
*/
	//! 中心线折线段连接
	//std::deque<std::deque<const voronoi_edge*>> mat_edges;
	//while (!mat_tmp_edges.empty())
	//{
	//	mat_edges.push_back(mat_tmp_edges.front());
	//	mat_tmp_edges.pop_front();
	//	//
	//	std::deque<std::deque<const voronoi_edge*>>::iterator matply_iter = mat_tmp_edges.begin();
	//	for (; matply_iter != mat_tmp_edges.end(); matply_iter++)
	//	{
	//		;
	//	}
	//}
	
	//! 
	mPolys = polylines;
}
bool MedialAxisTransform::backNextTravel(const voronoi_edge* src, std::deque<const voronoi_edge*>& dst)
{
	//! 分支
	if (countMATEdge(src->next()) > 2)
	{
		std::cout << "fork edge" << std::endl;
		return false;
	}
	
	//! 骨架
	const voronoi_edge* one_edge = NULL;
	const voronoi_edge* cur_edge = src->next();
	if (MAT_EDGE_SKL == cur_edge->color())
	{
		one_edge = cur_edge;
	}
	else {
		do
		{
			cur_edge = cur_edge->rot_next();
			if (MAT_EDGE_SKL == cur_edge->color() && cur_edge != src->twin() && cur_edge != src)
			{
				one_edge = cur_edge;
				break;
			}
		} while (cur_edge != src->next());
	}
	if (NULL == one_edge)
	{
		std::cout << "end edge" << std::endl;
		return false;
	}
	//! 
	std::deque<const voronoi_edge*> edges;
	edges.push_back(cur_edge);
	cur_edge->color(MAT_EDGE_SKL_BRANCH);
	cur_edge->twin()->color(MAT_EDGE_SKL_BRANCH);
	cur_edge = one_edge;
	{
		const voronoi_edge* tmp_edge = cur_edge->next();
		do
		{
			if (MAT_EDGE_SKL == tmp_edge->color())
			{
				if (countMATEdge(tmp_edge) > 2)
					break;
				edges.push_back(tmp_edge);
				tmp_edge->color(MAT_EDGE_SKL_BRANCH);
				tmp_edge->twin()->color(MAT_EDGE_SKL_BRANCH);
			}
			else {
				break;
			}
			tmp_edge = tmp_edge->next();
		} while (tmp_edge != edges.front());

		tmp_edge = cur_edge->prev();
		do
		{
			if (MAT_EDGE_SKL == tmp_edge->color())
			{
				if (countMATEdge(tmp_edge) > 2)
					break;
				edges.push_back(tmp_edge);
				tmp_edge->color(MAT_EDGE_SKL_BRANCH);
				tmp_edge->twin()->color(MAT_EDGE_SKL_BRANCH);
			}
			else {
				break;
			}
			tmp_edge = tmp_edge->prev();
		} while (tmp_edge != edges.back());
	}
	//travelInCell(cur_edge, edges);
	if (edges.empty())
		return false;
	for (size_t i = 0; i < edges.size(); i++)
	{
		dst.push_back(edges[i]);
	}
	return true;
}
bool MedialAxisTransform::frontPrevTravel(const voronoi_edge* src, std::deque<const voronoi_edge*>& dst)
{
	if (countMATEdge(src) > 2)
		return false;

	const voronoi_edge* one_edge = NULL;
	const voronoi_edge* cur_edge = src->twin();
	//if (cur_edge->color())
	{
		//one_edge = cur_edge;
	}
	//else {
		do
		{
			cur_edge = cur_edge->rot_next();
			int color = cur_edge->color();
			if (MAT_EDGE_SKL == cur_edge->color() && cur_edge != src->twin() && cur_edge != src)
			{
				one_edge = cur_edge;
				break;
			}
		} while (cur_edge != src->twin());
//	}
	if (NULL == one_edge)
		return false;
	//! 
	std::deque<const voronoi_edge*> edges;
	edges.push_back(cur_edge);
	cur_edge->color(MAT_EDGE_SKL_BRANCH);
	cur_edge->twin()->color(MAT_EDGE_SKL_BRANCH);
	cur_edge = one_edge;
	{
		const voronoi_edge* tmp_edge = cur_edge->next();
		do
		{
			if (MAT_EDGE_SKL == tmp_edge->color())
			{
				if (countMATEdge(tmp_edge) > 2)
					break;
				edges.push_back(tmp_edge);
				tmp_edge->color(MAT_EDGE_SKL_BRANCH);
				tmp_edge->twin()->color(MAT_EDGE_SKL_BRANCH);
			}
			else {
				break;
			}
			tmp_edge = tmp_edge->next();
		} while (tmp_edge != edges.front());

		tmp_edge = cur_edge->prev();
		do
		{
			if (MAT_EDGE_SKL == tmp_edge->color())
			{
				if (countMATEdge(tmp_edge) > 2)
					break;
				edges.push_front(tmp_edge);
				tmp_edge->color(MAT_EDGE_SKL_BRANCH);
				tmp_edge->twin()->color(MAT_EDGE_SKL_BRANCH);
			}
			else {
				break;
			}
			tmp_edge = tmp_edge->prev();
		} while (tmp_edge != edges.back());
	}
	//travelInCell(cur_edge, edges);
	if (edges.empty())
		return false;
	for (size_t i = 0; i < edges.size(); i++)
	{
		dst.push_front(edges[i]);
	}
	
	return true;

}
void MedialAxisTransform::connectCellMATEdge(std::deque<std::deque<const voronoi_edge*>>& src, std::deque<std::deque<const voronoi_edge*>>& dst)
{
	typedef std::deque<std::deque<const voronoi_edge*>>::iterator iterator;
	while (!src.empty())
	{
		std::deque<const voronoi_edge*> edges;
		edges = src.front();
		src.pop_front();
		
		for (iterator iter = src.begin(); iter!= src.end();)
		{
			if (isConnect(edges.back(), iter->front()))
			{
				edges.insert(edges.end(), iter->begin(),iter->end());
				iter = src.erase(iter);
			}
			else if(isConnect(edges.back(), iter->back()))
			{
				edges.insert(edges.end(), iter->rbegin(), iter->rend());
				iter = src.erase(iter);
			}
			else if (isConnect(edges.front(), iter->front()))
			{
				edges.insert(edges.begin(), iter->begin(), iter->end());
				iter = src.erase(iter);
			}
			else if (isConnect(edges.front(), iter->back()))
			{
				edges.insert(edges.begin(), iter->rbegin(), iter->rend());
				iter = src.erase(iter);
			}
			else {
				++iter;
			}
		}

		dst.push_back(edges);
	}
}
bool MedialAxisTransform::isConnect(const voronoi_edge* src, const voronoi_edge* dst)
{
	if (countMATEdge(src) > 2)
		return false;

	const voronoi_edge* cur_edge = src->next();
	do
	{
		cur_edge = cur_edge->rot_next();
		if (cur_edge == dst || cur_edge == dst->twin())
			return true;
	} while (cur_edge != src->next());

	return false;
}

void MedialAxisTransform::travelInCell(const voronoi_edge* src, std::deque<const voronoi_edge*>& dst)
{
	if (MAT_EDGE_SKL == src->color())
	{
		dst.push_back(src);
		src->color(MAT_EDGE_SKL_BRANCH);
		src->twin()->color(MAT_EDGE_SKL_BRANCH);
		const voronoi_edge* cur_edge = src->next();
		do
		{
			if (MAT_EDGE_SKL == cur_edge->color())
			{
				if (countMATEdge(cur_edge) > 2)
					break;
				dst.push_back(cur_edge);
				cur_edge->color(MAT_EDGE_SKL_BRANCH);
				cur_edge->twin()->color(MAT_EDGE_SKL_BRANCH);
			}
			else {
				break;
			}
			cur_edge = cur_edge->next();
		} while (cur_edge != dst.front());

		cur_edge = src->prev();
		do
		{
			if (MAT_EDGE_SKL == cur_edge->color())
			{
				if (countMATEdge(cur_edge) > 2)
					break;
				dst.push_front(cur_edge);
				cur_edge->color(MAT_EDGE_SKL_BRANCH);
				cur_edge->twin()->color(MAT_EDGE_SKL_BRANCH);
			}
			else {
				break;
			}
			cur_edge = cur_edge->prev();
		} while (cur_edge != dst.back());
	}
}
size_t MedialAxisTransform::countMATEdge(const voronoi_edge* src)
{
	size_t count = 0;
	const voronoi_edge* cur_edge = src;
	do
	{
		cur_edge = cur_edge->rot_next();
		if (cur_edge->color())
			++count;
	} while (cur_edge != src);
	return count;

	/*size_t count0 = 0;
	cur_edge = src->twin();
	do
	{
		cur_edge = cur_edge->rot_next();
		if (cur_edge->color())
			++count0;
	} while (cur_edge != src->twin());
	return count> count0? count: count0;*/
}
