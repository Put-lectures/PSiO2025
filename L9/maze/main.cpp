#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

class GraphicalObject : public sf::Sprite
{
protected:
    sf::Texture texture_;

public:
    GraphicalObject(std::string tex_path, bool is_repeated = false)
    {
        if (!texture_.loadFromFile(tex_path)) {
            std::cerr << "Could not load texture" << std::endl;
            throw("Could not load texture");
        }

        setTexture(texture_);
        if (is_repeated)
            texture_.setRepeated(true);
    }
};
class Hero : public GraphicalObject
{
protected:
    int HP_;

public:
    Hero(std::string tex_path = "../tex/guy.png")
        : GraphicalObject(tex_path)
        , HP_(100)
    {}
};

class Wall : public GraphicalObject
{
public:
    Wall(int pos_x, int pos_y, int width, int height, std::string tex_path = "../tex/wall.png")
        : GraphicalObject(tex_path, true)
    {
        setTextureRect(sf::IntRect(0, 0, width, height));
        setScale(0.3, 0.3);
        setPosition(pos_x, pos_y);
    }
};
class Background : public GraphicalObject
{
public:
    Background(std::string tex_path = "../tex/grass.png",
               sf::IntRect window = sf::IntRect(0, 0, 800, 600))
        : GraphicalObject(tex_path, true)
    {
        setTextureRect(window);
    }
};
class Maze
{
    std::vector<GraphicalObject *> objects_;
    Hero *hero_;

public:
    Maze(Hero *hero)
        : hero_(hero)
    {
        objects_.emplace_back(new Background);
        objects_.emplace_back(new Wall(100, 100, 40, 400));
        objects_.emplace_back(new Wall(300, 200, 40, 400));
    }
    void move_hero(int dx, int dy) { hero_->move(sf::Vector2f(dx, dy)); }
    void display(sf::RenderWindow *window)
    {
        for (auto &el : objects_) {
            window->draw(*el);
        }
        window->draw(*hero_);
    }
    ~Maze()
    {
        for (auto &el : objects_)
            delete el;
    }
};

class GameEngine
{
private:
    Maze *maze_;
    sf::RenderWindow window_;
    Hero *hero_;

public:
    GameEngine(sf::Vector2i window_size)
        : window_(sf::VideoMode(window_size.x, window_size.y), "Maze")
    {
        maze_ = create_maze();
    }
    Maze *create_maze()
    {
        hero_ = new Hero();
        return new Maze(hero_);
    }
    void events_loop()
    {
        sf::Clock clock;
        while (window_.isOpen()) {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window_.pollEvent(event)) {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window_.close();
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Space) {
                        // guy.setTextureRect(sf::IntRect(10, 20, 20, 15));

                        std::cout << "Space released" << std::endl;
                    }

                    if (event.key.code == sf::Keyboard::Left) {
                        maze_->move_hero(1, 0);
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        maze_->move_hero(-1, 0);
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
                        std::cout << "Mouse clicked: " << mouse_pos.x << ", " << mouse_pos.y
                                  << std::endl;
                    }
                }
            }
            display();
        }
    }
    void display()
    {
        window_.clear(sf::Color::Black);
        maze_->display(&window_);
        window_.display();
    }
    ~GameEngine() { delete maze_; }
};

int main()
{
    GameEngine game(sf::Vector2i(800, 600));
    game.events_loop();
    return 0;
}
/*nt main_old()
{
    // create some shapes

    sf::Texture texture_wall;
    if (!texture_wall.loadFromFile("../tex/wall.png")) {
        return 1;
    }
    texture_wall.setRepeated(true);

    sf::Sprite wall;
    wall.setTexture(texture_wall);
    wall.setScale(0.3, 0.3);
    wall.setTextureRect(sf::IntRect(0, 0, 40, 400));
    wall.setPosition(100, 100);

    sf::Sprite wall_2;
    wall_2.setTexture(texture_wall);
    wall_2.setScale(0.3, 0.3);
    wall_2.setTextureRect(sf::IntRect(0, 0, 40, 400));
    wall_2.setPosition(300, 200);
    //    wall.setRotation(70);
    // run the program as long as the window is open
}

return 0;
}*/
