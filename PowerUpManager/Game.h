// Knapecz, Adam - 1DAE11
#pragma once
#include "BaseGame.h"
#include "PowerUpManager.h"

class PowerUp;

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
    // DATA MEMBERS
    const Window m_Window;
    Point2f m_MousePos;
    Rectf m_Destroyer;

    float m_PowerUpRadius;
    const size_t m_Rows;
    const size_t m_Cols;
    const size_t m_MaxNrItems;
    std::vector<Point2f> m_Centers;
    std::vector<PowerUp::Type> m_Types;
    PowerUpManager* m_pTestedManager;
    size_t m_TestedManagerSize;

    // FUNCTIONS
    void Initialize();
    void Cleanup();
    void ClearBackground() const;

    void TestWithoutDrawing();
    void InitTestWithDrawing();

    void TestSize(PowerUpManager* pTestedManager, size_t expectedSize);
    void TestAddingItems(PowerUpManager* pTestedManager, const std::vector<Point2f>& centers,
                         const std::vector<PowerUp::Type>& types);
    void TestHittingItems(PowerUpManager* pTestedManager, const std::vector<Point2f>& centers);
    void TestHittingItem(PowerUpManager* pTestedManager, const Rectf& destroyer);
    void TestHittingCircle(std::vector<Point2f>& centers, const Rectf& destroyer);

    void ShowTestMessage() const;
    void ShowNrItems() const;

    void MoveDestroyer(const Point2f& newCenter);
    void DrawDestroyer() const;
    void DrawCircles(const std::vector<Point2f>& centers, const std::vector<PowerUp::Type>& types) const;
};
