#include <iostream>
#include <SDL.h>
#include <omp.h>
#include <cmath>
#include <string>
#include <vector>
#include <queue>

SDL_Color HSVtoRGB(float H, float S,float V){ //в хсв проще работать
    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
        std::cout << "ALERT" << H << " " << S << " " << V << std::endl;
        return {0, 0, 0};
    }
    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    int R = (r+m)*255;
    int G = (g+m)*255;
    int B = (b+m)*255;
    SDL_Color col = {B, G, R, 255};
    return col;
}

class ComplexNum final{
private:
public:
    double real;
    double im;
    ComplexNum(){// Конструктор по умолчанию (без параметров)
        real = 0;
        im = 0;
    }

    ComplexNum(double real, double im): real(real), im(im){} //Конструктор от двух чисел
    double mod(){  // модуль коплексного числа, то есть длина вектора
        return sqrt(real*real + im * im);
    }

    ComplexNum operator+(ComplexNum num){ // оператора сложения двух комлексных чисел
        return ComplexNum(real + num.real, im + num.im);
    }

    ComplexNum operator-(ComplexNum num){
        return ComplexNum(real - num.real, im - num.im);
    }

    ComplexNum operator-(){ // Унарный минус
        return ComplexNum(-real, -im);
    }

    ComplexNum operator*(ComplexNum num){ //умножение по формуле....
        return ComplexNum(real * num.real - im * num.im, real * num.im + im * num.real);
    }

    double ret_real(){ 
        return real;
    }

    double ret_im(){
        return im;
    }
};

class Basic_Application{
private:

protected:
    SDL_Window *window; // Указатель на объект окна 
    SDL_Surface *surface; // Как раз таки поверхность окна (массив пикселей)
public:
    int width; // ширина
    int height; // Высота
    
    std::string name;
    Basic_Application(std::string name, int width, int height): width(width), height(height), name(name){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // Запускаем все механизмы графической библиотеки
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        }

        window = SDL_CreateWindow(name.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN); // Создаём окно с заданным именем, координатами и размером + флаг "показать окно"
        surface = SDL_GetWindowSurface(window); // Получаем поферхность окна (на ней мы будем рисовать)
    }

    Basic_Application(Basic_Application const &src) = delete; // Т.к. мы не умеем копировать окна, ибо это бред (удаляем конструктор копирования)

    Basic_Application(Basic_Application &&other):window(other.window), surface(other.surface), width(other.width), height(other.height), name(name){
        other.window = nullptr;
        other.surface = nullptr;
    } // Конструктор перемещения, то есть мы просто перенимаем всё от "временного объекта"

    Basic_Application &operator=(Basic_Application &src) = delete;
    Basic_Application &operator=(Basic_Application &&src){
        this->width = src.width;
        this->height = src.height;
        this->name = src.name;
        this->window = src.window;
        this->surface = src.surface;
        src.window = nullptr;
        src.surface = nullptr;
    }

    ~Basic_Application(){
        SDL_DestroyWindow(window);
        surface = nullptr;
    }



    void PresentWin(){//учесть изменения поверхности (обновить окно)
        SDL_UpdateWindowSurface(window);
    }

    virtual void ReDraw() = 0; // перерисовка окна (заготовка при наследовании)

};

class ComplexPolinomial final{
public:
    int deg;
    ComplexNum c;
    ComplexPolinomial(): c(), deg(0){} 
    ComplexPolinomial(ComplexNum c_, int deg_) :c(c_), deg(deg_){}
    double CountUnitaryLimiter(double accuracy){
        double R = 1;
        while (pow(R, double(deg)) - R - c.mod() < 0){
            R += accuracy;
        }
        return R;
    }
    ComplexNum eval(ComplexNum z){
        ComplexNum x = z;
        for (int i = 0; i < deg - 1; i++){
            x = x * z;
        }
        return x + c;
    }

    int get_deg(){
        return deg;
    }
};

