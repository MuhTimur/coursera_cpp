#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

DateComparisonNode::DateComparisonNode(const Comparison& comp_to, const Date& date_to)
    : comparison(comp_to), date(date_to) { }

bool DateComparisonNode::Evaluate(const Date& date_to, const string& event) const {
    switch (comparison) {
    case Comparison::Less:
        return date_to < date;
    case Comparison::LessOrEqual:
        return  date_to <= date;
    case Comparison::Greater:
        return date_to > date;
    case Comparison::GreaterOrEqual:
        return date_to >= date;
    case Comparison::Equal:
        return date_to == date;
    case Comparison::NotEqual:
        return date_to != date;
    }
    return true;
}

EventComparisonNode::EventComparisonNode(const Comparison& comp_to, const string& event_to)
    : comparison(comp_to), event(event_to) { }

bool EventComparisonNode::Evaluate(const Date& date_to, const string& event_to) const {
    switch (comparison) {
    case Comparison::Less:
        return event_to < event;
    case Comparison::LessOrEqual:
        return event_to <= event;
    case Comparison::Greater:
        return event_to > event;
    case Comparison::GreaterOrEqual:
        return event_to >= event;
    case Comparison::Equal:
        return event_to == event;
    case Comparison::NotEqual:
        return event_to != event;
    }
    return true;
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation operation_to, const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) 
    : operation(operation_to), lhs_node(lhs), rhs_node(rhs) { }

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
    switch (operation) {
    case LogicalOperation::And:
        return lhs_node->Evaluate(date, event) && rhs_node->Evaluate(date, event);
    case LogicalOperation::Or:
        return lhs_node->Evaluate(date, event) || rhs_node->Evaluate(date, event);
    }
    return true;
}