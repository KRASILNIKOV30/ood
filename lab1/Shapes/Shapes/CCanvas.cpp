#include "CCanvas.h"
#include "../../../external/SDL2_gfx/SDL2_gfxPrimitives.h"
#include "Common.h"

CCanvas::CCanvas(SDL_Window* window)
    : m_renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
{
    SDL_RenderClear(m_renderer);
    SetColor(m_color);
}

void CCanvas::MoveTo(Point point)
{
    m_point = point;
}

void CCanvas::LineTo(Point point)
{
    SDL_RenderDrawLineF(m_renderer, (float)m_point.x, (float)m_point.y, (float)point.x, (float)point.y);
    m_point = point;
}

void CCanvas::SetColor(Color color)
{
    m_color = color;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    ParseColor(m_color, red, green, blue);
    SDL_SetRenderDrawColor(m_renderer, red, green, blue, 0xFF);
}

void CCanvas::DrawEllipse(Point center, double rx, double ry)
{
    aaellipseColor(m_renderer, (Sint16)center.x, (Sint16)center.y, (Sint16)rx, (Sint16)ry, m_color);
}

void CCanvas::DrawText(Point leftTop, double fontSize, std::string text)
{
    stringColor(m_renderer, leftTop.x, leftTop.y, text.c_str(), m_color);
}

void CCanvas::ParseColor(Color color, Color& red, Color& green, Color& blue) const
{
    std::string colorStr = GetHexStrFromUint32(color, COLOR_LEN);
    std::string redStr = colorStr.substr(0, 2);
    std::string greenStr = colorStr.substr(2, 2);
    std::string blueStr = colorStr.substr(4, 2);
    StringToUint32(redStr, red);
    StringToUint32(greenStr, green);
    StringToUint32(blueStr, blue);
}

void CCanvas::Render()
{
    SDL_RenderPresent(m_renderer);
}
