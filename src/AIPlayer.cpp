#include "AIPlayer.h"
AIPlayer::AIPlayer(GameEngine* game_eng_, const std::string& path): Player(game_eng_),s_tensor(DT_FLOAT, TensorShape({21168})), rnnState(DT_FLOAT, TensorShape({2, 1, 512})) {
	Scope root = Scope::NewRootScope();
	Status load_graph_status = LoadGraph(path, &session);
	if (!load_graph_status.ok()) {
		LOG(ERROR) << load_graph_status;
	}
}

void AIPlayer::Play() {
	while(CanMove()) {
		Tensor prediction = PredictMove();
		
		int m;
		if(game_eng->GetMode()==2) m = prediction.flat<tensorflow::int32>()(0);
		else m = prediction.flat<tensorflow::int64>()(0);
		
		auto recents_rev=recents.rbegin();
		
		// Rarely the AI agent gets stuck in a loop: 
		// here we have a simple heuristic to determine if it's going to loop and avoid it choosing suboptimal move
		if (game_eng->GetMode()==2 && ((recents.size()>5 && (m==recents_rev[1] && m==recents_rev[3]) && (recents_rev[0]==recents_rev[2] && recents_rev[2]==recents_rev[4]) && (recents_rev[0] != recents_rev[1])
			&&  ((recents_rev[0]<=1 && recents_rev[1]<=1) || (recents_rev[0]>=2 && recents_rev[1]>=2) )
			)
		|| (moved.size()>5 && moved.rbegin()[0]==moved.rbegin()[1] && moved.rbegin()[1]==false))) {
			m=prediction.flat<tensorflow::int32>()(1);
		}
		recents.push_back(m);
		moved.push_back(MoveInDirection(m));
		qApp->processEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(60));
	}
	
}
Status AIPlayer::LoadGraph(const string& graph_file_name, unique_ptr<tensorflow::Session>* session) {
	tensorflow::GraphDef graph_def;
	Status load_graph_status = ReadBinaryProto(tensorflow::Env::Default(), graph_file_name, &graph_def);
	if (!load_graph_status.ok()) {
		return tensorflow::errors::NotFound("Failed to load graph at '", graph_file_name, "'");
	}
	session->reset(tensorflow::NewSession(tensorflow::SessionOptions()));
	Status session_create_status = (*session)->Create(graph_def);
	if (!session_create_status.ok()) {
		return session_create_status;
	}
	return Status::OK();
}

Tensor AIPlayer::PredictMove() {
	using namespace cv;
	vector<Mat> res_data(3);
	game_eng->ToMatrix(res_data);


	// Moving matrix from opencv to tensorflow
	for (int z=0; z<3; z++)
		for(int i=0; i<84; i++) {
			for(int j=0; j<84; j++) {
				auto idx=i*84*3+j*3+z;
				s_tensor.vec<float>()(idx)=res_data[z].at<float>(i,j);

			}
		}

	std::vector<std::pair<string,Tensor> > inputs;
	std::vector<Tensor> outputs;

	Input::Initializer uno(1);
	inputs.push_back(std::make_pair ("main_scalarinput", s_tensor));
	inputs.push_back(std::make_pair ("main_train_length",uno.tensor));
	inputs.push_back(std::make_pair ("main_state_in",rnnState));
	inputs.push_back(std::make_pair ("main_batch_size",uno.tensor));

	Status run_status;
	if(game_eng->GetMode()==2)
	run_status = session->Run(inputs, {"main_qout","main_state_out","main_predict"}, {}, &outputs);
	else run_status = session->Run(inputs, {"main_predict","main_state_out"}, {}, &outputs);
	if (!run_status.ok()) {
		LOG(ERROR) << "Running model failed: " << run_status;
	}

	// Feeding RNN with new state
	rnnState = outputs[1];
	return outputs[0];
}
