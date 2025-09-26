### Есть класс CodeGenerator, который умеет генерить код на разных языках.
### Предложите рефакторинг с учетом, что количество языков будет расширяться

    class CodeGenerator
    {
    public:
        enum Lang {JAVA, C_PLUS_PLUS, PHP};
        CodeGenerator(Lang language) { _language=language; }
        std::string generateCode()
        {
            switch(_language) {
            case JAVA:        //return generated java code
            case C_PLUS_PLUS: //return generated C++ code
            case PHP:         //return generated PHP code
            }
            throw new std::logic_error("Bad language");
        }
        std::string someCodeRelatedThing() // used in generateCode()
        {
            switch(_language) {
            case JAVA:        //return generated java-related stuff
            case C_PLUS_PLUS: //return generated C++-related stuff
            case PHP:         //return generated PHP-related stuff
            }
            throw new std::logic_error("Bad language");
        }

    private:
        Lang _language;
    }

---

### Ответ:

Сделать базовый CodeGenerator с виртуальными методами generateCode() и someCodeRelatedThing(). Для каждого языка создать класс-наследник (JavaCodeGenerator и др.) и реализовать методы там. Сделать функцию createGenerator, которая на вход принимает язык и возвращает нужный объект через базовый интерфейс. При добавлении нового языка, достаточно будет создать его класс и вызов в функции createGenerator.
