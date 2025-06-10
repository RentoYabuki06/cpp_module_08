/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:34:51 by yabukirento       #+#    #+#             */
/*   Updated: 2025/06/10 14:31:27 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <algorithm>
#include <set>
#include <exception>

class FullException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "Container already full.";
	}
};

class NotFoundException : public std::exception {
public:
	virtual const char* what() const throw() {
		return "span not found in container.";
	}
};

class Span {
private:
	unsigned int		_maxSize;
	std::multiset<int>	_numbers;
public:
	Span(unsigned int N);
	Span(const Span &other);
	Span& operator=(const Span &other);
	~Span();

	void	addNumber(int number);
	int		shortestSpan();
	int		longestSpan();
};

#endif
