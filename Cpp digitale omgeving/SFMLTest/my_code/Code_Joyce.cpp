#include <SFML/Graphics.hpp>
#include <cmath>

//Om dit progamma te starten:
/*
g++ Code_Joyce.cpp -o Code_Joyce.exe -lsfml-graphics -lsfml-window -lsfml-system
    .\Code_Joyce.cpp.exe
*/

float hoek = 0.f;  //De hoek van de auto instellen, zodat hij kan draaien
float hoekVerandering = 0.1f;  //De hoekverandering van de auto instellen, zodat hij kan draaien
float snelheid = 0.f; //De snelheid instellen
float afstand = 0.f; //De afstand instellen
const float maxSnelheid = 800.f; //De maximale snelheid instellen
const float minSnelheid = 0.f; //De minimale snelheid instellen
int main() 
{ sf::RenderWindow raampje(
        sf::VideoMode(1800, 1200),            //Het venster maken (raampje), en de grootte instellen
        "raampje"
    );
sf::RectangleShape car({50.f,100.f});  //Auto maken, en de grootte instellen
car.setFillColor(sf::Color::Black);    //De kleur van de auto instellen
car.setPosition(400.f, 450.f);     //De positie van de auto instellen
car.setOrigin(25.f, 50.f);        //De oorsprong van de auto instellen

sf::Clock klok;  //Klok maken, zodat de tijd kan worden gemeten

while (raampje.isOpen())                //Zolang het venster open is, blijft dit programma draaien
{
    float tijd = klok.restart().asSeconds();  //De tijd meten, en de klok opnieuw starten
    
    sf::Event event;
    while (raampje.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            raampje.close();
    }

    float hoekInGraden = car.getRotation();
    float hoekInRadialen = hoekInGraden * (3.14159 / 180.f);  //De hoek van graden naar radialen omzetten

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        car.rotate(hoekVerandering);       //De auto draaien naar rechts
        hoek = car.getRotation();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        car.rotate(-hoekVerandering);   //De auto draaien naar links
        hoek = car.getRotation();
    }
   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        snelheid = snelheid + 200.f * tijd;  //De snelheid van de auto verhogen met 0,1 per seconde
    }
    else {
        snelheid = snelheid - 800.f * tijd;  //De snelheid van de auto verlagen met 0,1 per seconde
    }
    afstand = snelheid * tijd;  //De afstand berekenen die de auto aflegt in de tijd  
    float dx = afstand * std::sin(hoekInRadialen);  //De afstand in de x-richting berekenen
    float dy = afstand * std::cos(hoekInRadialen);  //De afstand in de y-richting berekenen
    car.move(dx, -dy);  //De auto verplaatsen in de x- en y-richting
    
    if (snelheid >= maxSnelheid)
    {
        snelheid = maxSnelheid;  //De snelheid van de auto instellen op de maximale snelheid
    }
    if (snelheid <= minSnelheid)
    {
        snelheid = minSnelheid;  //De snelheid van de auto instellen op de minimale snelheid
    }
    raampje.clear(sf::Color::White);       //Het venster leegmaken, en de kleur instellen
    raampje.draw(car);                     //De auto tekenen
    raampje.display();                      //Het venster weergeven
}
return 0;
}
