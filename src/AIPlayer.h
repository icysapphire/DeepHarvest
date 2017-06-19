#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include "GameEngine.h"

#include <chrono>
#include <thread>
#include <qt/QtWidgets/QApplication>
#include "tensorflow/cc/framework/ops.h"

#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/image_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/framework/tensor_util.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

using tensorflow::Flag;
using tensorflow::Tensor;
using tensorflow::Status;

using tensorflow::int32;
using namespace tensorflow;
using namespace tensorflow::tensor;
using namespace tensorflow::ops;


class AIPlayer: public Player {
public:
	AIPlayer(GameEngine* game_eng_, const std::string& path);
	
	/**
	* @brief gets the two most optimal game moves from Q-network
	* @return tensorflow::Tensor of size 2x1
	*/
	Tensor PredictMove();
	
	/**
	* @brief actually plays the game according to Q-network predictions
	*/
	virtual void Play();

protected:
	Mat state;
	Tensor s_tensor;
	std::unique_ptr<tensorflow::Session> session;
	Tensor rnnState;
	Status LoadGraph(const string& graph_file_name, std::unique_ptr<tensorflow::Session>* session);
	vector<int> recents;
	vector<bool> moved;
};


#endif
