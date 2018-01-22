//
// Created by Administrator on 2018/1/15.
//

#ifndef AUTODIFF_NODE_H
#define AUTODIFF_NODE_H

#include <vector>
#include <string>
#include <functional>


namespace ad {
	// 常数的类型
	typedef float Ctype;

	class Node;
	typedef std::function<Ctype(const Node&, const std::vector<Ctype>&)> forward_func;
	typedef std::function<std::vector<Node>(const Node&, const Node&)> backward_func;

	class Node
	{
	public:
		Node() :id_(id_base_++) {}

		size_t            get_id() const { return id_; }

		forward_func      forward;
		backward_func     backward;
		std::vector<Node> inputs;
		bool              is_placeholder;
		Ctype             const_attr;
		std::string       name;
	private:
		size_t id_;
		static size_t id_base_;
	};

	size_t Node::id_base_ = 0;
}




#endif //AUTODIFF_NODE_H
