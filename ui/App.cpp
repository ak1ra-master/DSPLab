#include "App.h"

#include <raylib.h>
#include <cmath>

#include "../core/Generators/SineGenerator.h"
#include "../core/Processing/FFT.h"
#include "../core/Processing/STFT.h"

namespace
{
    const size_t   W        = 1280;
    const size_t   H        = 720;
    const double_t SR       = 44100.0;
    const double_t FREQ     = 440.0;
    const double_t PHASE    = 0.0;
    const size_t   DURATION = 1;  // 0.5 сек

    // отступы для графиков
    const int PAD_LEFT   = 70;   // ось Y
    const int PAD_BOTTOM = 50;   // ось X
    const int PAD_TOP    = 130;  // UI
    const int PAD_RIGHT  = 20;

    // область рисования графика
    const int PLOT_X = PAD_LEFT;
    const int PLOT_Y = PAD_TOP;
    const int PLOT_W = W - PAD_LEFT - PAD_RIGHT;
    const int PLOT_H = H - PAD_TOP - PAD_BOTTOM;

    // сколько сэмплов показывать в режиме Signal (~2 периода 440Гц)
    const size_t DISPLAY_SAMPLES = 200;

    // сколько бинов STFT показывать (нижняя часть спектра)
    const size_t STFT_BINS = 64;
}

// ─────────────────────────────────────────────
Signal App::makeSignal(SignalType type)
{
    SineGenerator gen(SR, FREQ, 1.0, PHASE, DURATION);
    return gen.getSignal();
}

// ─────────────────────────────────────────────
void App::run()
{
    InitWindow(W, H, "DSPLab");
    SetTargetFPS(60);

    cachedSignal = makeSignal(currentSignal);

    while (!WindowShouldClose())
    {
        updateInput();

        BeginDrawing();
        ClearBackground(BLACK);

        switch (currentMode)
        {
            case ProcessingMode::None: drawSignal(); break;
            case ProcessingMode::FFT:  drawFFT();    break;
            case ProcessingMode::STFT: drawSTFT();   break;
        }

        drawUI();  // UI всегда поверх графиков
        EndDrawing();
    }

    CloseWindow();
}

// ─────────────────────────────────────────────
void App::updateInput()
{
    bool signalChanged = false;

    if (IsKeyPressed(KEY_ONE))
    {
        currentSignal = SignalType::Sine;
        signalChanged = true;
    }
    if (IsKeyPressed(KEY_TWO))
    {
        currentSignal = SignalType::Cosine;
        signalChanged = true;
    }

    if (signalChanged)
    {
        cachedSignal = makeSignal(currentSignal);
        fftDirty     = true;
        stftDirty    = true;
    }

    if (IsKeyPressed(KEY_Q)) currentMode = ProcessingMode::None;
    if (IsKeyPressed(KEY_W)) currentMode = ProcessingMode::FFT;
    if (IsKeyPressed(KEY_E)) currentMode = ProcessingMode::STFT;
}

// ─────────────────────────────────────────────
void App::drawUI()
{
    // полупрозрачный фон под UI чтобы текст читался поверх графика
    DrawRectangle(0, 0, W, PAD_TOP - 10, {0, 0, 0, 200});

    const char* sig  = (currentSignal == SignalType::Sine) ? "Sine" : "Cosine";
    const char* mode =
        (currentMode == ProcessingMode::None) ? "Signal" :
        (currentMode == ProcessingMode::FFT)  ? "FFT"    : "STFT";

    DrawText("1 - Sine  |  2 - Cosine",           10, 10, 20, WHITE);
    DrawText("Q - Signal  |  W - FFT  |  E - STFT", 10, 35, 20, WHITE);
    DrawText(TextFormat("Signal: %s", sig),        10, 70, 20, GREEN);
    DrawText(TextFormat("Mode:   %s", mode),       10, 95, 20, GREEN);
}

