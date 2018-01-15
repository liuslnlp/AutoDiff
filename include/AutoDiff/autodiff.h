//
// Created by Administrator on 2018/1/15.
//

#ifndef AUTODIFF_AUTODIFF_H
#define AUTODIFF_AUTODIFF_H


// 基于静态计算图的自动微分法.
// Automatic differentiation based on static computational graph.
//
// Author: Shilei Liu.
// Date: 2018/1/9.
// Last modified date: 2018/1/9.
//
#include <algorithm>
#include <numeric>
#include "node.h"
#include "nodeop.h"
#include "operator.h"
#include "executor.h"

namespace ad {
	Node Variable(const std::string &name)
	{
		Node new_node = PlaceholderOp::initialize();
		new_node.name = name;
		return new_node;
	}


	Node sum_node_list(const std::vector<Node> &node_list)
	{
		return std::accumulate(node_list.begin(), node_list.end(), Node());
	}

	std::vector<Node> map_get(std::map<size_t, std::vector<Node>> &m, size_t id) {
		if (m.find(id) == m.end())
			return std::vector<Node>();
		else
			return m[id];
	}



	std::vector<Node> Gradients(const Node& output_node, const std::vector<Node> &node_list)
	{
		std::map<size_t, std::vector<Node>> node_to_output_grads_list;

		node_to_output_grads_list[output_node.get_id()]
			= std::vector<Node>{ OnesLikeOp::initialize(output_node) };
		std::map<size_t, Node> node_to_output_grad;
		std::vector<Node> topo_order = find_topo_sort(std::vector<Node>{output_node});
		for (auto it = topo_order.rbegin(); it != topo_order.rend(); ++it)
		{
			Node grad = std::move(sum_node_list(node_to_output_grads_list[it->get_id()]));
			node_to_output_grad[it->get_id()] = grad;
			std::vector<Node> grads = it->backward(*it, grad);
			for (size_t i = 0; i < it->inputs.size(); ++i)
			{
				Node& ch = it->inputs[i];
				std::vector<Node> grads_list = map_get(node_to_output_grads_list, ch.get_id());
				grads_list.push_back(grads[i]);
				node_to_output_grads_list[ch.get_id()] = grads_list;
			}
		}
		std::vector<Node> grad_node_list;
		for (auto &node : node_list)
			grad_node_list.push_back(node_to_output_grad[node.get_id()]);
		return grad_node_list;
	}


}



#endif //AUTODIFF_AUTODIFF_H
