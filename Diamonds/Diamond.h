// Knapecz, Adam - 1DAE11
#pragma once
#include "Vector2f.h"
#include <vector>

#include "Matrix2x3.h"

class Texture;

class Diamond
{
public:
    void InitVertices();
    Diamond(const Point2f& center);
    ~Diamond();

    void Draw() const;
    void TransformVertices();
    void DrawDiamondTexture() const;
    void Reset();
    void OnMouseDown(const Point2f& pos);
    static void SetTexture(Texture* pTexture);
    static void DeleteTexture();
    
    Vector2f GetTranslation() const;
    void SetTranslation(const Vector2f& translation);
    float GetRotation() const;
    void SetRotation(float rotation);
    float GetScaling() const;
    void SetScaling(float scaling);
    bool IsSelected() const;
    void IsSelected(bool isSelected);
    const std::vector<Point2f>& GetVertices() const;

private:
    static Texture* s_pDiamondTexture;

    const Point2f m_Center;
    const float m_Size;
    std::vector<Point2f> m_Vertices;
    std::vector<Point2f> m_TransformedVertices;
    Vector2f m_Translation;
    float m_Rotation;
    float m_Scaling;
    bool m_IsSelected;
    
    Matrix2x3 m_TransformationMatrix;
    Matrix2x3 m_RotationMatrix;
    Matrix2x3 m_ScalingMatrix;
    Matrix2x3 m_NegativeOffsetMatrix;
    Matrix2x3 m_PositiveOffsetMatrix;
};
