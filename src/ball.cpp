#include "ball.h"
#include <cmath>

Ball::Ball(float x, float y, float radius, float vx, float vy, std::shared_ptr<PongPlayer> player1, std::shared_ptr<PongPlayer> player2)
    : x(x), y(y), radius(radius), vx(vx), vy(vy), p1(player1), p2(player2), cachedPoints(PixelizeFilledCircle(radius)) {}

void Ball::update(int screenWidth, int screenHeight) {
    x += vx;
    y += vy;


    if (x - radius < 0 || x + radius > screenWidth) {
        vx = -vx;

        if(x - radius <= 0){
            p2->addScore();
        }else{
            p1->addScore();
        }

        x = screenWidth / 2;
        y = screenHeight / 2;

        return;
    }

    if (y - radius < 0 || y + radius > screenHeight) vy = -vy;

    auto checkCollisionWithPaddle = [this](const std::shared_ptr<PongPlayer>& player) {
        SDL_FRect rect = player->getRect();
        return x - radius < rect.x + rect.w &&
                x + radius > rect.x &&
                y - radius < rect.y + rect.h &&
                y + radius > rect.y;
    };

    auto checkTopCollision = [this](const std::shared_ptr<PongPlayer> &player){
        SDL_FRect rect = player->getRect();
        return y + radius >= rect.y && y - radius <= rect.y + rect.h &&
        x + radius >= rect.x && x - radius <= rect.x + rect.w;
    };

    if(checkCollisionWithPaddle(p1) || checkCollisionWithPaddle(p2)) vx = -vx;  
    if(checkTopCollision(p1) || checkTopCollision(p2)) vy = -vy;
}

void Ball::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

    // Create a temporary vector to store the translated points
    std::vector<SDL_FPoint> translatedPoints;
    translatedPoints.reserve(cachedPoints.size());

    // Translate cached points based on the ball's position
    for (const auto& point : cachedPoints) {
        translatedPoints.push_back({point.x + x, point.y + y});
    }

    // Render all points at once
    SDL_RenderPoints(renderer, translatedPoints.data(), translatedPoints.size());
}

std::vector<SDL_FPoint> Ball::PixelizeFilledCircle(float radius) {
    std::vector<SDL_FPoint> points;

    const int arrSize = ((radius * 8 * 35 / 49 + 7) / 8) * 8; // round up to the nearest multiple of 8
    points.reserve(arrSize);

    const float diameter = (radius * 2);

    float x = (radius - 1);
    float y = 0;
    float tx = 1;
    float ty = 1;
    float error = (tx - diameter);

    while (x >= y) {
        // Each of the following renders an octant of the circle
        for (int i = -x; i <= x; ++i) {
            points.push_back({static_cast<float>(i), -y});
            points.push_back({static_cast<float>(i), y});
        }
        for (int i = -y; i <= y; ++i) {
            points.push_back({static_cast<float>(i), -x});
            points.push_back({static_cast<float>(i), x});
        }

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    return points;
}