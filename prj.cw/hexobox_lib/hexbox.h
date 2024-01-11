/*!
* \file hexbox.h
* \brief Библиотека для фильтра Байера
* \author Курсов Михаил БПМ-22-2
* \date Январь 2024 года
* \details Данный файл содержит в себе объявление класса библиотеки
Hexbox для создания Контейнера (Хранилища) 
*/

#ifndef Hexbox_10012024
#define Hexbox_10012024

#include <fstream>

#include <array>
#include <vector>
#include <string>

#include <algorithm>

typedef const int& cint;

//параметры перехода
/*!
* \brief Параметры перехода
* \details Структура для хранения параметров одного перехода в массиве переходов
*/
struct smooth_trans_args {
    int st_h = 0; //!< высота перехода
    int type_mat = 0; //!< тип материала/текстуры перехода
    int type_smooth = 0; //!< тип сглаживания перехода
};

/*!
* \brief Параметра гекса
* \details Структура для хранения параметров одного гекса в массиве гексов
*/
struct hex_args {
    long int x2d = 0; //!< координата X центра гекса в 2Д плоскости (XoY) (в пикселях)
    long int y2d = 0; //!< координата Y центра гекса в 2Д плоскости (XoY) (в пикселях)
    int hex_h = 0; //!< высота гекса (в 3D)
    int type_mat = 0; //!< тип материала/текстуры гекса 

    //std::array <int, 6> st = { 0,0,0,0,0,0 }; //адреса всех окружающих гекс переходов (индексы на массив переходов)
    //std::array <int, 6> vertex = { 0,0,0,0,0,0 }; //адреса вершин (нужно ли хранить?)
    //hex_args() : hex_h(0), type_mat(0){}
};

/*!
* \brief Класс для реализации контейнера
* \details Экземпляр класса может хранить необходимую информацию 
о сетке гексогонального террейна, а также необходимые методы API
для связи с другими частями проекта
*/
class Hexbox {
public:

    int w; //!< количество гексов в сетке "по ширине"
    //ширина поля (OX)(в кол-ве гексов)
    int h; //!< количество гексов в сетке "по высоте"/"длине"
    //высота(в 2D) поля (OY)(или длина...)(в кол-ве гексов)
    int count_st; //!< количество переходов в массиве переходов
    int count_hex; //!< количество гексов в массиве гексов
    int a; //!< длина стороны (ребра) каждого гекса в пикселях
    //сторона (ребро) гекса
    std::vector <hex_args> hex_grid; //!< массив шестиугольников (гексов) с параметрами для каждого гекса
    std::vector <smooth_trans_args>  st_grid; //!< массив переходов с параметрами для каждого перехода
    /*!
    * \brief Конструктор класса Hexbox
    * \details Создаёт экземпляр хранилища и инициализирует его
    * \param [in] ww  количество гексов в сетке "по ширине"
    * \param [in] hh  количество гексов в сетке "по высоте"/"длине"
    * \param [in] aa  длина ребра гекса
    */
    Hexbox(cint ww, cint hh, cint aa) {
        w = ww;
        h = hh;
        a = aa;
        count_hex = w * h;
        count_st = count_st_func(w, h);
        fe_hex_grid(w, h, a);
        fe_st_grid(w, h);
    };
    ~Hexbox() = default;

    //API
    /**
    * @addtogroup API
    * @{
    */
    hex_args GetHex(cint x, cint y); //возвращает гекс с координатами x, y
    smooth_trans_args GetSt(cint ch1, cint ch2); //возвращает переход по двум номерам двух гексов

    int GetSt_num(cint ch1, cint ch2);
    
    int GetHeight_st(cint ch1, cint ch2);


    int GetHeight_hex(cint x, cint y);
    int GetHeight_st1(cint x1, cint y1, cint x2, cint y2);

    float GetCoordX_hex_float(cint x, cint y);
    int GetCoordX_hex(cint x, cint y);
    int GetCoordY_hex(cint x, cint y);

    void PutHeight_hex(cint x, cint y, cint h);
    void PutHeight_st(cint ch1, cint ch2, cint h);
    

