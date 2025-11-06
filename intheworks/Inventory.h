#pragma once
#include <unordered_map>
#include <string>
#include <iostream>

class Item {
	public:
	Item(const std::string& name, int quantity)
		: itemName(name), itemQuantity(quantity) {}
	std::string itemName;
	int itemQuantity;
};

class Inventory {
public:
	Inventory() = default;
	void addItem(const std::string& itemName, int quantity) {
		std::cout << "Adding " << quantity << " of " << itemName << " to inventory." << std::endl;

		auto it = items.find(itemName);
		if (it != items.end()) {
			it->second.itemQuantity += quantity;
		}
		else {
			items.emplace(itemName, Item(itemName, quantity));
		}
	}
	bool removeItem(const std::string& itemName, int quantity) {
		auto it = items.find(itemName);
		if (it != items.end() && it->second.itemQuantity >= quantity) {
			it->second.itemQuantity -= quantity;
			if (it->second.itemQuantity == 0) {
				items.erase(it);
			}
			return true;
		}
		return false;
	}
protected:
	std::unordered_map<std::string, Item> items;
};