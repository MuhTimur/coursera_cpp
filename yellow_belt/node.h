#pragma once
#include "date.h"
#include "comparison.h"
#include "logical_operation.h"
#include <string>
#include <memory>

using namespace std;

class Node {
public:
	Node() {};
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison& comp_to, const Date& date_to);
	bool Evaluate(const Date& date_to, const string& event) const override;

private:
	const Comparison comparison;
	const Date date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison& comp_to, const string& event_to);
	bool Evaluate(const Date& date_to, const string& event_to) const override;

private:
	const Comparison comparison;
	const string event;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(LogicalOperation operation_to, const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs);
	bool Evaluate(const Date& date, const string& event) const override;

private:
	const LogicalOperation operation;
	shared_ptr<Node> lhs_node, rhs_node;
};