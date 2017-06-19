#include "GameEngine.h"
#include <stdlib.h>  /* srand, rand */
#include <math.h>
#include <time.h>
#include "GameView.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Item.h"
#include "Bonus.h"
#include "Hole.h"


bool operator==(const position& lhs, const position& rhs) {
	return (lhs.x==rhs.x) && (lhs.y==rhs.y);
}

GameEngine::GameEngine(const int mode_, const int sizex, const int sizey): mode(mode_), sizeX(sizex), sizeY(sizey) {
	srand (time(NULL));
	bonus_sound.setSource(QUrl::fromLocalFile(":/sounds/bonus.wav"));
	bonus_sound.setVolume(0.95f);
	
	hole_sound.setSource(QUrl::fromLocalFile(":/sounds/hole.wav"));
	hole_sound.setVolume(0.95f);

}

void GameEngine::Init() {
	items_container.Clear();
	round=0;

	if(mode==1) {
		for(int i=0; i<2; i++) {
			items_container.CreateItem(1,Item::HOLE,-1, PickNewPosition());
		}

		for(int i=0; i<4; i++) {
			items_container.CreateItem(1,Item::BONUS,1, PickNewPosition());
		}
	}

	else {
		for(int i=0; i<7; i++) {
			items_container.CreateItem(1,Item::HOLE,-1, PickNewPosition());
		}
		int randnum[4];
		int max=64;
		int min=16;
		float sum_rand =0;
		for(int i=0; i<4; i++) {
			randnum[i] = rand()%(max-min + 1) + min;
			sum_rand += randnum[i];
		}
		for(int i=0; i<4; i++) {
			float reward = 100*randnum[i]/sum_rand;
			items_container.CreateItem(reward/52,Item::BONUS,reward, PickNewPosition(), reward/52*64);
		}
	}

	items_container.Backup();

}


position GameEngine::PickNewPosition() {
	position pos;
	pos.x=rand() % 9 + 0;
	pos.y=rand() % 9 + 0;
	ItemsContainer::Iterator iter(items_container);
	bool good=true;
	if (player!=NULL && player->pos == pos) good = false;
	while (iter.HasNext()){
		Item* item = iter.GetNext();
		if(item->pos == pos) good = false;
	}

	if(good) return pos;
	else return PickNewPosition(); // recursively
}

void GameEngine::Update() {
	float delta;
	// Fix collisions
	ItemsContainer::Iterator iter(items_container);
	while (iter.HasNext()){

		Item& current = *(iter.GetNext());
		if(current.type!=Item::BOY && current.pos.x == player->pos.x && current.pos.y == player->pos.y) {
			if(current.type==Item::HOLE) {
				hole_sound.play();
				
				// A bit of animation
				player->hide();
				qApp->processEvents();
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
				player->show();player->setFocus();
				qApp->processEvents();
				
				if(mode==1) delta = -1;
				else delta = -0.3*player->GetScore();
			} else {delta=current.reward; bonus_sound.play();}
			player->AddScore(delta);
			
			position newpos = PickNewPosition();
			current.pos=newpos;
			current.setPosIndex(newpos.x, newpos.y);
			
			game_v->FlashScoreChange(delta);
		}
	}
	
	game_v->SetPlayerTooltipText(QString::fromStdString("Score: <b style='color:#06C; font-size:20px;'>"+std::to_string((int) player->GetScore())+"</b>, Moves:<b>"+std::to_string(player->GetMoves())+"/50"));
	
	if (round == 0 && !player->CanMove())
		{game_v->PassToAI();}

}

void GameEngine::PopulateGrid(QGraphicsScene* scene, const bool restore) {
	ItemsContainer::Iterator iter(items_container);
	
	if(!restore) {
		
		// Reclaim ownership & destroy all items
		
		if(player!=NULL) {
			scene->removeItem(player);
			delete player;
			player = NULL;
		}
		
		iter.Reset();
		while (iter.HasNext()){
			Item* item = iter.GetNext();
			if(item!=NULL){
				scene->removeItem(item);
				delete item;
				item = NULL;
			}
		}
		
		Init();

		player = new HumanPlayer(this);
		player->RefreshPosition();
	} else {
		round = 1;
		position start_pos = player->GetStartPos();
		
		// Reclaim ownership & destroy player
		scene->removeItem(player);
		delete player;
		player = NULL;
		
		iter.Reset();
		while (iter.HasNext()){
			Item* item = iter.GetNext();
			scene->removeItem(item);
			// not deleting because will be re-added to scene
		}
				
		player = new AIPlayer(this, game_v->GetPath()+"/networks/output_graph"+std::to_string(GetMode()) +".pb");
		player->SetPosition(start_pos);
		player->RefreshPosition();

		items_container.RestoreBackup();
	}

	// Move ownership and put them on the grid
	scene->addItem(player);
	Item* item;
	iter.Reset();
	while (iter.HasNext()){
		item = iter.GetNext();		
		item->RefreshPosition();
		scene->addItem(item);
	}

} 


void GameEngine::ToMatrix(vector<cv::Mat>& res_data){
	int sizes[] = {GetWidth()+2, GetHeight()+2, 3};
	vector<Mat> data(3);
	using namespace cv;
	// Init 3D matrix
	for (int z = 0; z < sizes[2]; ++z) {
		data[z] = Mat(sizes[0], sizes[1], CV_32F);
		// Creating outer frame
		data[z] = 1;
		auto roi = Rect(1, 1, GetWidth(),GetHeight());
		data[z](roi) = 0;
	}
	
	// Populating 3D matrix with game items

	// Filling player [type = 2]
		Mat roi=data[2](Rect(player->pos.x+1, player->pos.y+1, 1, 1));
		roi = Scalar(1);
		
	ItemsContainer::Iterator iter(items_container);
	while (iter.HasNext()){
		Item* item = iter.GetNext();
		auto p = item->pos;

		Mat roi=data[item->type](Rect(p.x+1, p.y+1, 1, 1));
		roi = Scalar(item->intensity);
	}

	// Resizing to 84x84 matrices
	for (int z = 0; z < sizes[2]; ++z) {
		res_data[z] = Mat(84, 84, CV_32F);
		resize(data[z], res_data[z], cv::Size(84,84), 0, 0, INTER_NEAREST);
	}
}
