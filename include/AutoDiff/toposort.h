//
// Created by Administrator on 2018/1/15.
//

#ifndef AUTODIFF_TOPOSORT_H
#define AUTODIFF_TOPOSORT_H

#include <unordered_set>
#include <vector>
#include "node.h"

namespace ad {
	void topo_sort_dfs(const Node &node, std::unordered_set<size_t> &visited, std::vector<Node> &topo_order)
	{
		if (visited.find(node.get_id()) != visited.end())
			return;
		visited.insert(node.get_id());
		for (auto &input_node : node.inputs)
			topo_sort_dfs(input_node, visited, topo_order);
		topo_order.push_back(node);
	}

	std::vector<Node> find_topo_sort(const std::vector<Node>&node_list)
	{
		std::unordered_set<size_t>visited;
		std::vector<Node>topo_order;
		for (auto &node : node_list)
			topo_sort_dfs(node, visited, topo_order);
		return topo_order;
	}
}



#endif //AUTODIFF_TOPOSORT_H