// ─────────────────────────────────────────────
// Вспомогательная: рисует оси с подписями
// xLabel, yLabel — названия осей
// xMin/xMax, yMin/yMax — диапазоны значений
// nTicksX, nTicksY — количество делений
static void drawAxes(const char* xLabel, const char* yLabel,
                     float xMin, float xMax,
                     float yMin, float yMax,
                     int nTicksX, int nTicksY)
{
    const Color axisColor = GRAY;
    const Color tickColor = DARKGRAY;
    const int   fontSize  = 20;

    // горизонтальная ось (низ графика)
    DrawLine(PLOT_X, PLOT_Y + PLOT_H, PLOT_X + PLOT_W, PLOT_Y + PLOT_H, axisColor);
    // вертикальная ось (левый край)
    DrawLine(PLOT_X, PLOT_Y, PLOT_X, PLOT_Y + PLOT_H, axisColor);

    // подпись оси X (по центру снизу)
    int xLabelW = MeasureText(xLabel, fontSize);
    DrawText(xLabel, PLOT_X + PLOT_W / 2 - xLabelW / 2, H - PAD_BOTTOM + 28, fontSize, axisColor);

    // подпись оси Y (слева вертикально — рисуем повёрнутый текст через буквы, просто пишем сверху)
    DrawText(yLabel, 5, PLOT_Y + PLOT_H / 2 - 40, fontSize, axisColor);

    // деления оси X
    for (int i = 0; i <= nTicksX; i++)
    {
        float t  = (float)i / nTicksX;
        int   px = PLOT_X + (int)(t * PLOT_W);
        DrawLine(px, PLOT_Y + PLOT_H, px, PLOT_Y + PLOT_H + 5, axisColor);

        float val = xMin + t * (xMax - xMin);
        // форматируем: если значение >= 1 и целое — без точки
        const char* label;
        if (val >= 1.0f && val == (int)val)
            label = TextFormat("%d", (int)val);
        else if (val >= 0.001f)
            label = TextFormat("%.3f", val);
        else
            label = TextFormat("%.0f", val);

        int lw = MeasureText(label, 14);
        DrawText(label, px - lw / 2, PLOT_Y + PLOT_H + 8, 14, tickColor);
    }

    // деления оси Y
    for (int i = 0; i <= nTicksY; i++)
    {
        float t  = (float)i / nTicksY;
        int   py = PLOT_Y + PLOT_H - (int)(t * PLOT_H);
        DrawLine(PLOT_X - 5, py, PLOT_X, py, axisColor);

        float val = yMin + t * (yMax - yMin);
        const char* label;
        if (std::abs(val) >= 1000.0f)
            label = TextFormat("%.0f", val);
        else if (val == (int)val)
            label = TextFormat("%d", (int)val);
        else
            label = TextFormat("%.2f", val);

        int lw = MeasureText(label, 14);
        DrawText(label, PLOT_X - lw - 8, py - 7, 14, tickColor);
    }
}

// ─────────────────────────────────────────────
void App::drawSignal()
{
    const Signal& s = cachedSignal;
    size_t N = s.getSize();
    if (N < 2) return;

    size_t displayN = std::min(N, DISPLAY_SAMPLES);

    // диапазон времени для подписей оси X (в секундах)
    float tMax = (float)(displayN - 1) / (float)SR;

    drawAxes("Time (s)", "Amplitude",
             0.0f, tMax,
             -1.0f, 1.0f,
             5, 4);

    for (size_t i = 0; i < displayN - 1; i++)
    {
        // X: время
        float x1 = PLOT_X + (float)i       / (float)(displayN - 1) * PLOT_W;
        float x2 = PLOT_X + (float)(i + 1) / (float)(displayN - 1) * PLOT_W;
        // Y: амплитуда [-1, 1] → [низ, верх] графика
        float y1 = PLOT_Y + PLOT_H / 2.0f - (float)s.getSample(i)     * (PLOT_H / 2.0f);
        float y2 = PLOT_Y + PLOT_H / 2.0f - (float)s.getSample(i + 1) * (PLOT_H / 2.0f);
        DrawLine((int)x1, (int)y1, (int)x2, (int)y2, GREEN);
    }

    // нулевая линия
    int zeroY = PLOT_Y + PLOT_H / 2;
    DrawLine(PLOT_X, zeroY, PLOT_X + PLOT_W, zeroY, {0, 100, 0, 120});
}

