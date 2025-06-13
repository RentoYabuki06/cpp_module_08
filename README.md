## Exercise 00: Easy find

**Objective**: Implement a template function to search for values in STL containers

### Key Concepts
This exercise covers:
- Basic usage of function templates
- Utilizing STL algorithm `std::find`
- Iterator concepts and usage
- Exception handling implementation

### Implementation Highlights

```12:34:ex00/includes/easyfind.hpp
template <typename T>
typename T::iterator easyfind(T& container, int value) {
	typename T::iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end()) {
		throw NotFoundException();
	}
	return it;
}
```

#### Technical Explanation:
1. **Template Function**: `template <typename T>` allows compatibility with any container type
2. **Return Type**: `typename T::iterator` retrieves the container's iterator type
3. **std::find**: Uses STL algorithm for linear search
4. **Exception Handling**: Throws custom exception when value is not found

### Test Case Explanation

```19:38:ex00/srcs/main.cpp
    // Case 1: When value is found
    try {
        std::vector<int>::iterator it = easyfind(vec, 30);
        std::cout << "Found value: " << *it << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Case 2: When value is not found
    try {
        easyfind(vec, 99);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
```

This implementation tests with both `std::vector` and `std::list`, confirming functionality with any STL container.

---

## Exercise 01: Span

**Objective**: Create a numeric container class that calculates shortest and longest spans

### Key Concepts
This exercise covers:
- Utilizing `std::multiset` container
- Efficient span calculation algorithms
- Exception-safe design
- Large data processing

### Class Design

```33:49:ex01/includes/Span.hpp
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
```

#### Design Rationale:
- **std::multiset**: Enables efficient span calculation through automatic sorting and duplicate value support
- **Capacity Limit**: `_maxSize` restricts the number of storable elements
- **Exception Safety**: Throws appropriate exceptions to notify abnormal states

### Important Implementation Details

#### Shortest Span Calculation
```32:46:ex01/srcs/Span.cpp
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
```

**Algorithm Explanation**:
- Calculates differences between adjacent elements in sorted `multiset`
- Time Complexity: O(n)
- Space Complexity: O(1)

#### Longest Span Calculation
```56:60:ex01/srcs/Span.cpp
int Span::longestSpan() {
	if (this->_numbers.size() < 2)
		throw NotFoundException();
	return *std::prev(_numbers.end()) - *_numbers.begin();
}
```

**Algorithm Explanation**:
- Calculated as maximum value - minimum value due to sorting
- Time Complexity: O(1)
- Space Complexity: O(1)

### Test Case Explanation

#### Normal Case Test
```18:29:ex01/srcs/main.cpp
        Span sp(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "=== Small Span Test ===" << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span : " << sp.longestSpan() << std::endl;
```

#### Large Capacity Test
```47:56:ex01/srcs/main.cpp
        const int largeSize = 100000;
        Span sp_large(largeSize);
        std::srand(std::time(NULL));

        for (int i = 0; i < largeSize; ++i) {
            sp_large.addNumber(std::rand());
        }

        std::cout << "Shortest span: " << sp_large.shortestSpan() << std::endl;
        std::cout << "Longest span : " << sp_large.longestSpan() << std::endl;
```

This test processes 100,000 elements to verify implementation efficiency.

#### Duplicate Value Test
```58:65:ex01/srcs/main.cpp
        Span sp_dup(3);
        sp_dup.addNumber(100);
        sp_dup.addNumber(100);
        sp_dup.addNumber(200);
        std::cout << "\n=== Duplicate Test ===" << std::endl;
        std::cout << "Shortest span with duplicates: " << sp_dup.shortestSpan() << std::endl;
```

Verifies that shortest span becomes 0 when duplicate values exist.

---

## Overall Learning Outcomes

### STL Understanding
- **Containers**: Characteristics and usage of `vector`, `list`, and `multiset`
- **Iterators**: Unified access method across different containers
- **Algorithms**: Utilization of generic algorithms like `std::find`

### Advanced C++ Features
- **Templates**: Generic programming using type parameters
- **Exception Handling**: Safe error handling
- **RAII**: Automatic resource management

### Performance Awareness
- Appropriate data structure selection (automatic sorting with multiset)
- Efficient algorithm design (O(1) and O(n) optimization)
