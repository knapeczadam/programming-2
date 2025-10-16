// Knapecz, Adam - 1DAE11

#include "pch.h"
#include "Game.h"
#include "fstream"
#include "utils.h"
#include "regex"

Game::Game(const Window& window)
    : BaseGame{window}
      , m_Vertices{}
{
    Initialize();
}

Game::~Game()
{
    Cleanup();
}

void Game::Initialize()
{
    //CreatePolygonFromFile("../../Resources/example1.obj");
    CreatePolygonsFromFile("../../Resources/example2.obj");
}

void Game::Cleanup()
{
}

void Game::Update(float elapsedSec)
{
    // Check keyboard state
    //const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
    //if ( pStates[SDL_SCANCODE_RIGHT] )
    //{
    //	std::cout << "Right arrow key is down\n";
    //}
    //if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
    //{
    //	std::cout << "Left and up arrow keys are down\n";
    //}
}

void Game::Draw() const
{
    ClearBackground();
    utils::SetColor(Color4f{1, 0, 0, 1});
    for (const auto& vertices : m_Polygons)
    {
        utils::DrawPolygon(vertices);
    }
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
    //std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
    //std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
    //switch ( e.keysym.sym )
    //{
    //case SDLK_LEFT:
    //	//std::cout << "Left arrow key released\n";
    //	break;
    //case SDLK_RIGHT:
    //	//std::cout << "`Right arrow key released\n";
    //	break;
    //case SDLK_1:
    //case SDLK_KP_1:
    //	//std::cout << "Key 1 released\n";
    //	break;
    //}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
    //std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
    //std::cout << "MOUSEBUTTONDOWN event: ";
    //switch ( e.button )
    //{
    //case SDL_BUTTON_LEFT:
    //	std::cout << " left button " << std::endl;
    //	break;
    //case SDL_BUTTON_RIGHT:
    //	std::cout << " right button " << std::endl;
    //	break;
    //case SDL_BUTTON_MIDDLE:
    //	std::cout << " middle button " << std::endl;
    //	break;
    //}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
    //std::cout << "MOUSEBUTTONUP event: ";
    //switch ( e.button )
    //{
    //case SDL_BUTTON_LEFT:
    //	std::cout << " left button " << std::endl;
    //	break;
    //case SDL_BUTTON_RIGHT:
    //	std::cout << " right button " << std::endl;
    //	break;
    //case SDL_BUTTON_MIDDLE:
    //	std::cout << " middle button " << std::endl;
    //	break;
    //}
}

void Game::ClearBackground() const
{
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::CreatePolygonFromFile(const std::string& objFilePath)
{
    std::ifstream file{objFilePath};
    if (file)
    {
        std::regex regex{R"(v\s(\d+)\s(\d+)\s(\d+))"};
        std::smatch match{};
        std::string line;
        while (std::getline(file, line))
        {
            if (line[0] == 'v')
            {
                if (std::regex_match(line, match, regex))
                {
                    m_Vertices.emplace_back(std::stof(match[1]), std::stof(match[2]));
                }
            }
        }
    }
}

void Game::CreatePolygonsFromFile(const std::string& objFilePath)
{
    std::ifstream file{objFilePath};
    if (file)
    {
        std::regex regex{R"(v\s(\d+)\s(\d+)\s(\d+))"};
        std::smatch match{};
        std::string line;
        std::vector<Point2f> vertices{};
        while (std::getline(file, line))
        {
            if (line[0] == 'o')
            {
                if (vertices.empty())
                {
                    continue;
                }
                m_Polygons.emplace_back(vertices);
                vertices.clear();
            }
            if (line[0] == 'v')
            {
                if (std::regex_match(line, match, regex))
                {
                    vertices.emplace_back(std::stof(match[1]), std::stof(match[2]));
                }
            }
        }
        if (!vertices.empty())
        {
            m_Polygons.emplace_back(vertices);
        }
    }
}
