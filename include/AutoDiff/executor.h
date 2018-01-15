//
// Created by Administrator on 2018/1/15.
//

#ifndef AUTODIFF_EXECUTOR_H
#define AUTODIFF_EXECUTOR_H

#include <vector>
#include <map>
#include "node.h"
#include "toposort.h"
namespace ad {
    class FeedDict
    {
    public:
        Ctype& operator [](const Node &key) {
            return feed_dict_[key.get_id()];
        }

    private:
        std::map<size_t, Ctype> feed_dict_;
    };


    class Executor
    {
    public:
        Executor(const std::vector<Node>& eval_node_list) : eval_node_list_(eval_node_list) {
            topo_order_ = find_topo_sort(eval_node_list_);
        }

        std::vector<Ctype> run(const FeedDict &feed_dict)
        {
            auto node_to_val_map = feed_dict;
            std::vector<Ctype>vals;

            for (auto &node : topo_order_)
            {
                if (node.is_placeholder)
                    continue;
                for (auto &n : node.inputs)
                    vals.push_back(node_to_val_map[n]);
                node_to_val_map[node] = node.forward(node, vals);
                vals.clear();
            }
            std::vector<Ctype> node_val_results;
            for (auto node : eval_node_list_)
                node_val_results.push_back(node_to_val_map[node]);
            return node_val_results;
        }

    private:
        std::vector<Node> eval_node_list_;
        std::vector<Node> topo_order_;
    };
}


#endif //AUTODIFF_EXECUTOR_H
