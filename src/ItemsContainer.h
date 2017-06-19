#ifndef ITEMSCONTAINER_H
#define ITEMSCONTAINER_H
#include "Item.h"
#include "Bonus.h"
#include "Hole.h"
#include <iostream>

class ItemsContainer {
	public:
	ItemsContainer();
	
	void CreateItem(const float intensity, const int type, const float reward, const position pos, int size=0);
	void Backup();
	void RestoreBackup();
	inline void Clear() {objects.clear();}
	class Iterator {
		private:
		std::vector<Item*>::iterator it;
		ItemsContainer* container;
		
		public:
		Iterator(ItemsContainer& container_) {
			container = &container_;
			it = container->objects.begin();
		}
		void Reset(){ it = container->objects.begin(); }
		inline Item* GetNext() {
			Item* e = *it; ++it;  return e;}
		inline bool HasNext() const { return (it != container->objects.end()); }
	};
	friend class Iterator;
	
	protected:
	std::vector<Item*> objects;
	std::vector<position> start_positions;
};

#endif
