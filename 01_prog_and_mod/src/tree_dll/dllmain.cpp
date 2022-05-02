// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#include <iostream>  // ANCHOR - Aufgabe 1.1.3
#include <sstream>
#include <algorithm>

#include "node.h"

Node::Node(const std::string& name)
{
	static int node_id = 1;
	this->node_id = node_id++;
	if (name == "")
	{
		// ANCHOR - Aufgabe 1.2.1
		// this->name = "node_" + std::to_string(Node::node_id);  

		// NOTE - StringStream Methode
		std::stringstream str_sm;
		str_sm << "node_" << Node::node_id;
		std::string node_id_str = str_sm.str();
		this->name = node_id_str;
	}
	else {
		this->name = name;
	}

}

Node::~Node()
{
	std::cout << "enter ~Node of " << this->name << std::endl;  // ANCHOR - Aufgabe 1.1.3
	for (Node * n : children)
		delete n;
	std::cout << "leave ~Node of " << this->name << std::endl;  // ANCHOR - Aufgabe 1.1.3
}

const std::string Node::get_name() const
{
	return name;
}

void Node::set_name(const std::string& name)
{
	this->name = name;
}

int Node::get_nr_children() const
{
	return children.size();
}

Node * Node::get_child(int i) const
{
	return children[i];
}

void Node::add_child(Node* child)
{
	children.push_back(child);
}

std::ostream& Node::print(std::ostream& str, int offset)
{
	// ANCHOR - Aufgabe 1.2.3
	str << std::string(offset, ' ') << this->name << std::endl;
	for (Node * child : this->children)
	{
		str << std::string(offset + 2, ' ') << child->name << std::endl;
		if (child->children.size())
			child->print(str, offset + 2);
	}
	return str;
}

// ANCHOR - Aufgabe 1.2.2

Node * create_complete_tree(int nr_child_nodes, int tree_depth)
{
	// Gelöst von panda_no1
	Node * root = new Node();

	if (tree_depth > 1)
	{
		for (int c = 0; c < nr_child_nodes; c++)
			root->add_child(create_complete_tree(nr_child_nodes, tree_depth - 1));
	}

	return root;
}

std::ostream& operator<<(std::ostream& os, Node * n_ptr)
{
	// ANCHOR - Aufgabe 1.2.3
	return n_ptr->print(os);
}

// Zusatzaufgabe 1

std::ostream& traverse_without_cycles(std::ostream& os, Node * n_ptr, int offset)
{
	static std::vector<int> visited_nodes;
	// os << "[debug] n_ptr.name = "<< n_ptr->get_name() << "n_ptr.id=" << n_ptr->node_id << std::endl;

	if (std::find(visited_nodes.begin(), visited_nodes.end(), n_ptr->node_id) != visited_nodes.end())
	{
		os << "cycle detected" << std::endl;
	}
	else {
		visited_nodes.push_back(n_ptr->node_id);
		os << std::string(offset, ' ') << n_ptr->get_name() << std::endl;
		for (int idx = 0; idx < n_ptr->get_nr_children(); idx++) {
			Node * child = n_ptr->get_child(idx);
			traverse_without_cycles(os, child, offset + 1);
		}
	}
	return os;
}