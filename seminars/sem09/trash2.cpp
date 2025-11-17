#include <iostream>
#include <stack>
#include <memory>

// Узел бинарного дерева
template <typename T>
struct Node {
    T key;
    Node* left;
    Node* right;
    Node* parent;

    Node(const T& k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Бинарное дерево поиска
template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(root); }

    // Вставка ключа в дерево
    void insert(const T& key) {
        Node<T>** current = &root;
        Node<T>* prev = nullptr;
        while (*current) {
            prev = *current;
            if (key < (*current)->key) {
                current = &(*current)->left;
            } else if (key > (*current)->key) {
                current = &(*current)->right;
            } else {
                return; // Дубликаты игнорируем
            }
        }
        *current = new Node<T>(key);
        (*current)->parent = prev;
    }

    // Класс итератора
    class Iterator {
    public:
        Iterator(Node<T>* node, Node<T>* root = nullptr) : current(node), root(root) {}

        // Префиксный инкремент (переход к следующему узлу)
        Iterator& operator++() {
            if (current) {
                if (current->right) {
                    current = current->right;
                    while (current->left) {
                        current = current->left;
                    }
                } else {
                    Node<T>* prev;
                    do {
                        prev = current;
                        current = current->parent;
                    } while (current && current->right == prev);
                }
            }
            return *this;
        }

        // Постфиксный инкремент
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Префиксный декремент (переход к предыдущему узлу)
        Iterator& operator--() {
            if (current) {
                if (current->left) {
                    current = current->left;
                    while (current->right) {
                        current = current->right;
                    }
                } else {
                    Node<T>* prev;
                    do {
                        prev = current;
                        current = current->parent;
                    } while (current && current->left == prev);
                }
            } else {
                // Если current == nullptr, устанавливаем на последний узел
                current = root;
                if (current) {
                    while (current->right) {
                        current = current->right;
                    }
                }
            }
            return *this;
        }

        // Постфиксный декремент
        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        // Разыменование
        T& operator*() const { 
            if (!current) {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return current->key; 
        }

        T* operator->() const { 
            if (!current) {
                throw std::runtime_error("Dereferencing end iterator");
            }
            return &current->key; 
        }

        // Сравнение итераторов
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }

    private:
        Node<T>* current;
        Node<T>* root; // Для корректной работы operator-- с end()
    };

    // Итератор на начало (наименьший элемент)
    Iterator begin() const {
        Node<T>* node = root;
        while (node && node->left) {
            node = node->left;
        }
        return Iterator(node, root);
    }

    // Итератор на конец (за последним элементом)
    Iterator end() const { return Iterator(nullptr, root); }

    // Поиск узла
    Iterator find(const T& key) const {
        Node<T>* current = root;
        while (current) {
            if (key == current->key) {
                return Iterator(current, root);
            } else if (key < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return end();
    }

private:
    Node<T>* root;

    // Рекурсивное удаление узлов
    void clear(Node<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

// Тестирование
int main() {
    BinarySearchTree<int> tree;
    
    // Вставляем элементы
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::cout << "Прямой обход (for): ";
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Прямой обход (range-based for): ";
    for (int value : tree) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Обратный обход: ";
    auto it = tree.end();
    --it;
    while (it != tree.begin()) {
        std::cout << *it << " ";
        --it;
    }
    std::cout << *it << " "; // Печатаем первый элемент
    std::cout << std::endl;

    // Тестирование поиска
    std::cout << "Поиск элементов: ";
    auto found = tree.find(4);
    if (found != tree.end()) {
        std::cout << "Найден: " << *found << std::endl;
    } else {
        std::cout << "Не найден" << std::endl;
    }

    found = tree.find(10);
    if (found != tree.end()) {
        std::cout << "Найден: " << *found << std::endl;
    } else {
        std::cout << "Не найден: " << 10  << std::endl;
    }

    return 0;
}