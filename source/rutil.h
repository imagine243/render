//
//  rutil.h
//  render
//
//  Created by chao on 2017/8/7.
//  Copyright © 2017年 chao. All rights reserved.
//

#ifndef rutil_h
#define rutil_h

#include <cstdio>            // fprint function, stderr
#include <vector>
#include <string>

static std::vector<std::string> split(const std::string &str, char delimiter)
{
	std::vector<std::string> l;
	std::size_t start = 0;
	std::size_t end = 0;

	while ((end = str.find(delimiter, start)) != std::string::npos)
	{
		l.push_back(str.substr(start, end - start));
		start = end + 1;
	}

	l.push_back(str.substr(start));
	return l;
}

#endif /* rutil_h */
