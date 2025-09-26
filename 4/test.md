### Что не так в этом коде? Перечислите, какие недостатки вы видите. Предложите свой вариант рефакторинга.

    #include <stdio.h>
    
    class Feature
    {
    public:
        enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};
    
        Feature() : type(eUnknown), points(0) {    }
    
        ~Feature()
        {
            if (points)
                delete points;
        }
    
        bool isValid() 
        {
            return type != eUnknown;
        }
    
        bool read(FILE* file)
        {        
            if (fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType))
                return false;
            short n = 0;
            switch (type) 
            {
            case eCircle: n = 3; break;
            case eTriangle:    n = 6; break;
            case eSquare: n = 8; break;
            default: type = eUnknown; return false;
            }
            points = new double[n];
            if (!points)
                return false;
            return fread(&points, sizeof(double), n, file) == n*sizeof(double);
        }
        void draw()
        {
            switch (type)
            {
            case eCircle: drawCircle(points[0], points[1], points[2]); break;
            case eTriangle:    drawPoligon(points, 6); break;
            case eSquare: drawPoligon(points, 8); break;
            }
        }
    
    protected:
        void drawCircle(double centerX, double centerY, double radius);
        void drawPoligon(double* points, int size);
    
        double* points;
        FeatureType type;        
    };
    
    int main(int argc, char* argv[])
    {
        Feature feature;
        FILE* file = fopen("features.dat", "r");
        feature.read(file);
        if (!feature.isValid())
            return 1;
        return 0;
    }

---

### Ответ:

1. Не проверяется результат fopen — file может быть NULL.
2. fopen("features.dat", "r") — файл открыт в текстовом режиме, а чтение идёт через fread, должен быть бинарный режим "rb".
3. fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType) — ошибка сравнения: fread возвращает количество элементов, а не байт. нужно сравнивать с 1. Это делает проверку всегда неверной (если sizeof(FeatureType) != 1).
4. fread(&points, sizeof(double), n, file) — передаётся адрес указателя points, а не буфер; это неверно(должно читаться в points).
5. Сравнение результата второго fread с n*sizeof(double) — опять же fread возвращает количество элементов, а не байтов.
6. В деструкторе используется delete points. для массива, выделенного new[] — нужно delete[].
7. Объявлены drawCircle и drawPoligon, но реализации в коде отсутствуют
8. В main файл не закрывается (fclose отсутствует).
9. 

Предложения по рефакторингу:
сделать так: создать общий базовый класс “Фигура”, а для каждой конретной фигуры — свой класс-наследник с собственными уникальными методами. В таком случае, для добавления новой фигуры, нужно будет только создать новый класс(этой фигуры) и его методы.
