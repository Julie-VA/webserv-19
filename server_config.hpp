#ifndef SERVER_CONFIG_HPP
#define SERVER_CONFIG_HPP

#include <map>
#include <set>
#include <arpa/inet.h>
#include "location_config.hpp"
#include "utils.hpp"

class ServerConfig
{
public:
	ServerConfig(const std::string& content);

	const std::string& 								getRoot() const;
	const std::string& 								getIndex() const;
	const std::string& 								getServerName() const;
	struct in_addr									getHost() const;
	unsigned short									getPort() const;
	const std::map<std::string, LocationConfig>&	getLocations() const;
private:
	std::string 							_root;
	std::string								_index;
	std::string 							_server_name;
	struct in_addr							_host;
	unsigned short							_port;
	std::set<Method>						_allowed_methods;
	std::map<std::string, LocationConfig>	_locations;
};

#endif /* SERVER_CONFIG_HPP */
