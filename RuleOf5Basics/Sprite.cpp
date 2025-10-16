// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Sprite.h"

#include "Texture.h"

#include <iostream>

Sprite::Sprite(const std::string& path, int cols, int rows, float frameSec)
    : m_pTexture{new Texture(path)}
      , m_Cols(cols)
      , m_Rows(rows)
      , m_FrameSec(frameSec)
      , m_AccuSec{}
      , m_ActFrame{}
      , m_Path{path}
{
    std::cout << "Sprite: Constructor" << std::endl;
    //m_pTexture = new Texture( path );
}

Sprite::~Sprite()
{
    std::cout << "Sprite: Destructor" << std::endl;
    delete m_pTexture;
}

Sprite::Sprite(const Sprite& other)
    : m_Cols(other.m_Cols)
      , m_Rows(other.m_Rows)
      , m_FrameSec(other.m_FrameSec)
      , m_AccuSec(other.m_AccuSec)
      , m_ActFrame(other.m_ActFrame)
      , m_Path{other.m_Path}
{
    std::cout << "Sprite: Copy constructor" << std::endl;
    m_pTexture = new Texture(m_Path);
}

Sprite::Sprite(Sprite&& other) noexcept
    : m_Cols{other.m_Cols}
    , m_Rows{other.m_Rows}
    , m_FrameSec{other.m_FrameSec}
    , m_AccuSec{other.m_AccuSec}
    , m_ActFrame{other.m_ActFrame}
{
    std::cout << "Sprite: Move constructor" << std::endl;
    m_Path = other.m_Path;
    m_pTexture = other.m_pTexture;
    other.m_pTexture = nullptr;
}

Sprite& Sprite::operator=(const Sprite& other)
{
    std::cout << "Sprite: Copy assignment" << std::endl;
    if (this != &other)
    {
        m_Cols = other.m_Cols;
        m_Rows = other.m_Rows;
        m_FrameSec = other.m_FrameSec;
        m_AccuSec = other.m_AccuSec;
        m_ActFrame = other.m_ActFrame;
        m_Path = other.m_Path;
        delete m_pTexture;
        m_pTexture = new Texture(m_Path);
    }
    return *this;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
    std::cout << "Sprite: Move assignment" << std::endl;
    if (this != &other)
    {
        m_Cols = other.m_Cols;
        m_Rows = other.m_Rows;
        m_FrameSec = other.m_FrameSec;
        m_AccuSec = other.m_AccuSec;
        m_ActFrame = other.m_ActFrame;
        m_Path = other.m_Path;
        delete m_pTexture;
        m_pTexture = other.m_pTexture;
        other.m_pTexture = nullptr;
    }
    return *this;
}

void Sprite::Update(float elapsedSec)
{
    m_AccuSec += elapsedSec;

    if (m_AccuSec > m_FrameSec)
    {
        // Go to next frame
        ++m_ActFrame;
        if (m_ActFrame >= m_Cols * m_Rows)
        {
            m_ActFrame = 0;
        }

        // Only keep the remaining time
        m_AccuSec -= m_FrameSec;
    }
}

void Sprite::Draw(const Point2f& pos, float scale)
{
    // frame dimensions
    const float frameWidth{m_pTexture->GetWidth() / m_Cols};
    const float frameHeight{m_pTexture->GetHeight() / m_Rows};
    int row = m_ActFrame / m_Cols;
    int col = m_ActFrame % m_Cols;

    Rectf srcRect;
    srcRect.height = frameHeight;
    srcRect.width = frameWidth;
    srcRect.left = m_ActFrame % m_Cols * srcRect.width;
    srcRect.bottom = m_ActFrame / m_Cols * srcRect.height + srcRect.height;
    Rectf destRect{pos.x, pos.y, srcRect.width * scale, srcRect.height * scale};
    m_pTexture->Draw(destRect, srcRect);
}

float Sprite::GetFrameWidth()
{
    return m_pTexture->GetWidth() / m_Cols;
}

float Sprite::GetFrameHeight()
{
    return m_pTexture->GetHeight() / m_Rows;
}