    /**
    * @addtogroup material_lib
    * @{
    */
    //Для материалов поверхностей
    /*!
    Определяет ближайший гекс относительно 2Д точки
    \param[in] x Координата точки по оси x 
    \param[in] y Координата точки по оси y
    \param[in] n Какой ближайший по счёту гекс нужно вернуть (от 1 до 4 включительно)
    \return Номер гекса в массиве гексов
    @ingroup material_lib
    */
    int Get_hex_near(cint x, cint y, const short& n); 
    /*!
    Определяет координату X ближайшего гекса относительно 2Д точки
    \param[in] x Координата точки по оси x
    \param[in] y Координата точки по оси y
    \param[in] n Какой ближайший по счёту гекс нужно вернуть (от 1 до 4 включительно)
    \return Координата X гекса (x2d) (в пикселях)
    @ingroup material_lib
    */
    int GetCoordX_hex_near(cint x, cint y, const short& n);
    /*!
    Определяет координату Y ближайшего гекса относительно 2Д точки
    \param[in] x Координата точки по оси x
    \param[in] y Координата точки по оси y
    \param[in] n Какой ближайший по счёту гекс нужно вернуть (от 1 до 4 включительно)
    \return Координата Y гекса (y2d) (в пикселях)
    @ingroup material_lib
    */
    int GetCoordY_hex_near(cint x, cint y, const short& n);
    //возвращает отсортированный по близости номер n гекса 
    //+ заполняет массив 4-мя расстояниями и номерами ближайших гексов относительно 2д точки, 

    //где а - расстояние от центра гекса до его вершин

    /**
    * @}
    */

    /**
    * @}
    */


    /**
    * @addtogroup Filework
    * @{
    */
    //сохраняет сетку в файл с именем name
    /*!
    Сохраняет все параметры сетки в файл с расширением ".hb"
    \param[in] name Название сохраняемого файла
    @ingroup Filework
    */
    void save(std::string name);
    /*!
    Загружает все параметры сетки из файла с расширением ".hb"
    \param[in] name Название открываемого файла
    @ingroup Filework
    */
    void load(std::string name);
    /**
    * @}
    */
    
private:
    std::pair <int, int> point_near = {};
    std::array <std::pair <unsigned int, int>, 4> near_hex = {};


    int number_ch(cint x, cint y, cint w); //номер гекса в массиве гексов(по x, y и ширине поля)(только если квадратное!)

    void fe_hex_grid(cint x, cint y, cint a); //заполнение дефолтными значениями параметров каждого гекса
    void fe_st_grid(cint x, cint y); //заполнение дефолтными значениями параметров каждого перехода

    int number_st(cint x1, cint y1, cint x2, cint y2, cint w);
    int count_st_func(cint x, cint y); //кол-во всех переходов для сетки с данными размерами(по ширине и длине)(только если квадратное!)
};

//номер перехода в массиве переходов(по координатам двух смежных гексов и ширине поля)
//Правила:
//1) номер первого гекса должен быть меньше второго
//2) если y1 = y2, то номер первого гекса должен быть меньше второго на единицу
//3) если пункт 2) не выполняется, то номер первого гекса должен быть меньше второго на ширину поля w или w + 1
//4) при невыполнении правил - бан (возвращает 0 
//     (может быть использовано как особый номер для индикации границ поля и его обработки(специальный переход для границы)))
inline int Hexbox::number_st(cint x1, cint y1, cint x2, cint y2, cint w)
{
    int ch1 = std::min(number_ch(x1, y1, w), number_ch(x2, y2, w));
    int ch2 = std::max(number_ch(x1, y1, w), number_ch(x2, y2, w));
    //if (( ch1 < ch2) || ((ch1 + 1) == ch2) || ((ch1 + w) == ch2) || ((ch1 + w + 1) == ch2) 
    if ((ch1 < ch2) && (((ch1 + 1) == ch2 && (y1 == y2)) || ((ch1 + w) == ch2) ||
        (((ch1 + w + 1) == ch2) && ((y2 % 2) == 0)) || (((ch1 + w - 1) == ch2) && (y1 % 2 == 0))))
        //&& (x1 == w && y1 == y2 )))
    {
        return (y2 - y1) * (ch1 + ch2 + 2 * y1)
            + (1 + y1 - y2) * (y1 * (3 * w - 2) + x2);
    }
    else {
        return 0;
    }
}

inline int Hexbox::count_st_func(cint x, cint y)
{
    int c = (3 * x * y) - 2 * x - 2 * y + 1;
    return c;
}

//API

