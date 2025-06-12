

## Exercise 00: Easy find

**目的**: テンプレート関数を使ってSTLコンテナ内で値を検索する

### 主要な概念
この演習では以下を学びます：
- 関数テンプレートの基本的な使用法
- STLアルゴリズム `std::find` の活用
- イテレーターの概念と使用法
- 例外処理の実装

### 実装のポイント

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

#### 技術的な解説：
1. **テンプレート関数**: `template <typename T>` により、任意のコンテナ型に対応
2. **戻り値型**: `typename T::iterator` でコンテナのイテレーター型を取得
3. **std::find**: STLアルゴリズムを使って線形探索を実行
4. **例外処理**: 値が見つからない場合は独自例外をスロー

### テスト例の解説

```19:38:ex00/srcs/main.cpp
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
```

この実装では `std::vector` と `std::list` でテストしており、どのSTLコンテナでも動作することを確認しています。

---

## Exercise 01: Span

**目的**: 数値のコンテナクラスを作成し、最短・最長スパンを計算する

### 主要な概念
この演習では以下を学びます：
- `std::multiset` コンテナの活用
- 効率的なスパン計算アルゴリズム
- 例外安全性の設計
- 大量データの処理

### クラス設計

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

#### 設計の理由：
- **std::multiset**: 自動ソートと重複値の許可により、効率的なスパン計算が可能
- **容量制限**: `_maxSize` で保存可能な要素数を制限
- **例外安全**: 適切な例外をスローして異常状態を通知

### 重要な実装詳細

#### 最短スパンの計算
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

**アルゴリズムの解説**:
- ソート済みの `multiset` で隣接要素の差分を計算
- 時間計算量: O(n)
- 空間計算量: O(1)

#### 最長スパンの計算
```56:60:ex01/srcs/Span.cpp
int Span::longestSpan() {
	if (this->_numbers.size() < 2)
		throw NotFoundException();
	return *std::prev(_numbers.end()) - *_numbers.begin();
}
```

**アルゴリズムの解説**:
- ソート済みなので、最大値 - 最小値で計算
- 時間計算量: O(1)
- 空間計算量: O(1)

### テストケースの解説

#### 正常系テスト
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

#### 大容量テスト
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

このテストでは10万個の要素を処理し、実装の効率性を確認します。

#### 重複値テスト
```58:65:ex01/srcs/main.cpp
        Span sp_dup(3);
        sp_dup.addNumber(100);
        sp_dup.addNumber(100);
        sp_dup.addNumber(200);
        std::cout << "\n=== Duplicate Test ===" << std::endl;
        std::cout << "Shortest span with duplicates: " << sp_dup.shortestSpan() << std::endl;
```

重複値がある場合、最短スパンが0になることを確認します。

---

## 全体の学習効果

### STLの理解
- **コンテナ**: `vector`, `list`, `multiset`の特性と使い分け
- **イテレーター**: 異なるコンテナ間での統一的なアクセス方法
- **アルゴリズム**: `std::find`などの汎用アルゴリズムの活用

### C++の高度な機能
- **テンプレート**: 型パラメータを使った汎用プログラミング
- **例外処理**: 安全なエラーハンドリング
- **RAII**: リソースの自動管理

### パフォーマンス意識
- 適切なデータ構造の選択（multisetによる自動ソート）
- 効率的なアルゴリズム設計（O(1)とO(n)の最適化）
