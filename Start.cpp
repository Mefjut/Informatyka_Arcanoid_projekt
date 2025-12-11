#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

#include "Gra.h"
#include "Menu.h"

enum class StanAplikacji
{
    Menu,
    Gra,
    Wyniki,
    GameOver,
    Wyjscie
};

std::vector<std::string> wczytajWyniki()
{
    std::vector<std::string> wyniki;
    std::ifstream plik("wyniki.txt");

    if (!plik.is_open())
    {
        wyniki.push_back("Brak zapisanych wynikow.");
        return wyniki;
    }

    std::string linia;
    while (std::getline(plik, linia))
        wyniki.push_back(linia);

    if (wyniki.empty())
        wyniki.push_back("Brak zapisanych wynikow.");

    return wyniki;
}

void rysujWyniki(sf::RenderWindow& okno, const std::vector<std::string>& wyniki)
{
    sf::Font f;
    f.loadFromFile("arial.ttf");

    okno.clear(sf::Color(25, 25, 32));

    sf::Text naglowek("OSTATNIE WYNIKI", f, 36);
    naglowek.setPosition(180, 50);
    naglowek.setFillColor(sf::Color::White);
    okno.draw(naglowek);

    int y = 150;
    for (const std::string& w : wyniki)
    {
        sf::Text t(w, f, 26);
        t.setPosition(200, y);
        t.setFillColor(sf::Color(200, 200, 200));
        okno.draw(t);
        y += 40;
    }

    sf::Text opis("\nWcisnij ESC aby wrocic do MENU", f, 22);
    opis.setPosition(160, 480);
    opis.setFillColor(sf::Color(180, 180, 180));
    okno.draw(opis);

    okno.display();
}

int main()
{
    sf::RenderWindow okno(sf::VideoMode(800, 600), "Arkanoid – Projekt");
    okno.setFramerateLimit(60);

    Menu menu(okno.getSize().x, okno.getSize().y);
    Gra gra;

    StanAplikacji stan = StanAplikacji::Menu;
    sf::Clock zegar;

    std::vector<std::string> wyniki;

    while (okno.isOpen())
    {
        sf::Event e;
        while (okno.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                okno.close();

            if (stan == StanAplikacji::Menu)
            {
                if (e.type == sf::Event::KeyPressed)
                {
                    if (e.key.code == sf::Keyboard::Up) menu.przesunWGore();
                    if (e.key.code == sf::Keyboard::Down) menu.przesunWDol();

                    if (e.key.code == sf::Keyboard::Enter)
                    {
                        int opcja = menu.wezWybranaOpcje();

                        if (opcja == 0)  
                        {
                            gra.resetGra();
                            stan = StanAplikacji::Gra;
                        }
                        else if (opcja == 1)   
                        {
                            if (gra.wczytajGre("zapis.txt"))
                            {
                               
                                stan = StanAplikacji::Gra;
                            }
                            else
                                std::cout << "Blad wczytywania zapisu!\n";
                        }
                        else if (opcja == 2)    
                        {
                            wyniki = wczytajWyniki();
                            stan = StanAplikacji::Wyniki;
                        }
                        else if (opcja == 3)   
                        {
                            okno.close();
                        }
                    }
                }
            }

            
            else if (stan == StanAplikacji::Gra)
            {
                if (e.type == sf::Event::KeyPressed)
                {
                    if (e.key.code == sf::Keyboard::Escape)
                        stan = StanAplikacji::Menu;

                    if (e.key.code == sf::Keyboard::F5)
                    {
                        if (gra.zapiszGre("zapis.txt"))
                            std::cout << "Stan gry zapisany!\n";
                    }
                }
            }


            else if (stan == StanAplikacji::Wyniki)
            {
                if (e.type == sf::Event::KeyPressed &&
                    e.key.code == sf::Keyboard::Escape)
                {
                    stan = StanAplikacji::Menu;
                }
            }

                       else if (stan == StanAplikacji::GameOver)
            {
                if (e.type == sf::Event::KeyPressed &&
                    e.key.code == sf::Keyboard::Enter)
                {
                    stan = StanAplikacji::Menu;
                }
            }
        }

                if (stan == StanAplikacji::Gra)
        {
            gra.aktualizuj(zegar.restart());

            if (gra.czyGameOver())
            {
                std::ofstream plik("wyniki.txt", std::ios::app);
                plik << "Wynik: " << rand() % 500 << "\n";
                plik.close();

                stan = StanAplikacji::GameOver;
            }
        }

        
        if (stan == StanAplikacji::Menu)
        {
            okno.clear(sf::Color(25, 25, 32));
            menu.rysuj(okno);
            okno.display();
        }
        else if (stan == StanAplikacji::Gra)
        {
            okno.clear(sf::Color(25, 25, 32));
            gra.rysuj(okno);
            okno.display();
        }
        else if (stan == StanAplikacji::Wyniki)
        {
            rysujWyniki(okno, wyniki);
        }
        else if (stan == StanAplikacji::GameOver)
        {
            sf::Font f;
            f.loadFromFile("arial.ttf");

            sf::Text t("GAME OVER\n\nNacisnij ENTER", f, 34);
            t.setPosition(200, 250);
            t.setFillColor(sf::Color::White);

            okno.clear(sf::Color(25, 25, 32));
            okno.draw(t);
            okno.display();
        }
    }

    return 0;
}

