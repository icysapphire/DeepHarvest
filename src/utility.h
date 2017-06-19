#ifndef UTILITY_H
#define UTILITY_H
#include <qt/QtCore/QString>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

namespace utility{
	
	template<typename T>
	QString qstring_placeholder(const std::string& fmt, const T& arg){
	return (QString::fromStdString((boost::format(fmt) % arg).str()));
	}
	
	std::string get_working_directory();	
}
#endif
