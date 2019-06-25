#include"node.h"

TypeNode EmptyNode::type()const{
    return TypeNode::EmptyNode;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, Date date) : comparison(cmp), value(date){}
TypeNode DateComparisonNode::type()const{
    return TypeNode::EmptyNode;
}

EventComparisonNode::EventComparisonNode(Comparison cmp, string event) : comparison(cmp), value(event){}
TypeNode EventComparisonNode::type()const{
    return TypeNode::EmptyNode;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation logOper, shared_ptr<Node> lt, shared_ptr<Node> rh): logicalOperation(logOper), left(lt), right(rh){}
TypeNode LogicalOperationNode::type()const{
    return TypeNode::EmptyNode;
}
