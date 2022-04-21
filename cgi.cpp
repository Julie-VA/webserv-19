//Execute cgi
#include "header.hpp"
#include "request.hpp"
#include "webserv.hpp"
#include <iostream>
#include <unistd.h>
std::vector<Header>::iterator	find_header(std::vector<Header> vec, std::string key);

void		fork_exec(std::string path, int fd[2], int fd_i[2], std::string body, char **env)
{
	char	*av[3];

	av[0] = (char *)"python";
	av[1] = &path[0];
	av[2] = NULL;
	//dup2(fd_i[0], 0);
	//dup2(fd[1], 1);
	// write(1, body.c_str(), body.size() + 1);
	// close(fd_i[0]);
	// close(fd_i[1]);
	// close(fd[0]);
	// close(fd[1]);
	
	execve("/usr/bin/python", av, NULL);
}

struct timeval	zero_time()
{
	struct timeval	ret;

	ret.tv_sec = 0;
	ret.tv_usec = 0;
	return (ret);
}

std::string exec_cgi(std::string path, Request const &req) //Check if body is ready to send
{
	int			fd[2];
	int			fd_i[2];
	char		tmp[11];
	std::string	return_string = "";
	fd_set	sockets;
	struct timeval	timer = zero_time();

	FD_ZERO(&sockets);
	pipe(fd);
	pipe(fd_i);
	if (!fork())
	{
		char **env = vec_to_tab(create_env(req));
		fork_exec(path, fd, fd_i, req.get_body(), env);		
	}
	close(fd[1]);
	close(fd_i[0]);
	FD_SET(fd[0], &sockets);
	sleep(1);
	int r = read(fd[0], tmp, 10);
	while (r == 10)
	{
		return_string += std::string(tmp);
		int se = select(fd[0] + 1, &sockets, NULL, NULL, &timer);
		timer = zero_time();
		if (se > 0)
			r = read(fd[0], tmp, 10);
		else
			r = -1;
		tmp[r] = 0;
	}
	if (r != -1)
		return_string += std::string(tmp);
	std::cout << "Return of the script " << return_string << std::endl;
	return (return_string);
}
