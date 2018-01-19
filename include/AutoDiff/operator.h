//
// Created by Administrator on 2018/1/15.
//

#ifndef AUTODIFF_OPERATOR_H
#define AUTODIFF_OPERATOR_H

#include "node.h"
#include <sstream>
#include <string>
#include <cmath>
#include <assert.h>

namespace ad {
    template<typename T>
    std::string to_str(T t) {
        std::ostringstream buffer;
        buffer << t;
        return std::string(buffer.str());
    }

    struct NegOp {
        static Node initialize(const Node &node) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.inputs.push_back(node);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "-" + node.name;
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return -input_vals[0];
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{initialize(output_grad)};
        }
    };

    struct AddOp {
        static Node initialize(const Node &node_a, const Node &node_b) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.inputs.push_back(node_a);
            new_node.inputs.push_back(node_b);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + node_a.name + " + " + node_b.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return input_vals[0] + input_vals[1];
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{output_grad, output_grad};
        }
    };

    struct SubOp {
        static Node initialize(const Node &node_a, const Node &node_b) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.inputs.push_back(node_a);
            new_node.inputs.push_back(node_b);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + node_a.name + " - " + node_b.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return input_vals[0] - input_vals[1];
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{output_grad, NegOp::initialize(output_grad)};
        }
    };

    struct AddByconstOp {
        static Node initialize(const Node &node_a, Ctype const_val) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.const_attr = const_val;
            new_node.inputs.push_back(node_a);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + node_a.name + " + " + to_str(const_val) + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return input_vals[0] + node.const_attr;
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{output_grad};
        }
    };

    struct SubByconstOp {
        static Node initialize(const Node &node_a, Ctype const_val) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.const_attr = const_val;
            new_node.inputs.push_back(node_a);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + node_a.name + " - " + to_str(const_val) + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return input_vals[0] - node.const_attr;
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{output_grad};
        }
    };

    struct RSubByconstOp {
        static Node initialize(const Node &node_a, Ctype const_val) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.const_attr = const_val;
            new_node.inputs.push_back(node_a);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + to_str(const_val) + " - " + node_a.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return node.const_attr - input_vals[0];
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{NegOp::initialize(output_grad)};
        }
    };

    struct MulOp {
        static Node initialize(const Node &node_a, const Node &node_b) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.inputs.push_back(node_a);
            new_node.inputs.push_back(node_b);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + node_a.name + " * " + node_b.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return input_vals[0] + input_vals[1];
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{initialize(node.inputs[1], output_grad), initialize(node.inputs[1], output_grad)};
        }
    };

    struct DivOp {
        static Node initialize(const Node &node_a, const Node &node_b) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.inputs.push_back(node_a);
            new_node.inputs.push_back(node_b);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + node_a.name + "/" + node_b.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return input_vals[0] / input_vals[1];
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            auto left = initialize(output_grad, node.inputs[1]);
            auto denominator = MulOp::initialize(node.inputs[1], node.inputs[1]);
            auto numerator = MulOp::initialize(NegOp::initialize(output_grad), node.inputs[0]);
            auto right = initialize(numerator, denominator);
            return std::vector<Node>{left, right};
        }
    };

    struct MulByconstOp {
        static Node initialize(const Node &node_a, Ctype const_val) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.const_attr = const_val;
            new_node.inputs.push_back(node_a);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + node_a.name + " * " + to_str(const_val) + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return input_vals[0] * node.const_attr;
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{initialize(output_grad, node.const_attr)};
        }
    };

    struct DivByconstOp {
        static Node initialize(const Node &node_a, Ctype const_val) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.const_attr = const_val;
            new_node.inputs.push_back(node_a);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + node_a.name + "/" + to_str(const_val) + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return input_vals[0] / node.const_attr;
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{initialize(output_grad, node.const_attr)};
        }
    };

    struct RDivByconstOp {
        static Node initialize(const Node &node_a, Ctype const_val) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.const_attr = const_val;
            new_node.inputs.push_back(node_a);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "(" + to_str(const_val) + "/" + node_a.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return node.const_attr / input_vals[0];
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            auto denominator = MulOp::initialize(node.inputs[0], node.inputs[0]);
            auto numerator = MulByconstOp::initialize(NegOp::initialize(output_grad), node.const_attr);
            return std::vector<Node>{DivOp::initialize(numerator, denominator)};
        }
    };

    struct LogOp {
        static Node initialize(const Node &node) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.inputs.push_back(node);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "log(" + node.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return log(input_vals[0]);
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{DivOp::initialize(output_grad, node.inputs[0])};
        }
    };

    struct ExpOp {
        static Node initialize(const Node &node) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.inputs.push_back(node);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "exp(" + node.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return exp(input_vals[0]);
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{MulOp::initialize(output_grad, initialize(node.inputs[0]))};
        }
    };


    struct PlaceholderOp {
        static Node initialize() {
            Node new_node;
            new_node.is_placeholder = true;
            new_node.forward = forward;
            new_node.backward = backward;
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            assert(false);
            return 0;
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>();
        }
    };

    struct OnesLikeOp {
        static Node initialize(const Node &node_a) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.inputs.push_back(node_a);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "Oneslike(" + node_a.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return 1.0;
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{initialize(output_grad.inputs[0])};
        }
    };

    struct ZerosLikeOp {
        static Node initialize(const Node &node_a) {
            Node new_node;
            new_node.is_placeholder = false;
            new_node.inputs.push_back(node_a);
            new_node.forward = forward;
            new_node.backward = backward;
            new_node.name = "Zeroslike(" + node_a.name + ")";
            return new_node;
        }

        static Ctype forward(const Node &node, const std::vector<Ctype> &input_vals) {
            return 0;
        }

        static std::vector<Node> backward(const Node &node, const Node &output_grad) {
            return std::vector<Node>{initialize(output_grad.inputs[0])};
        }
    };

    Node exp(const Node &input_node){
        return ExpOp::initialize(input_node);
    }

    Node log(const Node &input_node){
        return LogOp::initialize(input_node);
    }
}


#endif //AUTODIFF_OPERATOR_H
