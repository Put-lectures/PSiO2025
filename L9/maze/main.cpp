#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
class Command
{
public:
    Command() {}
    virtual void execute() {

    };
};

class GraphicalObject : public sf::Sprite
{
protected:
    sf::Texture texture_;
    bool is_obstacle_;
    Command *action_;

public:
    GraphicalObject(std::string tex_path,
                    bool is_repeated = false,
                    bool is_obstacle = true,
                    Command *action = nullptr)
        : is_obstacle_(is_obstacle)
        , action_(action)
    {
        if (!texture_.loadFromFile(tex_path)) {
            std::cerr << "Could not load texture" << std::endl;
            throw("Could not load texture");
        }

        setTexture(texture_);
        if (is_repeated)
            texture_.setRepeated(true);
    }
    bool is_obstacle() { return is_obstacle_; }
    virtual void collision_handling(GraphicalObject *object)
    {
        if (action_ != nullptr)
            action_->execute();
    }
};
class Hero : public GraphicalObject
{
protected:
    int HP_;
    int x_old_, y_old_;

public:
    Hero(std::string tex_path = "../tex/guy.png")
        : GraphicalObject(tex_path)
        , HP_(100)
        , x_old_(0)
        , y_old_(0)
    {}
    void move(const sf::Vector2f &offset)
    {
        sf::Vector2f pos = getPosition();
        x_old_ = pos.x;
        y_old_ = pos.y;
        sf::Sprite::move(offset);
    }
    void addHP(int delta)
    {
        HP_ += delta;

        std::cout << HP_ << std::endl;
    }
    void collision_handling(GraphicalObject *object) { setPosition(sf::Vector2f(x_old_, y_old_)); }
};

class Decorator : public Hero
{
protected:
    Hero *component_;
    sf::RectangleShape rect_;

public:
    Decorator(Hero *c, sf::Color color)
        : component_(c)
    {
        rect_.setSize(sf::Vector2f(20, 10));
        rect_.setFillColor(color);
    }
    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(*component_, states);
        target.draw(rect_, states);
    }
};
class Add_HP : public Command
{
    Hero *hero_;
    int delta_;

public:
    Add_HP(Hero *h, int delta)
        : hero_(h)
        , delta_(delta)
    {}
    virtual void execute() { hero_->addHP(delta_); };
};
class Teleport : public Command
{
    Hero *hero_;
    sf::Vector2f pos_;

public:
    Teleport(Hero *h, sf::Vector2f pos)
        : hero_(h)
        , pos_(pos)
    {}
    virtual void execute() { hero_->setPosition(pos_); };
};
class HPIndicator : public Decorator
{
public:
    HPIndicator(Hero *c, sf::Color color, sf::Vector2f pos)
        : Decorator(c, color)
    {
        rect_.setPosition(pos);
    }
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

class Bonus : public GraphicalObject
{
public:
    Bonus(int pos_x,
          int pos_y,
          Command *action,
          int width = 30,
          int height = 30,
          std::string tex_path = "../tex/box.png")
        : GraphicalObject(tex_path, false)
    {
        action_ = action;
        setTextureRect(sf::IntRect(0, 0, width, height));
        setPosition(pos_x, pos_y);
    }
    void collision_handling(GraphicalObject *object)
    {
        action_->execute();
        is_obstacle_ = false;
    }
};
class Background : public GraphicalObject
{
public:
    Background(std::string tex_path = "../tex/grass.png",
               sf::IntRect window = sf::IntRect(0, 0, 800, 600))
        : GraphicalObject(tex_path, true, false)
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
        // create();
    }

    void move_hero(int dx, int dy)
    {
        hero_->move(sf::Vector2f(dx, dy));
        check_collisions();
    }
    void display(sf::RenderWindow *window)
    {
        for (auto &el : objects_) {
            window->draw(*el);
        }
        window->draw(*hero_);
    }
    void check_collisions()
    {
        sf::FloatRect bb = hero_->getGlobalBounds();
        for (auto &el : objects_) {
            if (!el->is_obstacle())
                continue;
            sf::FloatRect obb = el->getGlobalBounds();
            if (bb.intersects(obb)) {
                hero_->collision_handling(el);
                el->collision_handling(hero_);

                std::cout << "collision" << std::endl;
                // wrong usecase for liskov substitiotion principle
                // Wall *w = dynamic_cast<Wall *>(el);
                // if (w != nullptr) {
                //     std::cout << "this is a wall" << std::endl;
                // }
            }
        }
    }
    ~Maze()
    {
        for (auto &el : objects_)
            delete el;
    }
    void add_object(GraphicalObject *object) { objects_.emplace_back(object); }
};
class AbstractMazeFactory
{
public:
    virtual Maze *create(Hero *hero) = 0;
};

class MazeFactory : public AbstractMazeFactory
{
public:
    MazeFactory() {};

    Maze *create(Hero *hero)
    {
        Maze *tmp = new Maze(hero);
        tmp->add_object(new Background);
        tmp->add_object(new Wall(100, 100, 40, 400));
        tmp->add_object(new Wall(300, 200, 40, 400));
        Add_HP *a1 = new Add_HP(hero, 10);
        tmp->add_object(new Bonus(50, 80, a1));
        Add_HP *a2 = new Add_HP(hero, -10);
        tmp->add_object(new Bonus(250, 180, a2));
        Teleport *t1 = new Teleport(hero, sf::Vector2f(10, 10));
        tmp->add_object(new Bonus(350, 10, t1));
        return tmp;
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
        // Decorator *d_hero = new Decorator(hero_, sf::Color::Red);
        HPIndicator *hp_hero = new HPIndicator(hero_, sf::Color::Blue, sf::Vector2f(0, 60));
        MazeFactory factory;
        return factory.create(hp_hero);
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
                        maze_->move_hero(-4, 0);
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        maze_->move_hero(4, 0);
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        maze_->move_hero(0, 4);
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        maze_->move_hero(0, -4);
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