//получает гекс по xy (в виде структуры гекса)
/*!
    Получает гекс по xy (в виде структуры гекса)
    \param[in] x Координата гекса по оси w (в кол-ве гексов)
    \param[in] y Координата гекса по оси h (в кол-ве гексов)
    \return Структура гекса
*/
inline hex_args Hexbox::GetHex(cint x, cint y)
{
    int n_ch = number_ch(x, y, w);
    return hex_grid[n_ch];
}

//получает переход по xy (в виде структуры перехода)
/*!
    Получает переход по xy (в виде структуры перехода)
    \param[in] x Координата гекса по оси w (в кол-ве гексов)
    \param[in] y Координата гекса по оси h (в кол-ве гексов)
    \return Структура перехода
*/
inline smooth_trans_args Hexbox::GetSt(cint ch1, cint ch2)
{
    int x1 = ch1 % w;
    int x2 = ch2 % w;
    int y1 = ch1 / w;
    int y2 = ch2 / w;
    int n_st = number_st(x1, y1, x2, y2, w);
    return st_grid[n_st - 1];
}
/*!
    Получает переход между двумя гексами
    \param[in] ch1 Номер гекса
    \param[in] ch2 Номер гекса
    \return Номер перехода в массиве переходов
*/
inline int Hexbox::GetSt_num(cint ch1, cint ch2)
{
    int x1 = ch1 % w;
    int x2 = ch2 % w;
    int y1 = ch1 / w;
    int y2 = ch2 / w;
    int n_st = number_st(x1, y1, x2, y2, w);
    return n_st;
}
/*!
    Получает высоту гекса по xy (в виде структуры перехода)
    \param[in] x Координата гекса по оси w (в кол-ве гексов)
    \param[in] y Координата гекса по оси h (в кол-ве гексов)
    \return Высота гекса
*/
inline int Hexbox::GetHeight_hex(cint x, cint y)
{
    return GetHex(x, y).hex_h;
}
/*!
    Получает высоту перехода
    \param[in] ch1 Номер первого гекса
    \param[in] ch2 Номер второго гекса
    \return Высота перехода
*/
inline int Hexbox::GetHeight_st(cint ch1, cint ch2)
{
    return GetSt(ch1,ch2).st_h;
}
/*!
    Получает высоту перехода 
    \param[in] x1 Координата w первого гекса (в кол-ве гексов)
    \param[in] y1 Координата h первого гекса (в кол-ве гексов)
    \param[in] x2 Координата w второго гекса (в кол-ве гексов)
    \param[in] y2 Координата h второго гекса (в кол-ве гексов)
    \return Высота перехода
*/
inline int Hexbox::GetHeight_st1(cint x1, cint y1, cint x2, cint y2)
{
    return GetHeight_st(number_ch(x1,y1,w), number_ch(x2,y2,w));
}

inline float Hexbox::GetCoordX_hex_float(cint x, cint y)
{
    return GetHex(x, y).x2d;
}
/*!
    Получает координату X гекса по xy (в пикселях)
    \param[in] x Координата гекса по оси w (в кол-ве гексов)
    \param[in] y Координата гекса по оси h (в кол-ве гексов)
    \return Координата X гекса
*/
inline int Hexbox::GetCoordX_hex(cint x, cint y)
{
    return GetHex(x, y).x2d;
}
/*!
    Получает координату Y гекса по xy (в пикселях)
    \param[in] x Координата гекса по оси w (в кол-ве гексов)
    \param[in] y Координата гекса по оси h (в кол-ве гексов)
    \return Координата Y гекса
*/
inline int Hexbox::GetCoordY_hex(cint x, cint y)
{
    return GetHex(x, y).y2d;
}

inline int Hexbox::GetCoordX_hex_near(cint x, cint y, const short& n)
{
    return hex_grid[Get_hex_near(x, y, n)].x2d;
}

inline int Hexbox::GetCoordY_hex_near(cint x, cint y, const short& n)
{
    return hex_grid[Get_hex_near(x, y, n)].y2d;
}
/*!
    Изменяет высоту гекса 
    \param[in] x Координата гекса по оси w (в кол-ве гексов)
    \param[in] y Координата гекса по оси h (в кол-ве гексов)
    \param[in] h Новое значение высоты
*/
inline void Hexbox::PutHeight_hex(cint x, cint y, cint h)
{
    hex_grid[number_ch(x,y,w)].hex_h = h;
}
/*!
    Изменяет высоту перехода
    \param[in] ch1 Номер первого гекса
    \param[in] ch2 Номер второго гекса
    \param[in] h Новое значение высоты
*/
inline void Hexbox::PutHeight_st(cint ch1, cint ch2, cint h)
{
    int x1 = ch1 % w;
    int x2 = ch2 % w;
    int y1 = ch1 / w;
    int y2 = ch2 / w;
    st_grid[number_st(x1, y1, x2, y2, w)].st_h = h;
}

