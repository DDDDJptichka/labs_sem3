#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <windows.h>
#include <chrono>

#include "Includes/Tree.hpp"
#include "Includes/Exception.hpp"

int read_int(const std::string& message){

    while (true){

        std::cout << message;
        std::string line;
        
        if (!std::getline(std::cin, line)){
            
            throw input_error("Ввод завершён");
        
        }

        std::istringstream input(line);
        int value;
        char extra;

        if ((input >> value) && !(input >> extra)){

            return value;
        
        }

        std::cout << "Введите целое число.\n";

    }

}

std::string read_line(const std::string& message){

    std::cout << message;
    std::string line;

    if (!std::getline(std::cin, line)){

        throw input_error("Ввод завершён");
    
    }

    return line;

}

void show_menu(){

    std::cout << "\n========== AVL TREE ==========\n"
              << " 1. Добавить элемент\n"
              << " 2. Удалить элемент\n"
              << " 3. Найти элемент\n"
              << " 4. Вывести дерево (КЛП)\n"
              << " 5. Показать корень\n"
              << " 6. Количество элементов\n"
              << " 7. Очистить дерево\n"
              << " 8. Извлечь поддерево\n"
              << " 9. Проверить вхождение поддерева\n"
              << "10. Map: прибавить число\n"
              << "11. Where: оставить числа >= порога\n"
              << "12. Reduce: сумма элементов\n"
              << "13. Автоматически добавить случайные числа\n"
              << "14. Создать дерево из строки\n"
              << " 0. Выход\n";

}

int main(){

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Tree<int> tree;
    std::mt19937 generator(std::random_device{}());

    while (true){

        try{

            show_menu();
            int choice = read_int("Выберите действие: ");

            switch (choice){

                case 0:
                    return 0;

                case 1:{
                    
                    int value = read_int("Число: ");
                    tree.add(value);
                    std::cout << "Элемент добавлен.\n";
                    
                    break;
                }
                case 2:{

                    int value = read_int("Число: ");
                    std::cout << (tree.remove(value) ? "Элемент удалён.\n" : "Элемент не найден.\n");
                    
                    break;
                }
                case 3:{

                    int value = read_int("Число: ");
                    std::cout << (tree.find(value) ? "Элемент найден.\n" : "Элемент не найден.\n");
                    
                    break;
                }
                case 4:{

                    std::string result = tree.to_string();
                    std::cout << "КЛП: " << (result.empty() ? "(пусто)" : result) << '\n';
                    
                    break;
                }
                case 5:{

                    if (tree.is_empty()){

                        std::cout << "Дерево пустое.\n";
                    
                    }
                    else{
                        
                        std::cout << "Корень: " << tree.get_root() << '\n';
                    
                    }
                    
                    break;
                }
                case 6:{
                    
                    std::cout << "Количество элементов: " << tree.get_count() << '\n';
                    
                    break;
                }
                case 7:{
                    
                    tree.clear();
                    std::cout << "Дерево очищено.\n";
                    
                    break;
                }

                case 8:{

                    int value = read_int("Корень поддерева: ");
                    
                    if (!tree.find(value)){
                        
                        std::cout << "Такого узла нет.\n";
                    
                    }
                    else{
                        
                        Tree<int> subtree = tree.get_subtree(value);
                        std::cout << "Поддерево (КЛП): " << subtree.to_string() << '\n';
                    
                    }
                    
                    break;
                }
                case 9:{
                    
                    std::string line = read_line("Элементы проверяемого дерева через пробел: ");
                    Tree<int> subtree = Tree<int>::from_string(line);
                    std::cout << (tree.is_subtree(subtree) ? "Поддерево входит.\n" : "Поддерево не входит.\n");
                    
                    break;
                }
                case 10:{
                    
                    int value = read_int("Сколько прибавить: ");
                    Tree<int> result = tree.map([value](int x){ return x + value;});
                    std::cout << "Результат map (КЛП): " << result.to_string() << '\n';
                    
                    break;
                }
                case 11:{
                    
                    int value = read_int("Минимальное значение: ");
                    Tree<int> result = tree.where([value](int x){ return x >= value;});
                    std::cout << "Результат where (КЛП): " << result.to_string() << '\n';
                    
                    break;
                }
                case 12:{
                    
                    long long sum = tree.reduce(0LL, [](long long res, int x){return res + x;});
                    std::cout << "Сумма элементов: " << sum << '\n';
                    
                    break;
                }
                case 13:{
                    
                    int count = read_int("Количество чисел (1..100000): ");
                    
                    if ((count < 1) || (count > 100000)){
                        
                        std::cout << "Количество должно быть от 1 до 100000.\n";
                        
                        break;
                    }
                    
                    int low = read_int("Минимум: ");
                    int high = read_int("Максимум: ");
                    
                    if (low > high){
                        
                        std::cout << "Минимум не должен превышать максимум.\n";
                        
                        break;
                    }
                    
                    std::uniform_int_distribution<int> distribution(low, high);
                    
                    for (int i = 0; i < count; ++i){
                        
                        tree.add(distribution(generator));
                    
                    }
                    
                    std::cout << "Добавлено " << count << " чисел.\n";
                    
                    break;
                }

                case 14:{
                    
                    std::string line = read_line("Введите целые числа через пробел: ");
                    Tree<int> result = Tree<int>::from_string(line);
                    tree = std::move(result);
                    std::cout << "Дерево создано: " << tree.to_string() << '\n';
                    
                    break;
                }

                default:
                    
                    std::cout << "Такого пункта нет.\n";
                    
                    break;
            }
        }
        catch (const std::exception& error){
            
            if (!std::cin){
                
                std::cout << "\nЗавершение работы.\n";
                
                return 0;
            
            }
            
            std::cout << "Ошибка: " << error.what() << '\n';
        }
    }
}