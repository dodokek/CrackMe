#include <stdlib.h>
#include <assert.h>
#include "include/patcher.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main ()
{
    float bar_width = 100;
    float vbar_height = 20;
    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("img/SEASRN__.ttf");
    
    sf::RenderWindow window(sf::VideoMode(1200, 675), "Crack MC");
    window.setFramerateLimit(30);

    sf::Text text = *GenerateTextSprite (font, "Destroy the program \n            and all it eternities!!!",
                                         100, 300);

    sf::Sprite trollface  = *GenerateImageSprite("img/troll.jpeg", 0, 0);
    
    sf::Sprite herrington = *GenerateImageSprite("img/download.jpeg", 700, 50);

    PlayMusic ("img/destroy.ogg");
    sf::RectangleShape ProgBar = GenerateRectangle (bar_width, 20, 0, 500);
    sf::RectangleShape VerticalProgBar = GenerateRectangle (50, 20, 1200, 500);

    while (window.isOpen())
    {
        float time_now = clock.getElapsedTime().asMilliseconds();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || 
                time_now > 53000)
            {        
                window.close();
            }
        }
        window.clear();

        window.draw (trollface);
        window.draw (herrington);
        window.draw (text);

        bar_width += 1;
        ProgBar.setSize(sf::Vector2f(bar_width, 100));
        window.draw(ProgBar);

        if (time_now > 37000)
        {
            vbar_height += 1;
            VerticalProgBar.setSize(sf::Vector2f(200, vbar_height));
            VerticalProgBar.setPosition(1100, 500 - vbar_height);
            window.draw(VerticalProgBar);
        }

        window.display();
    }

    patch_comfile();

    return 0;
}


sf::Sprite *GenerateImageSprite (char* img_name, int x_coord, int y_coord)
{
    sf::Sprite *sprite = new sf::Sprite; 

    sf::Image *image   = new sf::Image;
    assert(image->loadFromFile(img_name));
    sf::Texture* texture = new sf::Texture;

    texture->loadFromFile(img_name);

    sprite->setTexture(*texture);   
    sprite->setPosition(x_coord, y_coord);
    // sprite->setScale(0.6, 0.6);

    
    return sprite;
}


sf::Text *GenerateTextSprite (sf::Font &font, char* content, float x_coord, float y_coord)
{
    sf::Text *text = new sf::Text;

    text->setFont(font);
    text->setFillColor(sf::Color::Red);
    text->setString(content);
    text->setCharacterSize(48);
    text->setPosition(x_coord, y_coord);

    return text;
}


sf::RectangleShape GenerateRectangle (float width, float height, float x, float y)
{
    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    rectangle.setSize(sf::Vector2f(height, width));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::Green);

    return rectangle;
}


void PlayMusic (char* filename)
{
    sf::Music *music = new sf::Music;
    assert(music->openFromFile(filename));
    music->play();
}


void patch_comfile ()
{

    char* buffer_res = (char*) calloc(MAX_BIN_FILE_LEN, sizeof(char));

    FILE* com_file = get_file ("hard_crack.com", "rb");

    int file_len = read_file (com_file, &buffer_res);
    close_file (com_file, "hard_crack.com");

    printf ("Total len: %d\n", file_len);

    for (int i = 0; i < file_len; i++)
    {
        if (buffer_res[i] == 0x75)
        {
            if (buffer_res[i+1] == 0x30)
            {
                printf ("Patching...\n");

                buffer_res[i] = 0xEB;
                buffer_res[i+1] = 0x14;
            }
        }
    }

    com_file = get_file ("sanya_cr.com", "wb+");
    fwrite(buffer_res, sizeof (char), file_len, com_file);
    close_file (com_file, "sanya_cr.com");
    free (buffer_res);
}