//даёт номер ближайшего гекса от точки в 2д плоскости
inline int Hexbox::Get_hex_near(cint point_x, cint point_y, const short& n)
{
    /*int h = a * sqrt(3) / 2;
    float xh = x / h;
    float ya = y / a;
    int ia = ya / a;*/
    //if (point_near.first != point_x || point_near.second != point_y) {
        std::vector <std::pair <unsigned int, int>> distance_vec = {};
        unsigned int distance = 0;
        int x_dif = 0; //разница по х
        int y_dif = 0; //разница по у
        for (int i = 0; i < count_hex; i += 1) {
            x_dif = hex_grid[i].x2d - point_x;
            y_dif = hex_grid[i].y2d - point_y;
            distance = sqrt(x_dif * x_dif + y_dif * y_dif);
            distance_vec.push_back(std::make_pair(distance, i));

        }
        std::sort(distance_vec.begin(), distance_vec.end());

        /*int xh1 = ( x / h ) - h;
        int ya1 = ( y / (1.5 * a) ) - a;*/

        //return distance_vec[0].second;

        near_hex[0] = distance_vec[0];
        near_hex[1] = distance_vec[1];
        near_hex[2] = distance_vec[2];
        near_hex[3] = distance_vec[3];
    //}
    return near_hex[n].second;
}

//заполняет массив гексов нулями
inline void Hexbox::fe_hex_grid(cint x, cint y, cint aa)
{
    count_hex = x * y;
    float hh = aa * sqrt(3) / 2;
    hex_args def_ha = { 0, 0 };
    /*for (int i = 0; i < count_hex; i += 1) {
        hex_grid.push_back(def_ha);
    }*/
    for (int yy = 0; yy < y; yy += 1) {
        for (int xx = 0; xx < x; xx += 1) {
            def_ha.x2d = (2 * hh * xx) + ((yy % 2) * hh) + hh;
            def_ha.y2d = ((aa + hh / 2) * yy) + aa;
            hex_grid.push_back(def_ha);
        }
    }

}

//заполняет массив переходов нулями
inline void Hexbox::fe_st_grid(cint x, cint y)
{
    count_st = Hexbox::count_st_func(x, y);
    smooth_trans_args def_st = { 0, 0, 0 };
    for (int i = 0; i < count_st; i += 1) {
        st_grid.push_back(def_st);
    }
}

inline int Hexbox::number_ch(cint x, cint y, cint w)
{
    return w * y + x;
}



inline void Hexbox::save(std::string name)
{
    std::ofstream file(name + ".hb");

    if (file.is_open()) {
        file << w << " " << h << " " << a << std::endl;
        file << count_hex << " " << count_st << std::endl;
        for (int i = 0; i < count_hex - 1; i += 1) {
            file << hex_grid[i].x2d << " " \
                << hex_grid[i].y2d << " " \
                << hex_grid[i].hex_h << " " \
                << hex_grid[i].type_mat << " " \
                << std::endl;
        }
        for (int j = 0; j < count_st - 1; j += 1) {
            file << st_grid[j].st_h << " " \
                << st_grid[j].type_mat << " " \
                << st_grid[j].type_smooth << " " \
                << std::endl;
        }
    }
}

inline void Hexbox::load(std::string name)
{
    std::ifstream file(name + ".hb");

    if (file.is_open()) {
        file >> w  >> h >> a;
        file >> count_hex >> count_st ;
        for (int i = 0; i < count_hex - 1; i += 1) {
            file >> hex_grid[i].x2d  \
                >> hex_grid[i].y2d  \
                >> hex_grid[i].hex_h  \
                >> hex_grid[i].type_mat;
        }
        for (int j = 0; j < count_st - 1; j += 1) {
            file >> st_grid[j].st_h  \
                >> st_grid[j].type_mat  \
                >> st_grid[j].type_smooth;
        }
    }
}

#endif // !Hexbox_10012024