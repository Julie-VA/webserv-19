#ifndef UTILS_HPP
# define UTILS_HPP
# include <string>
# include <vector>
# include <sstream>

const static std::string LINE_END = "\r\n";

std::vector<std::string> split(const std::string& str, const std::string& delim = " ")
{
	std::vector<std::string> tokens;
	std::string strCopy = str;

	size_t pos = 0;
	std::string token;

	while ((pos = strCopy.find(delim)) != std::string::npos)
	{
		token = strCopy.substr(0, pos);
		strCopy.erase(0, pos + delim.length());

		tokens.push_back(token);
	}
	if (strCopy.length() > 0)
		tokens.push_back(strCopy);
	return tokens;
}

std::string concat(const std::vector<std::string>& strings, const std::string& delim = " ")
{
	std::string res;

	for (size_t i = 0; i < strings.size(); i++)
	{
		res += strings[i];

		if ((i + 1) != strings.size())
			res += delim;
	}
	return res;
}

enum Method
{
	GET,
	HEAD,
	POST,
	PUT,
	DELETE,
	TRACE,
	OPTIONS,
	CONNECT,
	PATCH,
	INVALID_METHOD
};

std::string to_string(Method method)
{
	switch (method)
	{
	case GET:
		return "GET";
	case HEAD:
		return "HEAD";
	case POST:
		return "POST";
	case PUT:
		return "PUT";
	case DELETE:
		return "DELETE";
	case TRACE:
		return "TRACE";
	case OPTIONS:
		return "OPTIONS";
	case CONNECT:
		return "CONNECT";
	case PATCH:
		return "PATCH";
	default:
		return "INVALID";
	}
}

Method method_from_string(const std::string& method)
{
	if (method == to_string(GET))
		return GET;
	else if (method == to_string(HEAD))
		return HEAD;
	else if (method == to_string(POST))
		return POST;
	else if (method == to_string(PUT))
		return PUT;
	else if (method == to_string(DELETE))
		return DELETE;
	else if (method == to_string(TRACE))
		return TRACE;
	else if (method == to_string(OPTIONS))
		return OPTIONS;
	else if (method == to_string(CONNECT))
		return CONNECT;
	else if (method == to_string(PATCH))
		return PATCH;
	else
		return INVALID_METHOD;
}

enum Version
{
	HTTP_1_0,
	HTTP_1_1,
	HTTP_2_0
};

std::string to_string(Version version)
{
	switch (version)
	{
	case HTTP_1_0:
		return "HTTP/1.0";
	case HTTP_1_1:
		return "HTTP/1.1";
	case HTTP_2_0:
		return "HTTP/2.0";
	}
}

Version version_from_string(const std::string& version)
{
	if (version == to_string(HTTP_1_0))
		return HTTP_1_0;
	else if (version == to_string(HTTP_1_1))
		return HTTP_1_1;
	else if (version == to_string(HTTP_2_0))
		return HTTP_2_0;
	else
		return HTTP_1_1;
}

enum Directive
{
	allowed_methods,
	autoindex,
	upload,
	upload_dir,
	root,
	default_index,
	server_name,
	host,
	port,
	location,
	INVALID_DIRECTIVE
};

std::string to_string(Directive directive)
{
	switch(directive)
	{
	case allowed_methods:
		return "allowed_methods";
	case autoindex:
		return "autoindex";
	case upload:
		return "upload";
	case upload_dir:
		return "upload_dir";
	case root:
		return "root";
	case default_index:
		return "index";
	default:
		return "invalid";
	}
}

Directive directive_from_string(const std::string& directive)
{
	if (directive == to_string(allowed_methods))
		return allowed_methods;
	else if (directive == to_string(autoindex))
		return autoindex;
	else if (directive == to_string(upload))
		return upload;
	else if (directive == to_string(upload_dir))
		return upload_dir;
	else if (directive == to_string(root))
		return root;
	else if (directive == to_string(default_index))
		return default_index;
	else
		return INVALID_DIRECTIVE;
}

bool is_not_space(char c) { return !std::isspace(c); }
void ltrim(std::string& str) { str.erase(str.begin(), std::find_if(str.begin(), str.end(), is_not_space)); }
void rtrim(std::string& str) { str.erase(std::find_if(str.rbegin(), str.rend(), is_not_space).base(), str.end()); }
void trim(std::string& str) { ltrim(str); rtrim(str); }

#endif /* UTILS_HPP */