// ─────────────────────────────────────────────
void App::drawFFT()
{
    if (fftDirty) { cachedFFT = FFT(cachedSignal); fftDirty = false; }

    size_t N    = cachedFFT.size();
    size_t half = N / 2;
    if (half == 0) return;

    float binHz  = (float)SR / (float)N;
    float fMax   = 2000.0f;  // показываем только до 2000 Гц
    size_t maxBin = (size_t)(fMax / binHz);  // только эти бины рисуем
    maxBin = std::min(maxBin, half);

    float maxMag = 0.0f;
    for (size_t i = 0; i < maxBin; i++)
        maxMag = std::max(maxMag, (float)std::abs(cachedFFT[i]));
    if (maxMag == 0.0f) return;

    drawAxes("Frequency (Hz)", "Amplitude", 0.0f, fMax, 0.0f, 1.0f, 5, 4);

    for (size_t i = 0; i < maxBin; i++)
    {
        float mag = (float)std::abs(cachedFFT[i]) / maxMag;
        float h   = std::log1p(mag * 9.0f) / std::log1p(10.0f) * PLOT_H;
        float x   = PLOT_X + (float)i / (float)(maxBin - 1) * PLOT_W;
        DrawLine((int)x, PLOT_Y + PLOT_H, (int)x, (int)(PLOT_Y + PLOT_H - h), GREEN);
    }
}

// ─────────────────────────────────────────────
// Вспомогательная: цвет по значению 0..1 (чёрный → синий → голубой → жёлтый → белый)
static Color heatmapColor(float t)
{
    t = std::clamp(t, 0.0f, 1.0f);
    // 4 сегмента: 0-0.25 / 0.25-0.5 / 0.5-0.75 / 0.75-1.0
    if (t < 0.25f) {
        float s = t / 0.25f;
        return { 0, 0, (unsigned char)(255 * s), 255 };                          // чёрный → синий
    } else if (t < 0.5f) {
        float s = (t - 0.25f) / 0.25f;
        return { 0, (unsigned char)(255 * s), 255, 255 };                         // синий → голубой
    } else if (t < 0.75f) {
        float s = (t - 0.5f) / 0.25f;
        return { (unsigned char)(255 * s), 255, (unsigned char)(255 * (1-s)), 255 }; // голубой → жёлтый
    } else {
        float s = (t - 0.75f) / 0.25f;
        return { 255, 255, (unsigned char)(255 * s), 255 };                       // жёлтый → белый
    }
}

void App::drawSTFT()
{
    if (stftDirty) { cachedSTFT = STFT(cachedSignal, 256, 128); stftDirty = false; }

    const auto& mag = cachedSTFT.magnitude;
    if (mag.empty() || mag[0].empty()) return;

    int   cols    = (int)mag.size();
    int   allRows = (int)mag[0].size();

    float binHz = (float)SR / 256.0f;
    float fMax  = 2000.0f;
    int   rows  = (int)std::min((size_t)(fMax / binHz), (size_t)allRows);

    float tMax = (float)(cols * 128) / (float)SR;

    float maxVal = 0.0f;
    for (const auto& col : mag)
        for (int y = 0; y < rows; y++)
            maxVal = std::max(maxVal, (float)col[y]);
    if (maxVal == 0.0f) return;

    // оставляем 30px справа под легенду
    const int LEGEND_W = 30;
    const int plotW    = PLOT_W - LEGEND_W - 10;

    drawAxes("Time (s)", "Frequency (Hz)", 0.0f, tMax, 0.0f, fMax, 5, 4);

    float cellW = (float)plotW / (float)cols;
    float cellH = (float)PLOT_H / (float)rows;

    for (int x = 0; x < cols; x++)
        for (int y = 0; y < rows; y++)
        {
            float intensity = std::sqrt(std::clamp((float)mag[x][y] / maxVal, 0.0f, 1.0f));
            Color c = heatmapColor(intensity);
            DrawRectangle(
                PLOT_X + (int)(x * cellW),
                PLOT_Y + PLOT_H - (int)((y + 1) * cellH),
                (int)cellW + 1,
                (int)cellH + 1,
                c
            );
        }

    // ── легенда справа ──
    int legendX = PLOT_X + plotW + 10;
    int legendY = PLOT_Y;
    int legendH = PLOT_H;

    // градиентная полоска
    for (int py = 0; py < legendH; py++)
    {
        float t = 1.0f - (float)py / (float)(legendH - 1);  // сверху = 1 (белый), снизу = 0 (чёрный)
        Color c = heatmapColor(t);
        DrawRectangle(legendX, legendY + py, LEGEND_W, 1, c);
    }

    // подписи легенды
    DrawText("max", legendX, legendY - 20, 20, GRAY);
    DrawText("0",   legendX, legendY + legendH + 2, 14, GRAY);
}
