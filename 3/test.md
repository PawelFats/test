### Все ли хорошо в этом коде?

## Файл legacy.c
---
    int values[3];
---

## Файл modern.cpp
---
    #define LEGACY_SIZE 3
    extern int *values;

    class MyBlah {...};

    class Adapter
    {
    public:
        Adapter()
        {
    for (int i = 0; i < LEGACY_SIZE; ++i)
                map_[values[i]] = new MyBlah (values[i]);
        }
    private:
        std::map<int, MyBlah *> map_;
    };

---

### Ответ:

1. В legacy.c массив int values[3];. В modern.cpp — объявлено extern int *values;(указатель). 
Это разные типы - ошибка.

2. Модуль legacy.c не подключается в modern.cpp.

3. #define LEGACY_SIZE 3 - наверняка изначально полагается, что эта константа отвечает за размер массива. Но в текущем варианте программы, она не используется при создании массива. И если константа изменит значение, то программа выдаст ошибку.

4. map_ хранит указатели MyBlah* и создаются через new. Если не освободить, то будет утечка.
