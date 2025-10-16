// Knapecz, Adam - 1DAE11
#include "pch.h"
#include "Game.h"
#include "DaeShape.h"
#include "DaeEllipse.h"
#include "DaeRectangle.h"
#include "DaeCircle.h"
#include "DaeRectLabel.h"
#include "Vector2f.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <regex>

#include <fstream>

Game::Game(const Window& window)
    : BaseGame{window}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    BasicTesting();
    CreateLabelFont();
    //CreateShapesFromFile("Shapes.txt");
    CreateShapesFromFile("../../Resources/SavedShapes.txt");
}

void Game::Cleanup()
{
    SaveShapesToFile("../../Resources/SavedShapes.txt");
    DeleteShapes();
    CloseLabelFont();
}

void Game::Update(float elapsedSec)
{
    MoveShapes(elapsedSec);
}

void Game::Draw() const
{
    ClearBackground();
    DrawShapes();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
}

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::CreateLabelFont()
{
    m_pFont = TTF_OpenFont("DIN-Light.otf", 16);
    if (m_pFont == nullptr)
    {
        std::cerr << "Game::CreateFont, error when calling TTF_OpenFont: " << TTF_GetError() << std::endl;
    }
}

void Game::CloseLabelFont()
{
    if (m_pFont != nullptr)
    {
        TTF_CloseFont(m_pFont);
        m_pFont = nullptr;
    }
}

void Game::DeleteShapes()
{
    for (DaeShape* pShape : m_pShapes)
    {
        delete pShape;
    }
    m_pShapes.clear();
}

void Game::DrawShapes() const
{
    for (DaeShape* pShape : m_pShapes)
    {
        pShape->Draw();
    }
}

void Game::MoveShapes(float elapsedSec)
{
    Vector2f transVec{};

    // Check keyboard
    const Uint8* pKeyStates = SDL_GetKeyboardState(nullptr);
    if (pKeyStates[SDL_SCANCODE_RIGHT])
    {
        transVec.x += m_TransPerSec * elapsedSec;
    }
    if (pKeyStates[SDL_SCANCODE_LEFT])
    {
        transVec.x -= m_TransPerSec * elapsedSec;
    }
    if (pKeyStates[SDL_SCANCODE_DOWN])
    {
        transVec.y -= m_TransPerSec * elapsedSec;
    }
    if (pKeyStates[SDL_SCANCODE_UP])
    {
        transVec.y += m_TransPerSec * elapsedSec;
    }

    // Move shapes
    for (DaeShape* pShape : m_pShapes)
    {
        pShape->Translate(transVec);
    }
}

Color4f Game::ToColor(const std::string& colorStr) const
{
    // TODO: 1a. Complete the ToColor function definition
    // The parameter contains a color in the format: "r,g,b,a"
    // This function converts this color into a Color4f type and returns it
    Color4f color;
    std::stringstream ss{colorStr};
    int attr{};
    if (ss)
    {
        std::string colorAttr;
        while (std::getline(ss, colorAttr, ','))
        {
            switch (attr)
            {
            case 0:
                color.r = std::stof(colorAttr);
                break;
            case 1:
                color.g = std::stof(colorAttr);
                break;
            case 2:
                color.b = std::stof(colorAttr);
                break;
            case 3:
                color.a = std::stof(colorAttr);
                break;
            }
            ++attr;
        }
    }
    return color;
}

bool Game::ToBool(const std::string& boolStr) const
{
    // TODO: 2a. Complete the ToBool function definition
    // The parameter contains a bool in text form: "true" or "false"
    // This function converts this information into a bool type and returns it
    return boolStr == "true";
}

Point2f Game::ToPoint2f(const std::string& point2fStr) const
{
    // TODO: 3a. Complete the ToPoint2f function definition
    // The parameter contains a point in the format: "x,y"
    // This function converts this information into a Point2f type and returns it
    Point2f point;
    std::stringstream ss{point2fStr};
    int attr{};
    if (ss)
    {
        std::string pointAttr;
        while (std::getline(ss, pointAttr, ','))
        {
            switch (attr)
            {
            case 0:
                point.x = std::stof(pointAttr);
                break;
            case 1:
                point.y = std::stof(pointAttr);
                break;
            }
            ++attr;
        }
    }
    return point;
}

std::string Game::GetAttributeValue(const std::string& attrName, const std::string& element) const
{
    // TODO: 4a. Complete GetAttributeValue function
    // It looks for the value of the given attribute (attrName) 
    // in the given element and returns it

    std::string attribute;
    std::regex regex{attrName + "=\"(.+?)\""};
    std::smatch match;
    if (std::regex_search(element, match, regex))
    {
        attribute = match[1];
    }
    return attribute;
}

void Game::CreateShapesFromFile(const std::string& fileName)
{
    // TODO: 5. Read the XML shape elements from the given file
    // Call for each read DAE shape element the function CreateShape
    std::ifstream file{fileName};
    if (file)
    {
        std::string shape;
        while (std::getline(file, shape, '>'))
        {
            CreateShape(shape);
        }
    }
}

void Game::SaveShapesToFile(const std::string& fileName) const
{
    // TODO: 6. Complete the definition of SaveShapesToFile
    // Save all the shapes that are in the vector m_pShapes to the given file
    // in  the same XML format
    std::ofstream file{fileName};
    if (file)
    {
        for (const DaeShape* pShape : m_pShapes)
        {
            file << pShape->ToString();
        }
    }
}

