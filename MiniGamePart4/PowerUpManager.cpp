// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "PowerUpManager.h"
#include <algorithm>

PowerUpManager::PowerUpManager()
{
}

PowerUpManager::~PowerUpManager()
{
    std::ranges::for_each(m_pItems, [](PowerUp* e) { delete e; });
}

PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
    PowerUp* powerUp{new PowerUp{center, type}};
    m_pItems.push_back(powerUp);
    return powerUp;
}

void PowerUpManager::Update(float elapsedSec)
{
    std::ranges::for_each(m_pItems, [=](PowerUp* e) { e->Update(elapsedSec); });
}

void PowerUpManager::Draw() const
{
    std::ranges::for_each(m_pItems, [](PowerUp* e) { e->Draw(); });
}

size_t PowerUpManager::Size() const
{
    return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
    return std::erase_if(m_pItems, [&](PowerUp* e) { return e->IsOverlapping(rect); });
}
