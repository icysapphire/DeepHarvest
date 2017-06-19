#include "utility.h"
std::string utility::get_working_directory(){
	boost::filesystem::path p ("main");
	return boost::filesystem::system_complete(p).remove_filename().string();
}
