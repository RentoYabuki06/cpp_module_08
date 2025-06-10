/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:58:12 by yabukirento       #+#    #+#             */
/*   Updated: 2025/06/10 14:34:39 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Span.hpp"

Span::Span(unsigned int N) : _maxSize(N) {}

Span::Span(const Span &other) : _maxSize(other._maxSize), _numbers(other._numbers) {}

Span& Span::operator=(const Span &other) {
	if (this != &other) {
		this->_maxSize = other._maxSize;
		this->_numbers = other._numbers;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int number) {
	if (this->_numbers.size() >= _maxSize)
		throw FullException();
	this->_numbers.insert(number);
}

int Span::shortestSpan() {
	if (this->_numbers.size() < 2)
		throw NotFoundException();

	int minSpan = INT_MAX;

	std::multiset<int>::iterator it = _numbers.begin();
	std::multiset<int>::iterator nextIt = it;
	++nextIt;

	while (nextIt != _numbers.end()) {
		int diff = *nextIt - *it;
		if (diff < minSpan)
			minSpan = diff;
		++it;
		++nextIt;
	}

	return minSpan;
}


int Span::longestSpan() {
	if (this->_numbers.size() < 2)
		throw NotFoundException();
	return *std::prev(_numbers.end()) - *_numbers.begin();
}
