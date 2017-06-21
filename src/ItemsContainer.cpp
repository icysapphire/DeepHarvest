#include "ItemsContainer.h"
ItemsContainer::ItemsContainer(){}
void ItemsContainer::CreateItem(const float intensity, const int type, const float reward, const position pos, int size){
	Item* item;
	
	if(size==0) size = 64;
	if (type == Item::BONUS) item = new Bonus(intensity, reward, size);
	else item = new Hole(intensity, reward);
	

	item->SetPosition(pos);
	item->setPos(pos.x*64+(32-item->boundingRect().width()/2), pos.y*64+(32-item->boundingRect().height()/2));
	objects.push_back(item);
}


 void ItemsContainer::Backup(){ 
	 start_positions.clear();
	 ItemsContainer::Iterator iter(*this);
		while (iter.HasNext()){
		Item* item = iter.GetNext();
		start_positions.push_back(item->GetPosition());
		}
	 }
 void ItemsContainer::RestoreBackup(){ 
	 ItemsContainer::Iterator iter(*this);
	 int i = 0;
	 while (iter.HasNext()){
		Item* item = iter.GetNext();
		item->SetPosition(start_positions[i]);
		i++;
		}
	}