void Game::CreateShape(const std::string& shapeElement)
{
    if (shapeElement.find("DaeRectangle") != std::string::npos)
    {
        CreateRectangle(shapeElement);
    }
    else if (shapeElement.find("DaeEllipse") != std::string::npos)
    {
        CreateEllipse(shapeElement);
    }
    else if (shapeElement.find("DaeRectLabel") != std::string::npos)
    {
        CreateRectLabel(shapeElement);
    }
}

void Game::CreateRectangle(const std::string& rectangleElement)
{
    Point2f center = ToPoint2f(GetAttributeValue("Center", rectangleElement));
    float width = std::strtof(GetAttributeValue("Width", rectangleElement).data(), nullptr);
    float height = std::strtof(GetAttributeValue("Height", rectangleElement).data(), nullptr);
    Color4f color = ToColor(GetAttributeValue("Color", rectangleElement));

    m_pShapes.push_back(new DaeRectangle(center, width, height, color));
}

void Game::CreateRectLabel(const std::string& rectLabelElement)
{
    Point2f center = ToPoint2f(GetAttributeValue("Center", rectLabelElement));
    float width = std::strtof(GetAttributeValue("Width", rectLabelElement).data(), nullptr);
    float height = std::strtof(GetAttributeValue("Height", rectLabelElement).data(), nullptr);
    Color4f color = ToColor(GetAttributeValue("Color", rectLabelElement));
    std::string label = GetAttributeValue("Label", rectLabelElement);
    Color4f textColor = ToColor(GetAttributeValue("TextColor", rectLabelElement));
    std::string textColorStr = GetAttributeValue("TextColor", rectLabelElement);

    m_pShapes.push_back(new DaeRectLabel(center, width, height, color, label, textColor, m_pFont));
}

void Game::CreateEllipse(const std::string& ellipseElement)
{
    Point2f center = ToPoint2f(GetAttributeValue("Center", ellipseElement));
    float width = std::strtof(GetAttributeValue("Width", ellipseElement).data(), nullptr);
    float height = std::strtof(GetAttributeValue("Height", ellipseElement).data(), nullptr);
    Color4f color = ToColor(GetAttributeValue("Color", ellipseElement));
    bool isFilled = ToBool(GetAttributeValue("IsFilled", ellipseElement));

    m_pShapes.push_back(new DaeEllipse(center, width, height, color, isFilled));
}

#pragma region Tests
void Game::BasicTesting() const
{
    // TODO: 1b. Uncomment this call of TestToColor
    TestToColor();

    // TODO: 2b. Uncomment this call of TestToBool
    TestToBool();

    // TODO: 3b. Uncomment this call of TestToPoint2f
    TestToPoint2f();

    // TODO: 4b. Uncomment this call of TestGetAttributeValue
    TestGetAttributeValue();
}

void Game::TestToColor() const
{
    std::cout << "--> ToColor function test ";
    // Create a color in string format
    Color4f inputColor{0.5f, 0.1f, 0.3f, 0.6f};
    std::stringstream colorStream;
    colorStream << inputColor.r << "," << inputColor.g << "," << inputColor.b << "," << inputColor.a;

    // Call the function under test
    Color4f resultColor = ToColor(colorStream.str());

    // Verify the result of the function call
    const float smallValue{0.00001f};
    assert(abs(inputColor.r - resultColor.r) < smallValue);
    assert(abs(inputColor.g - resultColor.g) < smallValue);
    assert(abs(inputColor.b - resultColor.b) < smallValue);
    assert(abs(inputColor.a - resultColor.a) < smallValue);

    std::cout << " succeeded\n";
}

void Game::TestToBool() const
{
    std::cout << "--> ToBool function test ";
    assert(ToBool("false") == false);
    assert(ToBool("true") == true);

    std::cout << " succeeded\n";
}

void Game::TestToPoint2f() const
{
    std::cout << "--> ToPoint2f function test ";
    // Create a Point2f in string format
    Point2f inputPoint2f{3.21f, -4.56f};
    std::stringstream point2fStream;
    point2fStream << inputPoint2f.x << "," << inputPoint2f.y;

    // Call the function under test
    Point2f resultPoint2f = ToPoint2f(point2fStream.str());

    // Verify the result of the function call
    const float smallValue{0.00001f};
    assert(abs(inputPoint2f.x - resultPoint2f.x) < smallValue);
    assert(abs(inputPoint2f.y - resultPoint2f.y) < smallValue);

    std::cout << " succeeded\n";
}

void Game::TestGetAttributeValue() const
{
    std::cout << "--> GetAttributeValue function test ";
    // Create an attribute value
    std::string element{
        "<DaeEllipse  Center=\"20,40\"   Width=\"30\"  Height=\"40\" Color=\"1.0,0.6,0.07,1.0\" IsFilled=\"true\" />"
    };

    // Call the function under test and verify the result
    std::string result{GetAttributeValue("Center", element)};
    assert(result == "20,40");

    result = GetAttributeValue("Width", element);
    assert(result == "30");

    result = GetAttributeValue("Height", element);
    assert(result == "40");

    result = GetAttributeValue("Color", element);
    assert(result == "1.0,0.6,0.07,1.0");

    result = GetAttributeValue("IsFilled", element);
    assert(result == "true");

    std::cout << " succeeded\n";
}

#pragma endregion Tests
