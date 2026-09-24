# Smart Pointers

Реализация собственных умных указателей `UniquePtr` и `SharedPtr` на C++17.

### UniquePtr

Поддерживаются:

- создание из сырого указателя;
- запрет копирования;
- move-конструктор;
- move-присваивание;
- `operator*`;
- `operator->`;
- `get()`;
- `release()`;
- `reset()`;
- специализация для массивов `UniquePtr<T[]>`;
- `operator[]` для массивов;
- `makeUnique`;
- `makeUniqueArray`.


### SharedPtr

Поддерживаются:

- создание из сырого указателя;
- подсчёт количества владельцев;
- copy-конструктор;
- move-конструктор;
- copy-присваивание;
- move-присваивание;
- `operator*`;
- `operator->`;
- `get()`;
- `reset()`;
- `r_count()`;
- специализация для массивов `SharedPtr<T[]>`;
- `operator[]` для массивов;
- `makeShared`;
- `makeSharedArray`.


========== UNIQUE PTR ==========

N = 1000
Raw:             28 us
MyUnique:        26 us
std::unique_ptr: 43 us

N = 10000
Raw:             261 us
MyUnique:        259 us
std::unique_ptr: 570 us

N = 100000
Raw:             2577 us
MyUnique:        2644 us
std::unique_ptr: 4199 us

N = 1000000
Raw:             26156 us
MyUnique:        25399 us
std::unique_ptr: 41393 us


========== SHARED PTR ==========

N = 1000
Raw:             24 us
MyShared:        95 us
std::shared_ptr: 61 us

N = 10000
Raw:             279 us
MyShared:        497 us
std::shared_ptr: 574 us

N = 100000
Raw:             2412 us
MyShared:        4825 us
std::shared_ptr: 7059 us

N = 1000000
Raw:             25992 us
MyShared:        48365 us
std::shared_ptr: 58663 us


==327== HEAP SUMMARY:
==327==     in use at exit: 0 bytes in 0 blocks
==327==   total heap usage: 8,888,002 allocs, 8,888,002 frees, 62,290,752 bytes allocated
==327== 
==327== All heap blocks were freed -- no leaks are possible

Для тестов:

==348== HEAP SUMMARY:
==348==     in use at exit: 0 bytes in 0 blocks
==348==   total heap usage: 714 allocs, 714 frees, 172,303 bytes allocated
==348== 
==348== All heap blocks were freed -- no leaks are possible