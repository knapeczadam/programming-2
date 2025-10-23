// Knapecz, Adam - 1DAE11

#pragma once
#include "BaseGame.h"
#include <vector>

#include "Matrix2x3.h"
#include "Vector2f.h"

class Texture;

class Game : public BaseGame
{
public:
    explicit Game(const Window& window);
    Game(const Game& other) = delete;
    Game& operator=(const Game& other) = delete;
    Game(Game&& other) = delete;
    Game& operator=(Game&& other) = delete;
    // http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
    ~Game();

    void Update(float elapsedSec) override;
    void Draw() const override;

    // Event handling
    void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) override;
    void ProcessKeyUpEvent(const SDL_KeyboardEvent& e) override;
    void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e) override;
    void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) override;
    void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) override;

private:
    // FUNCTIONS
    void Initialize();
    void Cleanup();
    void ClearBackground() const;
    void PrintInfo() const;
    void RotateDiamond();
    void ScaleDiamond();
    void TransformDiamond();
    void ResetTranslationFactors();
    void TranslateDiamond();
    void OnMouseDown(float x, float y);
    void DrawDiamondTexture() const;

    std::vector<Point2f> m_Vertices;
    std::vector<Point2f> m_TransformedVertices;
    Point2f m_DiamondCenter;

    const float m_Size;
    float m_Angle;
    float m_ScalingFactor;
    Vector2f m_Translation;
    bool m_IsSelected;
    Texture* m_pDiamondTexture;

    Matrix2x3 m_TransformationMatrix;
    Matrix2x3 m_RotationMatrix;
    Matrix2x3 m_ScalingMatrix;
    Matrix2x3 m_OffsetMatrix;
};
