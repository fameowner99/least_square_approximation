#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "Matrix.hpp"

# define FPS 15
# define WIDTH 1300
# define HEIGHT 1000
# define MUL 50

void draw_lines(SDL_Renderer *renderer)
{
   for (int y = 0; y < HEIGHT; y += 1)
   {
       SDL_RenderDrawPoint(renderer, WIDTH / 2, y);
   }
   for (int x = 0; x < WIDTH; ++x)
   {
       SDL_RenderDrawPoint(renderer, x, HEIGHT / 2);
   }
}

void draw_points(SDL_Renderer *renderer, std::vector<std::pair<float, float>> &points)
{


    for (const auto &item : points)
    {
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + item.first * MUL, HEIGHT / 2 - item.second * MUL);
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + item.first * MUL - 1, HEIGHT / 2 - item.second * MUL);
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + item.first * MUL, HEIGHT / 2 - item.second * MUL - 1);
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + item.first * MUL + 1, HEIGHT / 2 - item.second * MUL);
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + item.first * MUL, HEIGHT / 2 - item.second * MUL + 1);
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + item.first * MUL - 1, HEIGHT / 2 - item.second * MUL - 1);
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + item.first * MUL + 1, HEIGHT / 2 - item.second * MUL + 1);
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + item.first * MUL - 1, HEIGHT / 2 - item.second * MUL + 1);
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + item.first * MUL + 1, HEIGHT / 2 - item.second * MUL - 1);
    }

}

void fill_matrix(Matrix &A, Matrix &b, std::vector<std::pair<float, float>> &points)
{
    int r = A.getSizeRows();
    int c = A.getSizeColomn();



    for (int i = 0; i < r; ++i)
    {
        for (int v = 0; v < points.size(); ++v)
        {
            b[i][0] = b[i][0] + points[v].second * pow(points[v].first,i);
        }
        for (int j = 0; j < c; ++j)
        {
            for (int k = 0; k < points.size(); ++k)
            {
                A[i][j] = A[i][j] + pow(points[k].first, j + i);
            }
        }
    }
    A[0][0] = points.size();
}

void draw_quadratic_plot(SDL_Renderer *renderer, Matrix &res)
{
    double y;

    for (double x = -10; x <= 10; x += 0.01)
    {
        y = res[0][0] + res[1][0] * x + res[2][0] * x * x;
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + x * MUL, HEIGHT / 2 - y * MUL);
    }

}
void draw_line_plot(SDL_Renderer *renderer, Matrix &res)
{
    double y;

    for (double x = -10; x <= 10; x += 0.01)
    {
        y = res[0][0] + res[1][0] * x;
        SDL_RenderDrawPoint(renderer, WIDTH / 2 + x * MUL, HEIGHT / 2 - y * MUL);
    }
}


void print_error(Matrix &res, Matrix &res1, std::vector<std::pair<float, float>> &points)
{
    double sum = 0, sum1 = 0;

    for (const auto &item : points)
    {
        sum += (res[0][0] + res[1][0] * item.first + res[2][0] * item.first * item.first - item.second) *
                (res[0][0] + res[1][0] * item.first + res[2][0] * item.first * item.first - item.second);
        sum1 += (res1[0][0] + res[1][0] * item.first - item.second) * (res1[0][0] + res[1][0] * item.first - item.second);
    }
    std::cout << "ERROR FOR QUADRATIC = " << sum << std::endl;
    std::cout << "ERROR FOR LINEAR = " << sum1 << std::endl;
}

void lab1()
{
    SDL_Window   *window;
    SDL_Renderer *renderer;
    SDL_Event    event;
    Uint32       start;

    SDL_CreateWindowAndRenderer(1300, 1000, 0, &window, &renderer);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    std::vector<std::pair<float, float>> points = {{0,0},{0.79, 0.71}, {1.6, 1}, {2.36, 0.71}, {3.14, 0}};
    //std::vector<std::pair<float, float>> points = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6,6}, {7, 7}, {8,8}};


    Matrix A(3, 3);
    Matrix A1(2, 2);
    Matrix b1(2, 1);
    Matrix b(3, 1);
    Matrix res(3, 1);
    Matrix res1(2, 1);
    fill_matrix(A, b, points);
    fill_matrix(A1, b1, points);
   // A1.print();
    //b1.print();


    res = (A.transpose() * A).inverse() * (A.transpose()) * b;
    res1 = (A1.transpose() * A1).inverse() * (A1.transpose()) * b1;
    print_error(res, res1, points);
    //res1.print();


    while (true)
    {
        SDL_RenderClear(renderer);
        if (SDL_PollEvent(&event) && (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE))
            break;
        start = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, 169, 169, 169, 0);
        draw_lines(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 128, 0, 0);
        draw_points(renderer, points);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        draw_quadratic_plot(renderer,res);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
        draw_line_plot(renderer, res1);


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);

        if (1000 / FPS > SDL_GetTicks() - start)
        {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}