#include "Drawing.h"

void CheckerboardDraw(const Vector2 position, const unsigned char squareSize, const char countX, const char countY, const Color color1, const Color color2)
{
    bool drawSecondColor = false;
    for (char i = 0; i < countX; i++)
    {
        for (char j = 0; j < countY; j++)
        {
            drawSecondColor = !drawSecondColor;
            DrawRectangle(position.x + squareSize * i, position.y + squareSize * j, squareSize, squareSize, drawSecondColor ? color2 : color1);
        }
        drawSecondColor = !drawSecondColor;
    }
}

void ScoreToString(unsigned char score, char* str)
{
    if (score > 99)
    {
        str[0] = score / 100 + '0';
        score -= score / 100 * 100;
        str[1] = score / 10 + '0';
        score -= score / 10 * 10;
        str[2] = score + '0';
        str[3] = 0;
        return;
    }

    if (score > 9)
    {
        str[0] = score / 10 + '0';
        score -= score / 10 * 10;
        str[1] = score + '0';
        str[2] = 0;
        return;
    }

    str[0] = score + '0';
    str[1] = 0;
}

void DrawFade()
{
    const float a = 1 - States_Get()->timeInState / FADE_TIME;
    if (a < 0)
        return;
    DrawTexture(g_gameData->prevRenderTexture.texture, 0, 0, ColorAlpha(WHITE, a));
}