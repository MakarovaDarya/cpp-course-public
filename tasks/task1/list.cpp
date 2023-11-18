#include "list.h"


List::List()
{
	first = nullptr;
	last = nullptr;
}


bool
List::is_empty()
{
	if (first == nullptr) {
		return true;
	} else {
		return false;
	}
}


void
List::clear()
{
	Node* current = first;
	while (current != nullptr) {
		Node* temp = current;
		current = current->next;
		delete temp;
	}
	first = nullptr;
}



void
List::push_front(int _val)
{
	Node* new_node = new Node(_val);
	new_node->next = first;
	first = new_node;
}


void
List::push_back(int _val)
{
	Node* new_node = new Node(_val);
	if (is_empty()) {
		first = new_node;

	}
	else {
		Node* current = first;
		while (current->next != nullptr) {
			current->next = new_node;
		}
	}

}


Node*
List::find(int _val)
{
	Node* current = first;
	while (current != nullptr) {
		if (current->val == _val) {
			return current;
		}
		current = current->next;
	}
	return nullptr;


}


void
List::remove_front()
{
	if (is_empty()) {
		return;
	}
	Node* temp = first;
	first = first->next;
	delete temp;
}


void
List::remove_back()
{
	if (!is_empty()) {
		if (first->next == nullptr) {
			delete first;
			first = nullptr;
		}
		else {
			Node* current = first;
			while (current->next->next != nullptr) {
				current = current->next;
			}
			delete current->next;
			current->next = nullptr;
		}
	}
}


bool
List::remove(const Node* _node)
{
	if (_node == nullptr) {
		return false;
	}
	if (first == _node) {
		remove_front();
		return true;
	}
	Node* current = first;
	while (current->next != nullptr) {
		if (current->next == _node) {
			Node* temp = current->next;
			current->next = temp->next;
			delete temp;
			return true;
		}
		current = current->next;
	}
	return false;
}
