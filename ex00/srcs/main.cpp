/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabukirento <yabukirento@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 22:54:13 by yabukirento       #+#    #+#             */
/*   Updated: 2025/06/09 17:35:18 by yabukirento      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/easyfind.hpp"
#include <vector>
#include <list>

int main() {
    // --- std::vector でのテスト ---
    std::cout << "--- Testing with std::vector ---" << std::endl;
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);

    // ケース1: 値が見つかる場合
    try {
        std::vector<int>::iterator it = easyfind(vec, 30);
        std::cout << "Found value: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // ケース2: 値が見つからない場合
    try {
        easyfind(vec, 99);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << std::endl;

    // --- std::list でのテスト ---
    std::cout << "--- Testing with std::list ---" << std::endl;
    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    // ケース3: 値が見つかる場合
    try {
        std::list<int>::iterator it = easyfind(lst, 1);
        std::cout << "Found value: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
