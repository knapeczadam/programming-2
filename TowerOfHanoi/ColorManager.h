// Knapecz, Adam - 1DAE11
#pragma once

class ColorManager final
{
public:
    ColorManager() = default;
    virtual ~ColorManager() = 0;
    ColorManager(const ColorManager& other) = delete;
    ColorManager(ColorManager&& other) noexcept = delete;
    ColorManager& operator=(const ColorManager& other) = delete;
    ColorManager& operator=(ColorManager&& other) noexcept = delete;

public:
    const static Color4f s_Black;
    const static Color4f s_Red;
    const static Color4f s_Green;
    const static Color4f s_Yellow;
    const static Color4f s_Brown;
    const static Color4f s_White;
    const static Color4f s_LightGray;
};
