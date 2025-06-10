/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:54:13 by yabukirento       #+#    #+#             */
/*   Updated: 2025/06/10 14:28:21 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Span.hpp"
#include <vector>
#include <cstdlib> // rand
#include <ctime>   // time

int main() {
    try {
        // 正常系テスト
        Span sp(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "=== Small Span Test ===" << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span : " << sp.longestSpan() << std::endl;
        std::cout << std::endl;

        // 容量超過テスト
        try {
            sp.addNumber(42);
        } catch (const std::exception &e) {
            std::cout << "[Expected] Error: " << e.what() << std::endl;
        }

        // 要素数不足による例外テスト
        Span sp_empty(2);
        sp_empty.addNumber(1);
        try {
            sp_empty.shortestSpan();
        } catch (const std::exception &e) {
            std::cout << "[Expected] Error: " << e.what() << std::endl;
        }

        // ==== 10000個以上の数値テスト ====
        std::cout << "\n=== Large Span Test (100000 elements) ===" << std::endl;

        const int largeSize = 100000;
        Span sp_large(largeSize);
        std::srand(std::time(NULL));

        for (int i = 0; i < largeSize; ++i) {
            sp_large.addNumber(std::rand());
        }

        std::cout << "Shortest span: " << sp_large.shortestSpan() << std::endl;
        std::cout << "Longest span : " << sp_large.longestSpan() << std::endl;

        // 重複テスト（shortestSpanが0になる）
        Span sp_dup(3);
        sp_dup.addNumber(100);
        sp_dup.addNumber(100);
        sp_dup.addNumber(200);
        std::cout << "\n=== Duplicate Test ===" << std::endl;
        std::cout << "Shortest span with duplicates: " << sp_dup.shortestSpan() << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return 0;
}
