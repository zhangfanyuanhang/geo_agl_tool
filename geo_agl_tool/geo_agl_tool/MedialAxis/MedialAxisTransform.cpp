
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
			if(dist < 0.0)
			{
				//gte::Point2i pt0(edge_iter->vertex0()->x(), edge_iter->vertex0()->y());
				//gte::Point2i pt1(edge_iter->vertex1()->x(), edge_iter->vertex1()->y());
				//if (mPolygons.within(pt0) && mPolygons.within(pt1))
				{
					edge_iter->color(MAT_EDGE_SKL);
					edge_iter->cell()->color(1);
				}
			}
		}
	}
	//! 顺序中心线折线段
	gte::Polylines2i* polylines = new gte::Polylines2i;
	edge_iter = mVoronoiDiagram.edges().begin();
	std::map<const voronoi_edge*, bool> flag;
	std::map<const voronoi_cell*, bool> cell_flag;
	std::deque<std::deque<const voronoi_edge*>> mat_tmp_edges;
	voronoi_diagram::const_cell_iterator cell_iter = mVoronoiDiagram.cells().begin();
	for (; cell_iter != mVoronoiDiagram.cells().end(); ++cell_iter)
	{
		if (1 == cell_iter->color())
		{
			if (cell_flag[&*cell_iter])
				continue;
			//! cell的第一个骨架边
			const voronoi_edge* one_edge = NULL;
			const voronoi_edge* edge = cell_iter->incident_edge();
			do {
				if (MAT_EDGE_SKL == edge->color())
				{
					one_edge = edge;
					break;
				}
				edge = edge->next();
			} while (edge != cell_iter->incident_edge());
			
			//! 同cell内的其它顺序骨架边
			if (NULL == one_edge)
				continue;

			std::deque<const voronoi_edge*> edges;
			travelInCell(one_edge, edges);

			bool trval = false;
			do
			{
				/*if (countMATEdge(edges.back()) > 2)
					break;*/
				trval = backNextTravel(edges.back(), edges);
			} while (trval);
			do
			{
				/*if (countMATEdge(edges.front()) > 2)
					break;*/
				trval = frontPrevTravel(edges.front(), edges);
			} while (trval);
			for (auto edge : edges)
			{
				edge->color(0);
				edge->twin()->color(0);
				cell_flag[edge->cell()] = true;
				cell_flag[edge->twin()->cell()] = true;
			}
			mat_tmp_edges.push_back(edges);
		}
	}
	std::deque<std::deque<const voronoi_edge*>> mat_edges= mat_tmp_edges;
	//connectCellMATEdge(mat_tmp_edges, mat_edges);

	for (size_t i = 0; i < mat_edges.size(); i++)
	{
		
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
	//const voronoi_edge* edge = src->next()->twin();
	if (countMATEdge(src->next()) > 2)
		return false;
	const voronoi_edge* cur_edge = src->next();
	do
	{
		cur_edge = cur_edge->rot_next();
		if (cur_edge->color())
			break;
	} while (cur_edge != src->next());
	if (!cur_edge->color())
		return false;
	std::deque<const voronoi_edge*> edges;
	travelInCell(cur_edge, edges);
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
	if (countMATEdge(src->prev()) > 2)
		return false;
	const voronoi_edge* cur_edge = src->prev();
	do
	{
		cur_edge = cur_edge->rot_prev();
		if (cur_edge->color())
			break;
	} while (cur_edge != src->prev());
	if (!cur_edge->color())
		return false;
	std::deque<const voronoi_edge*> edges;
	travelInCell(cur_edge, edges);
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
	if (src->color())
	{
		if (MAT_EDGE_SKL_BRANCH != src->color())
		{
			src->color(MAT_EDGE_SKL_BRANCH);
			dst.push_back(src);
		}
		else {
			return;
		}
		const voronoi_edge* cur_edge = src->next();
		do
		{
			if (cur_edge->color())
			{
				if (countMATEdge(cur_edge) > 2)
					break;
				if (MAT_EDGE_SKL_BRANCH != cur_edge->color())
				{
					cur_edge->color(MAT_EDGE_SKL_BRANCH);
					dst.push_back(cur_edge);
				}
				else {
					break;
				}
			}
			else {
				break;
			}
			cur_edge = cur_edge->next();
		} while (cur_edge != dst.front());

		cur_edge = src->prev();
		do
		{
			if (cur_edge->color())
			{
				if (countMATEdge(cur_edge) > 2)
					break;
				if (MAT_EDGE_SKL_BRANCH != cur_edge->color())
				{
					cur_edge->color(MAT_EDGE_SKL_BRANCH);
					dst.push_back(cur_edge);
				}
				else {
					break;
				}
			}
			else {
				break;
			}
			cur_edge = cur_edge->prev();
		} while (cur_edge != dst.back());
	}
	else {
		const voronoi_edge* cur_edge = src;
		do
		{
			if (cur_edge->color())
			{
				if (countMATEdge(cur_edge) > 2)
					break;
				if (MAT_EDGE_SKL_BRANCH != cur_edge->color())
				{
					cur_edge->color(MAT_EDGE_SKL_BRANCH);
					dst.push_back(cur_edge);
				}
			}
			cur_edge = cur_edge->next();
		} while (cur_edge != src);
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

	size_t count0 = 0;
	cur_edge = src->twin();
	do
	{
		cur_edge = cur_edge->rot_next();
		if (cur_edge->color())
			++count0;
	} while (cur_edge != src->twin());

	return count> count0? count: count0;
}
