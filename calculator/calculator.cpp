// В этом файле определения функций.
// За основу возьмите решение предыдущей задачи.
#include "calculator.h"

#include <iostream>
#include <cmath>


bool ReadNumber(Number& result){

    Number number;

    if (!(std::cin >> number)) {
        //Если будет введено что-либо, что нелья преобразовать
        //в тип double, например буквы, функция вернет false
        std::cerr << "Error: Numeric operand expected";
        return false;
    }

    //Если число валидно, оно будет присвоено в перменную result.
    //Функция вернет true.
    result = number;
    return true;

}


bool RunCalculatorCycle(){

    Number
        active_number, /*хранит значение операций + и -, пока не встретится * или / */
        number,/*хранит значение результата, который выводится после ввода "=" */
        number_in_memory; /*хранит значение переменной в памяти, если введена команда s*/

    bool was_save = false; /*хранит флаг, было ли уже сохраненео какое либо число в number_in_memory*/



    std::string operation; /*хранит значение одной операции*/

    if(!ReadNumber(number))
    {
        return false;
    }
    else{
        {
            while(true){

                std::cin >> operation;

                // Обрабокта операции сложение
                if(operation == "+"){
                    if(!ReadNumber(active_number)){
                        return false;
                    }
                    else{

                        number += active_number;
                    }
                }

                // Обрабокта операции вычитание
                else if(operation == "-"){
                    if(!ReadNumber(active_number)){
                        return false;
                    }
                    else{
                        number -= active_number;
                    }
                }

                // Обрабокта операции умножение
                else if(operation == "*"){
                    if(!ReadNumber(active_number)){
                        return false;
                    }
                    else{
                        number *= active_number;
                    }
                }

                // Обрабокта операции деление
                else if(operation == "/"){
                    if(!ReadNumber(active_number)){
                        return false;
                    }
                    else{
                        number /= active_number;
                    }
                }

                // Обрабокта операции возведение в степень
                else if(operation == "**"){
                    if(!ReadNumber(active_number)){
                        return false;
                    }
                    else{
                        number = std::pow(number,active_number);
                    }
                }

                // Обрабокта операции вывода результата операций
                else if(operation == "="){
                    std::cout << number << std::endl;
                }

                // Обрабокта операции явного указания значения итогового числа
                else if(operation == ":"){
                    if(!ReadNumber(active_number)){
                        return false;
                    }
                    else{
                        number = active_number;
                    }
                }

                // Обрабокта операции обнуление
                else if(operation == "c"){
                    number = 0;
                }

                // Обрабокта операции сохранение резульата в перменную
                else if(operation == "s"){
                    number_in_memory = number;

                    // Если операция была вызвана, ставится флаг, указывающий, в переменную записали данные
                    was_save = true;
                }

                // Обрабокта операции использование сохраненной переменной
                else if(operation == "l"){
                    if(was_save){
                        //если флаг записи в переменную true, используем сохраненной значение
                        number = number_in_memory;
                    }
                    else{
                        //иначе ошибка
                        std::cerr<< "Error: Memory is empty";
                        return false;
                    }
                }


                else if(operation == "q"){
                    return true;
                }


                else{
                    std::cerr << "Error: Unknown token " << operation << std::endl;
                    return false;
                }
            }

        }
    }

    return false;
}
