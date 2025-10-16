// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Diamond.h"
#include "Texture.h"
#include "utils.h"
#include <iostream>

Texture* Diamond::s_pDiamondTexture{};

void Diamond::InitVertices()
{
    Point2f A{0, -m_Size / 2};
    Point2f B{m_Size / 2, 0};
    Point2f C{0, m_Size / 2};
    Point2f D{-m_Size / 2, 0};

    A.x += m_Center.x;
    A.y += m_Center.y;
    B.x += m_Center.x;
    B.y += m_Center.y;
    C.x += m_Center.x;
    C.y += m_Center.y;
    D.x += m_Center.x;
    D.y += m_Center.y;

    m_Vertices.push_back(A);
    m_Vertices.push_back(B);
    m_Vertices.push_back(C);
    m_Vertices.push_back(D);
}

Diamond::Diamond(const Point2f& center)
    : m_Center{center}
      , m_Size{48.0f}
      , m_Vertices{}
      , m_TransformedVertices{}
      , m_Translation{}
      , m_Rotation{}
      , m_Scaling{1.0f}
      , m_IsSelected{}
      , m_TransformationMatrix{}
      , m_RotationMatrix{}
      , m_ScalingMatrix{}
      , m_NegativeOffsetMatrix{}
{
    InitVertices();

    m_NegativeOffsetMatrix.SetAsTranslate(-m_Center.x, -m_Center.y);
    m_PositiveOffsetMatrix.SetAsTranslate(m_Center.x, m_Center.y);
}

Diamond::~Diamond()
{
    std::cout << "Diamond destroyed" << std::endl;
}

void Diamond::Draw() const
{
    DrawDiamondTexture();
    if (m_IsSelected)
    {
        utils::SetColor(Color4f{1, 0, 0, 1.0f});
    }
    else
    {
        utils::SetColor(Color4f{0, 0, 1, 1.0f});
    }
    utils::DrawPolygon(m_TransformedVertices, 2.0f);
}

void Diamond::TransformVertices()
{
    // TRS + offset
    m_TransformationMatrix.SetAsTranslate(m_Translation);
    m_RotationMatrix.SetAsRotate(m_Rotation);
    m_ScalingMatrix.SetAsScale(m_Scaling);
    Matrix2x3 TRS{
        m_TransformationMatrix * m_PositiveOffsetMatrix * m_RotationMatrix * m_ScalingMatrix * m_NegativeOffsetMatrix
    };
    m_TransformedVertices = TRS.Transform(m_Vertices);
}

void Diamond::DrawDiamondTexture() const
{
    glPushMatrix();
    glTranslatef(m_Translation.x, m_Translation.y, 0);
    glTranslatef(m_Center.x, m_Center.y, 0);
    glRotatef(m_Rotation, 0, 0, 1);
    glScalef(m_Scaling, m_Scaling, 1);
    glTranslatef(-s_pDiamondTexture->GetWidth() / 2, -s_pDiamondTexture->GetHeight() / 2, 0);
    s_pDiamondTexture->Draw();
    glPopMatrix();
}

void Diamond::Reset()
{
    m_Translation = Vector2f{0, 0};
    m_Rotation = 0;
    m_Scaling = 1;
}

void Diamond::OnMouseDown(const Point2f& pos)
{
    if (utils::IsPointInPolygon(pos, m_TransformedVertices))
    {
        m_IsSelected = !m_IsSelected;
    }
}

void Diamond::SetTexture(Texture* pTexture)
{
    s_pDiamondTexture = pTexture;
}

void Diamond::DeleteTexture()
{
    delete s_pDiamondTexture;
}

Vector2f Diamond::GetTranslation() const
{
    return m_Translation;
}

void Diamond::SetTranslation(const Vector2f& translation)
{
    m_Translation = translation;
}

float Diamond::GetRotation() const
{
    return m_Rotation;
}

void Diamond::SetRotation(float rotation)
{
    m_Rotation = rotation;
}

float Diamond::GetScaling() const
{
    return m_Scaling;
}

void Diamond::SetScaling(float scaling)
{
    m_Scaling = scaling;
}

bool Diamond::IsSelected() const
{
    return m_IsSelected;
}

void Diamond::IsSelected(bool isSelected)
{
    m_IsSelected = isSelected;
}

const std::vector<Point2f>& Diamond::GetVertices() const
{
    return m_TransformedVertices;
}
