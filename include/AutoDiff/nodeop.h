//
// Created by Administrator on 2018/1/15.
//

#ifndef AUTODIFF_NODEOP_H
#define AUTODIFF_NODEOP_H

#include "node.h"
#include "operator.h"

namespace ad {

    Node operator-(const Node &node) {
        return NegOp::initialize(node);
    }

    Node operator + (const Node& a, const Node& b)
    {
        return AddOp::initialize(a, b);
    }

    Node operator + (const Node& a, Ctype const_val)
    {
        return AddByconstOp::initialize(a, const_val);
    }

    Node operator + (Ctype const_val, const Node& a)
    {
        return a + const_val;
    }

    Node operator - (const Node& a, const Node& b)
    {
        return SubOp::initialize(a, b);
    }

    Node operator - (const Node& a, Ctype const_val)
    {
        return SubByconstOp::initialize(a, const_val);
    }

    Node operator - (Ctype const_val, const Node& a)
    {
        return RSubByconstOp::initialize(a, const_val);
    }

    Node operator * (const Node& a, const Node& b)
    {
        return MulOp::initialize(a, b);
    }

    Node operator * (const Node& a, Ctype const_val)
    {
        return  MulByconstOp::initialize(a, const_val);
    }

    Node operator * (Ctype const_val, const Node& a)
    {
        return a * const_val;
    }

    Node operator / (const Node& a, const Node& b)
    {
        return DivOp::initialize(a, b);
    }

    Node operator / (const Node& a, Ctype const_val)
    {
        return DivByconstOp::initialize(a, const_val);
    }

    Node operator / (Ctype const_val, const Node& a)
    {
        return RDivByconstOp::initialize(a, const_val);
    }

}

#endif //AUTODIFF_NODEOP_H
