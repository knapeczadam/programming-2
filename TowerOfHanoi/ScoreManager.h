// Knapecz, Adam - 1DAE11
#pragma once

class ScoreManager final
{
public:
    ScoreManager() = default;
    virtual ~ScoreManager() = 0;
    ScoreManager(const ScoreManager& other) = delete;
    ScoreManager(ScoreManager&& other) noexcept = delete;
    ScoreManager& operator=(const ScoreManager& other) = delete;
    ScoreManager& operator=(ScoreManager&& other) noexcept = delete;

    static int GetScore();
    static int IncreaseScore();

private:
    static int s_Score;
};
