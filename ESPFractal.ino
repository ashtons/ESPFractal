#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

constexpr uint8_t SCREEN_ROTATION = 1;
constexpr int MAX_ITERATIONS = 180;

// A detailed area near the boundary known as Seahorse Valley.
// Reduce VIEW_WIDTH further to zoom in more.
constexpr double VIEW_CENTER_X = -0.743643887037151;
constexpr double VIEW_CENTER_Y = 0.131825904205330;
constexpr double VIEW_WIDTH = 0.012;

uint16_t fractalColor(int iterations)
{
    if (iterations == MAX_ITERATIONS)
    {
        return TFT_BLACK;
    }

    // A simple blue-to-yellow palette in RGB565 format.
    const uint8_t red = (iterations * 9) & 0xFF;
    const uint8_t green = (iterations * 5) & 0xFF;
    const uint8_t blue = 255 - ((iterations * 3) & 0xFF);
    return tft.color565(red, green, blue);
}

void drawMandelbrot()
{
    const int width = tft.width();
    const int height = tft.height();
    const double viewHeight = VIEW_WIDTH * height / width;
    const double viewMinX = VIEW_CENTER_X - VIEW_WIDTH / 2.0;
    const double viewMinY = VIEW_CENTER_Y - viewHeight / 2.0;

    tft.startWrite();

    for (int py = 0; py < height; ++py)
    {
        const double cy = viewMinY + viewHeight * py / (height - 1);

        for (int px = 0; px < width; ++px)
        {
            const double cx = viewMinX + VIEW_WIDTH * px / (width - 1);

            double x = 0.0;
            double y = 0.0;
            int iteration = 0;

            while ((x * x + y * y <= 4.0) && iteration < MAX_ITERATIONS)
            {
                const double nextX = x * x - y * y + cx;
                y = 2.0 * x * y + cy;
                x = nextX;
                ++iteration;
            }

            tft.drawPixel(px, py, fractalColor(iteration));
        }

        // Long renders can otherwise trigger the ESP32 task watchdog.
        if ((py & 7) == 0)
        {
            yield();
        }
    }

    tft.endWrite();
}

void setup()
{
    tft.init();
    tft.setRotation(SCREEN_ROTATION);
    tft.fillScreen(TFT_BLACK);

    drawMandelbrot();
}

void loop()
{
    // The image is static, so it only needs to be rendered once.
}
