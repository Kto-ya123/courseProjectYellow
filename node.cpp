#include"node.h"


TypeNode EmptyNode::type()const{
    return TypeNode::EmptyNode;
}

bool EmptyNode::Evaluate(Date date, string event) const{
    return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, Date date) : comparison(cmp), value(date){}
bool DateComparisonNode::Evaluate(Date date, string event) const{
    if(this->comparison == Comparison::Equal){
        return this->value == date;
    }else if(this->comparison == Comparison::NotEqual){
        return this->value != date;
    }else if(this->comparison == Comparison::Greater){
        return this->value < date;
    }else if(this->comparison == Comparison::Less){
        return date < this->value;
    }else if(this->comparison == Comparison::GreaterOrEqual){
        if(this->value != date){
            return this->value < date;
        }else{
            return true;
        }
    }else if(this->comparison == Comparison::LessOrEqual){
        if(this->value != date){
            return date < this->value;
        }else{
            return true;
        }
    }
}
TypeNode DateComparisonNode::type()const{
    return TypeNode::EmptyNode;
}


EventComparisonNode::EventComparisonNode(Comparison cmp, string event) : comparison(cmp), value(event){}
bool EventComparisonNode::Evaluate(Date date, string event) const{
    if(this->comparison == Comparison::Equal){
        return event == this->value;
    }else if(this->comparison == Comparison::NotEqual){
        return event != this->value;
    }
}
TypeNode EventComparisonNode::type()const{
    return TypeNode::EmptyNode;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation logOper, shared_ptr<Node> lt, shared_ptr<Node> rh): logicalOperation(logOper), left(lt), right(rh){}
bool LogicalOperationNode::Evaluate(Date date, string event) const{
    if(this->logicalOperation == LogicalOperation::Or){
        return (this->left->Evaluate(date, event) || this->right->Evaluate(date, event));
    }else if(this->logicalOperation == LogicalOperation::And){
        return this->left->Evaluate(date, event) || this->right->Evaluate(date, event);
    }
}
TypeNode LogicalOperationNode::type()const{
    return TypeNode::EmptyNode;
}