class Julia final : public Basic_Application {
private:
    int maxind;
    int X1;
    int Y1;
    double accuracy;
    double R;
public:
    ComplexNum left;
    ComplexNum right;
    ComplexNum LeftUp;
    ComplexNum RightDown;
    std::vector<SDL_Color> pallete;
    ComplexPolinomial f;
    Julia(
        std::string name, 
        int width, 
        int height, 
        ComplexPolinomial f, 
        ComplexNum Left, 
        ComplexNum Right, 
        int max, 
        double accuracy
        ): 
        Basic_Application(name, width, height), 
        f(f), 
        LeftUp(Left), 
        RightDown(Right), 
        maxind(max), 
        accuracy(accuracy)
        {
        left = Left;
        right = Right;
        R = f.CountUnitaryLimiter(accuracy);
        pallete.resize(maxind);
        for (int i = 0; i < maxind; i++){
            pallete[i] = HSVtoRGB(360 * (static_cast<double>((i)%maxind)/maxind), 100, 100);
        }
    }
    void JuliaCheck(ComplexNum x, int row, int col){
        int i = 0;
        ComplexNum z = x;
        
        while (i < maxind){
            if ((f.eval(z)).mod() < R){
                z = f.eval(z);
                i++;
                if (i == maxind){
                    SDL_Color cal = pallete[maxind - 1];
                    *((SDL_Color*)surface->pixels + row * width + col) = cal;
                    break;
                }
            }else{
                SDL_Color cal = pallete[i];
                *((SDL_Color*)surface->pixels + row * width + col) = cal;
                break;
            }
        }
    }
    virtual void ReDraw() override{
            size_t row;
            #pragma omp parallel for
            for (row = 0; row < height; ++row) {
                size_t col;
                #pragma omp parallel for
                for (col = 0; col < width; ++col) {
                    ComplexNum x((RightDown.ret_real() - LeftUp.ret_real()) / width * col + LeftUp.ret_real(),(RightDown.ret_im() - LeftUp.ret_im()) / height * row + LeftUp.ret_im());
                    JuliaCheck(x, row, col);
                }
            }
            SDL_UpdateWindowSurface(window);
        }
    void zoom(int row1, int column1, int row2, int column2){
        double T1 = RightDown.ret_real() - LeftUp.ret_real();
        double T2 = RightDown.ret_im() - LeftUp.ret_im();
        double T3 = LeftUp.real;
        double T4 = LeftUp.im; 
        LeftUp.real += (T1) / width * column1;
        LeftUp.im += (T2) / height * row1;
        RightDown.real = T3 + (T1) / width * (column2);
        RightDown.im = T4 + (T2) / height * (row2);
    }

    bool PopEvents(std::queue <SDL_Event>& queue){
        while(!queue.empty()) {
            SDL_Event cur_event = queue.front();
            queue.pop();
            switch (cur_event.type) {
                case SDL_QUIT:
                    return false;
                case SDL_MOUSEBUTTONDOWN:
                    if (cur_event.button.button == SDL_BUTTON_LEFT){
                        X1 = cur_event.button.x;
                        Y1 = cur_event.button.y;
                    }else
                    if (cur_event.button.button == SDL_BUTTON_RIGHT){
                        LeftUp = left;
                        RightDown = right;
                    }
                    return true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (cur_event.button.button == SDL_BUTTON_LEFT){
                        zoom(Y1, X1, cur_event.button.y, cur_event.button.x);
                    }
                    return true;
                    break;
                case SDL_KEYDOWN: {
                    switch (cur_event.key.keysym.sym) {
                        case SDLK_UP:
                            f.c.im += 0.001;
                            return true;
                            break;
    
                        case SDLK_DOWN:
                            f.c.im -= 0.001;
                            return true;
                            break;
    
                        case SDLK_RIGHT:
                            f.c.real += 0.001;                        
                            return true;
                            break;
                        
                        case SDLK_LEFT:
                            f.c.real -= 0.001;
                            return true;
                            break;
                        
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        return true;
    }
};

class Control{ //хранение нажатий
    std::queue<SDL_Event> queue;
    const int mx_queue_size = 100;
public:
    std::queue<SDL_Event>& getEvents(){
        return queue;
    }

    bool update(){
        SDL_Event event;
        int i = 0;
        while(SDL_PollEvent(&event) > 0){
            if (i < mx_queue_size){
                i++;
                queue.push(event);
            }else{
                break;
            }
        }
        return false;
    };
};

int main(int argc, char* argv[])
{
    ComplexNum z(0.28, 0.0113);
    ComplexNum left(-2, 2);
    ComplexNum right(2, -2);
    ComplexPolinomial f(z, 2);
    Julia jul1("Julia", 800, 800, f, left, right, 100, 0.1);
    SDL_Event event;
    bool running = true;
    Control control;
    while (running) {
        jul1.ReDraw();
        control.update();
        running = jul1.PopEvents(control.getEvents());
    }
    SDL_Quit();
    return 0;
}