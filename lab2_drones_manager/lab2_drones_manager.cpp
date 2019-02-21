#include "lab2_drones_manager.hpp"
#include <iostream>

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
	size = 0;
	first = NULL;
	last = NULL;

}

DronesManager::~DronesManager() {
	DroneRecord* currentNode = first;
	while (currentNode) {
		DroneRecord* previousNode = currentNode;
		currentNode = currentNode->next;
		delete previousNode;
	}
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	bool isSame = true;
	isSame = isSame && lhs.droneID == rhs.droneID;
	isSame = isSame && lhs.range == rhs.range;
	isSame = isSame && lhs.yearBought == rhs.yearBought;
	isSame = isSame && lhs.droneType == rhs.droneType;
	isSame = isSame && lhs.manufacturer == rhs.manufacturer;
	isSame = isSame && lhs.description == rhs.description;
	isSame = isSame && lhs.batteryType == rhs.batteryType;

	return isSame;
}

unsigned int DronesManager::get_size() const {
	DroneRecord* currentNode = first;
	int numNodes = 0;
	while (currentNode) {
		numNodes++;
		currentNode->next;
	}
	return numNodes;
}

bool DronesManager::empty() const {
	if (size == 0) {
		return true;
	}

	return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	DroneRecord* current = first;
	if (size <= index) {
		return *last;
	}

	for (int i = 0; i < index; i++) {
		current = current->next;
	}

	return *current;
}

unsigned int DronesManager::search(DroneRecord value) const {
	DroneRecord* current = first;

	for (int i = 0; i < size; i++) {
		if (*current == value) {
			return i;
		}
		current = current->next;
	}

	return size;

}

void DronesManager::print() const {
	DroneRecord* current = first;
//	<< range << yearBought << droneType << manufacturer << description << batteryType;
	for (int i = 0; i < size; i++) {
		DroneRecord toPrint = *current;
		toPrint.printRecord();
		*current = *current->next;
	}

}
bool DronesManager::insert(DroneRecord value, unsigned int index) {
	DroneRecord* curr = first;
	DroneRecord* previous = curr;
	DroneRecord* val_pointer = &value;

	if (size < index)
		return false;

	for (int counter = 0; counter < index; counter++) {
		previous = curr;
		curr = curr->next;
	}
	if (index != 0) {
		previous->next = val_pointer;
		val_pointer->prev = previous;
		val_pointer->next = curr;
		curr->prev = val_pointer;
	}
	
	else {
		insert_front(value);

	}
	return true;

}

bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord* oldFirst = first;
	if (size == 0) {
		first = &value;
		last = first;
		size++;
		return true;
	}
	oldFirst->next = first->next;
	first = &value;
	first->next = oldFirst;
	oldFirst->prev = first;
	first->prev = NULL;
	size++;
	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord* newLast = &value;

	if (size == 0) {
		last = &value;
		first = last;
		return true;
	}

	last->next = newLast;
	newLast ->prev = last;
	size++;
	return true;
}

bool DronesManager::remove(unsigned int index) {
	DroneRecord* curr = first;
	DroneRecord* previous;

	for (int i = 0;i < index; i++) {
		previous = curr;
		curr = curr->next;
	}

	DroneRecord* curr_next = curr->next;
	previous = curr_next;
	curr_next->prev = previous;
	delete curr;
	size--;
	return true;
}

bool DronesManager::remove_front() {
	DroneRecord* old_first = first;
	first = first->next;
	first->prev = NULL;
	old_first->next = NULL;
	delete old_first;
	size--;
	return true;
}

bool DronesManager::remove_back() {
	DroneRecord *old_last = last;
	last = last->prev;
	last->next = NULL;
	delete old_last;
	size--;
	return false;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	if (index < size) return false;
	DroneRecord* curr = first;
	DroneRecord* previous = curr;
	DroneRecord* replacement = &value;

	for (int i = 0; i < index; i++) {
		previous = curr;
		curr = curr->next;
	}

	previous->next = replacement;
	replacement->next = curr->next;
	curr->next->prev = replacement;
	replacement->prev = previous;
	delete curr;

	return true;

}

bool DronesManager::reverse_list() {
	if (first == NULL) return false;

	DroneRecord* previous = NULL;
	DroneRecord* current = first; 
	DroneRecord* next = NULL;

	while (current != NULL) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}

	first = previous;
	return true;
}
