// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "ScoreManager.h"

int ScoreManager::s_Score{};

int ScoreManager::GetScore()
{
    return s_Score;
}

int ScoreManager::IncreaseScore()
{
    return ++s_Score;
}
