#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
using namespace sf;
using namespace std;

//the cars, takes in their coordinates(x,y),speed and the angle of the car
struct Car
{
    float x,y,speed,angle;
    Car() {speed=2; angle=0;}
    void move()
    {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;    
    }
};

//the coins location x,y
struct Coin
{
  float x,y,used;
};

int main() 
{
    // START MENU!!!!!!!!!!!!!!!!
    // Create the window
    //sf::RenderWindow window(sf::VideoMode(640, 480), "Starting Screen");
    RenderWindow app(VideoMode(640, 480), "Virtual Machines");
    app.setFramerateLimit(60);
    app.clear(Color::Black);
    // Create the text
    Font mario_font;
    mario_font.loadFromFile("../SuperMario256.ttf");
    Texture t0;
    t0.loadFromFile("../start.png");
    t0.setSmooth(true);
    Sprite sStart(t0);

    Text menuText1("1 player", mario_font);
    menuText1.setPosition(175,300);
    menuText1.setCharacterSize(50);
    menuText1.setColor(Color::Yellow);

    Text menuText2("2 players", mario_font);
    menuText2.setPosition(175,350);
    menuText2.setCharacterSize(50);
    menuText2.setColor(Color::White);

    // Main loop
    bool start = false;
    int mode = 1;
    while (app.isOpen() && !start)
    {
        // Handle events
        sf::Event event;
        while (app.pollEvent(event) && !start)
        {
            if (event.type == sf::Event::Closed)
            {
                // Close the window
                app.close();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                menuText1.setColor(Color::Yellow);
                menuText2.setColor(Color::White);
                mode = 1;

            }
            else if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                menuText1.setColor(Color::White);
                menuText2.setColor(Color::Yellow);
                mode = 2;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                start = true;
            }
            app.draw(sStart);
            app.draw(menuText1);
            app.draw(menuText2);
            app.display();
        }
    }
            //END MENU!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //setting up the window and the framerate
    //RenderWindow app(VideoMode(640, 480), "Virtual Machines");
    //app.setFramerateLimit(60);

    //the textures being called 
    Texture t1, t2, t3, t4, t5;
    t1.loadFromFile("../track.png");
    t2.loadFromFile("../carkong.png");
    t3.loadFromFile("../coin.png");
    t4.loadFromFile("../luigiKart.png");
    t5.loadFromFile("../grass.png");
    t1.setSmooth(true);
    t2.setSmooth(true);
    t3.setSmooth(true);
    t4.setSmooth(true);
    t5.setSmooth(true);


    //naming the background image and the car
    Sprite sBackground(t1), sCar(t2), sCoin(t3), sCar2(t4), sGrass(t5);
    sBackground.scale(3,4);
    sCar.setOrigin(22, 22);
    sCar2.setOrigin(22, 22);

    //setting up the split screen and their names
    View view1, view2; //split
    //view1.setViewport(FloatRect(0, 0, 0.5f, 1.0f)); //split
    //view1.setSize(1000/2, 480); //split
    if (mode == 2) {
    view1.setViewport(FloatRect(0, 0, 0.5f, 1.0f)); //split
    view2.setViewport(FloatRect(0.5f, 0, 0.5f, 1.0f)); //split
    } else {
        view1.setViewport(FloatRect(0, 0, 1.0f, 1.0f)); //split
    }
        //view2.setSize(1000/2, 480); //split

    //////clock///////
    srand(time(NULL));
    Clock clock;
    Time t;
    stringstream ss;
    int s=0;
    int g=0;
    int m=0;
    bool stop1 = false;
    bool stop2 = false;
 
    //Font mario_font;
    //mario_font.loadFromFile("/home/jussi/cpp/src/SuperMario256.ttf");
 
    Text text("", mario_font);
    text.setPosition(7,0);
    text.setCharacterSize(50);
    text.setColor(Color::Yellow);
    string stringText1 = "";
    string stringText2 = "";
    //////clock///////

    /// laps ///
    stringstream ss1;
    Text laps("", mario_font);
    laps.setPosition(800,850);
    laps.setCharacterSize(100);
    laps.setColor(Color::Yellow);

    stringstream ss2;
    Text laps2("", mario_font);
    laps2.setPosition(800,850);
    laps2.setCharacterSize(100);
    laps2.setColor(Color::Yellow);
    /// laps ///

    /// you win ///
    stringstream ssW;
    Text win("", mario_font);
    win.setPosition(100,100);
    win.setCharacterSize(200);
    win.setColor(Color::Yellow);
    /// you win ///

    //number of cars
    const int N=mode;  
    Car car[N];
    
    //the cars speed and x,y coordinates
    for(int i=0;i<N;i++)
    {
        car[i].x=2760 + i*96;
        car[i].y=2336 + i*96;
        car[i].speed=7 + i;
    }

    //number of coins
    int X=14;
    Coin coin[X];

    //the coins x,y coordinates
    vector<int> coin_x = { 2170,2100,1800,1750,300,200,150,250,1500,1500,2550,2450,2350,2250 };
    vector<int> coin_y = { 1350,1300,840,800,1000,1000,2300,2300,2200,2300,3727,3727,3727,3727 };

    for(int i=0;i<X;i++)
    {
        coin[i].x=coin_x[i];
        coin[i].y=coin_y[i];
        coin[i].used = 0;
    }

    //the floats and ints for the cars speed,angle and their max speed, acceleration, decceleration and their turn speed
    ///float x=300, y=300;
    float speed = 0, angle = 0;
    float speed2 = 0, angle2 = 0;
    
    float maxSpeed=12.0;
    float maxSpeed2=12.0;

    float acc=0.2, dec=0.3;
    float turnSpeed=0.08;

    int offsetX=0, offsetY=0;
    int offsetX2=0, offsetY2=0;

    ///checkpoint and lap counters and max
    int counter=0;
    int counter2=0;

    int lapCounter=0;
    int lapCounter2=0;

    int totalLaps = 3;

    string firstTrackCompletion1 = "";
    string firstTrackCompletion2 = "";
    string secondTrackCompletion1 = "";
    string secondTrackCompletion2 = "";
    string nextLine = "\n";

    int currentTrack = 1;

    ///the main window that is opened up when you start the game///
    Event e;
    while (app.isOpen()) 
    {     
        while (app.pollEvent(e)) 
        {
            if (e.type == Event::Closed)
                app.close();
        }

	////Car 1 Movement////  
    bool Up=0, Right=0, Down=0, Left=0;
    if (Keyboard::isKeyPressed(Keyboard::W)) Up=1;
    if (Keyboard::isKeyPressed(Keyboard::D)) Right=1;
    if (Keyboard::isKeyPressed(Keyboard::S)) Down=1;
    if (Keyboard::isKeyPressed(Keyboard::A)) Left=1;

    if (Up && speed<maxSpeed)
        if (speed < 0) speed += dec;
        else speed += acc;
    
    if (Down && speed>-maxSpeed)
        if (speed > 0) speed -= dec;
        else speed -= acc;

    if (!Up && !Down)
        if (speed - dec > 0) speed -= dec;
        else if (speed + dec < 0) speed += dec;
        else speed = 0;
    
    if (Right && speed!= 0) angle += turnSpeed * speed/maxSpeed;
    if (Left && speed!= 0) angle -= turnSpeed * speed/maxSpeed;
    
    car[0].speed = speed;
    car[0].angle = angle;
	
	if (car[0].x>320) offsetX = car[0].x-320;
    if (car[0].y>240) offsetY = car[0].y-240;
    
    //bounds car 1
    if (car[0].x>3000 && car[0].speed>0) car[0].speed = -5, car[0].angle = 45; 
    else if (car[0].x>3000 && car[0].speed<0) car[0].speed = 5, car[0].angle = 225;
    if (car[0].x <= 40 && car[0].speed>0) car[0].speed = -5, car[0].angle = 225; 
    else if (car[0].x <= 40 && car[0].speed<0) car[0].speed = 5, car[0].angle = 45; 
    if (car[0].y>4000 && car[0].speed>0) car[0].speed = -5, car[0].angle = 135; 
    else if (car[0].y>4000 && car[0].speed<0) car[0].speed = 5, car[0].angle = 315;
    if (car[0].y <= 40 && car[0].speed>0) car[0].speed = -5, car[0].angle = 315; 
    else if (car[0].y <= 40 && car[0].speed<0) car[0].speed = 5, car[0].angle = 135;
    if (currentTrack == 1)
    {
    //bounds car 1 inside level
    //corners
    if (car[0].x>2200 && car[0].y<650 && car[0].speed>0) car[0].speed = -5, car[0].angle = 45;
    else if (car[0].x>2200 && car[0].y<650 && car[0].speed<0) car[0].speed = 0, car[0].angle = 225;
    if (car[0].y>3450 && car[0].x<1450 && car[0].speed>0) car[0].speed = 0, car[0].angle = 135; 
    else if (car[0].y>3450 && car[0].x<1450 && car[0].speed<0) car[0].speed = 5, car[0].angle = 315;

    //long thicc square
    //up and right
    if (car[0].x>480 && car[0].x<830 && car[0].y>620 && car[0].y<2390 && car[0].speed>0) car[0].speed = 0, car[0].angle = 135;
    else if (car[0].x>480 && car[0].x<830 && car[0].y>620 && car[0].y<2390 && car[0].speed<0) car[0].speed = 5, car[0].angle = 315;
    //down and left
    if (car[0].x>460 && car[0].x<810 && car[0].y>640 && car[0].y<2410 && car[0].speed>0) car[0].speed = -5, car[0].angle = 45;
    else if (car[0].x>460 && car[0].x<810 && car[0].y>640 && car[0].y<2410 && car[0].speed<0) car[0].speed = 0, car[0].angle = 225;

    //thicc horizontal square
    //up and right
    if (car[0].x>800 && car[0].x<2100 && car[0].y>1450 && car[0].y<2000 && car[0].speed>0) car[0].speed = 0, car[0].angle = 135;
    else if (car[0].x>800 && car[0].x<2100 && car[0].y>1450 && car[0].y<2000 && car[0].speed<0) car[0].speed = 5, car[0].angle = 315;
    //down and left
    if (car[0].x>800 && car[0].x<2080 && car[0].y>1470 && car[0].y<2050 && car[0].speed>0) car[0].speed = -5, car[0].angle = 45;
    else if (car[0].x>800 && car[0].x<2080 && car[0].y>1470 && car[0].y<2050 && car[0].speed<0) car[0].speed = 0, car[0].angle = 225;

    //long slim square
    //up and right
    if (car[0].x>2220 && car[0].x<2500 && car[0].y>1630 && car[0].y<3200 && car[0].speed>0) car[0].speed = 0, car[0].angle = 135;
    else if (car[0].x>2220 && car[0].x<2500 && car[0].y>1630 && car[0].y<3200 && car[0].speed<0) car[0].speed = 5, car[0].angle = 315;
    //down and left
    if (car[0].x>2200 && car[0].x<2480 && car[0].y>1650 && car[0].y<3250 && car[0].speed>0) car[0].speed = -5, car[0].angle = 45;
    else if (car[0].x>2200 && car[0].x<2480 && car[0].y>1650 && car[0].y<3250 && car[0].speed<0) car[0].speed = 0, car[0].angle = 225;

    //up and right
    if (car[0].x>2020 && car[0].x<2200 && car[0].y>1630 && car[0].y<2000 && car[0].speed>0) car[0].speed = 0, car[0].angle = 135;
    else if (car[0].x>2020 && car[0].x<2200 && car[0].y>1630 && car[0].y<2000 && car[0].speed<0) car[0].speed = 5, car[0].angle = 315;
    //down and left
    if (car[0].x>2000 && car[0].x<2180 && car[0].y>1650 && car[0].y<2050 && car[0].speed>0) car[0].speed = -5, car[0].angle = 45;
    else if (car[0].x>2000 && car[0].x<2180 && car[0].y>1650 && car[0].y<2050 && car[0].speed<0) car[0].speed = 0, car[0].angle = 225;
    
    //small square
    //up and right
    if (car[0].x>380 && car[0].x<530 && car[0].y>2190 && car[0].y<2640 && car[0].speed>0) car[0].speed = 0, car[0].angle = 135;
    else if (car[0].x>380 && car[0].x<530 && car[0].y>2190 && car[0].y<2640 && car[0].speed<0) car[0].speed = 5, car[0].angle = 315;
    //down and left
    if (car[0].x>360 && car[0].x<510 && car[0].y>2160 && car[0].y<2660 && car[0].speed>0) car[0].speed = -5, car[0].angle = 45;
    else if (car[0].x>360 && car[0].x<510 && car[0].y>2160 && car[0].y<2660 && car[0].speed<0) car[0].speed = 0, car[0].angle = 225;
    }
    //coins car 1
    for (int i = 0; i < X; i++)
    {
      if (coin[i].x <= car[0].x && car[0].x <= coin[i].x + 30 && coin[i].y <= car[0].y && car[0].y <= coin[i].y + 30) 
      {
        maxSpeed += 0.2;
        // Move all the elements after the coin one position to the left
        for (int n = i; n < X; n++)
        {
          coin[n] = coin[n+1];
        }
        X -= 1;
      };
    };
    
    
    ///checkpoints car 1///
    if (car[0].y <= 2230 && counter == 0) // test
    {
        counter += 1; 
    }// test
    else if (car[0].x <= 2230 && counter == 1) // test
    {
        counter += 1; 
    }// test
    else if (car[0].y >= 2230 && counter == 2) // test
    {
        counter += 1; 
    }// test
    else if (car[0].x >= 2230 && counter == 3) // test
    {
        counter += 1; 
    }// test
    else if (car[0].y <= 2230 && counter == 4 && lapCounter != 3) // test
    {
        counter = 0;
        lapCounter += 1;
    }// test
     ///checkpoints car 1///
    if (currentTrack == 2) 
    {
    
    //up and right
    if (car[0].x>1150 && car[0].x<2000 && car[0].y>1100 && car[0].y<3230 && car[0].speed>0) car[0].speed = 0, car[0].angle = 135;
    else if (car[0].x>1150 && car[0].x<2000 && car[0].y>1100 && car[0].y<3230 && car[0].speed<0) car[0].speed = 5, car[0].angle = 315;
    //down and left
    if (car[0].x>1130 && car[0].x<1980 && car[0].y>1080 && car[0].y<3250 && car[0].speed>0) car[0].speed = -5, car[0].angle = 45;
    else if (car[0].x>1130 && car[0].x<1980 && car[0].y>1080 && car[0].y<3250 && car[0].speed<0) car[0].speed = 0, car[0].angle = 225;
    
    //up and right
    if (car[0].x>950 && car[0].x<2200 && car[0].y>950 && car[0].y<1700 && car[0].speed>0) car[0].speed = 0, car[0].angle = 135;
    else if (car[0].x>950 && car[0].x<2200 && car[0].y>950 && car[0].y<1700 && car[0].speed<0) car[0].speed = 5, car[0].angle = 315;
    //down and left
    if (car[0].x>900 && car[0].x<2180 && car[0].y>1000 && car[0].y<1750 && car[0].speed>0) car[0].speed = -5, car[0].angle = 45;
    else if (car[0].x>900 && car[0].x<2180 && car[0].y>1000 && car[0].y<1750 && car[0].speed<0) car[0].speed = 0, car[0].angle = 225;
    }


	////Car 2 Movement////
	bool Up2=0, Right2=0, Down2=0, Left2=0;
    if (Keyboard::isKeyPressed(Keyboard::Up)) Up2=1;
    if (Keyboard::isKeyPressed(Keyboard::Right)) Right2=1;
    if (Keyboard::isKeyPressed(Keyboard::Down)) Down2=1;
    if (Keyboard::isKeyPressed(Keyboard::Left)) Left2=1;

    if (Up2 && speed2<maxSpeed2)
        if (speed2 < 0) speed2 += dec;
        else speed2 += acc;
    
    if (Down2 && speed2>-maxSpeed2)
        if (speed2 > 0) speed2 -= dec;
        else speed2 -= acc;

    if (!Up2 && !Down2)
        if (speed2 - dec > 0) speed2 -= dec;
        else if (speed2 + dec < 0) speed2 += dec;
        else speed2 = 0;
    
    if (Right2 && speed2!= 0) angle2 += turnSpeed * speed2/maxSpeed2;
    if (Left2 && speed2!= 0) angle2 -= turnSpeed * speed2/maxSpeed2;
    
    car[1].speed = speed2;
    car[1].angle = angle2;

    if (car[1].x>320) offsetX2 = car[1].x-320;
    if (car[1].y>240) offsetY2 = car[1].y-240;

    

    //bounds car 2
    if (car[1].x>3000 && car[1].speed>0) car[1].speed = -5, car[1].angle = 45; 
    else if (car[1].x>3000 && car[1].speed<0) car[1].speed = 5, car[1].angle = 225;
    if (car[1].x <= 40 && car[1].speed>0) car[1].speed = -5, car[1].angle = 225; 
    else if (car[1].x <= 40 && car[1].speed<0) car[1].speed = 5, car[1].angle = 45; 
    if (car[1].y>4000 && car[1].speed>0) car[1].speed = -5, car[1].angle = 135; 
    else if (car[1].y>4000 && car[1].speed<0) car[1].speed = 5, car[1].angle = 315; 
    if (car[1].y <= 40 && car[1].speed>0) car[1].speed = -5, car[1].angle = 315;
    else if (car[1].y <= 40 && car[1].speed<0) car[1].speed = 5, car[1].angle = 135;
    if (currentTrack == 1)
    {
    //bounds car 2 inside level
    //corners
    if (car[1].x>2200 && car[1].y<650 && car[1].speed>0) car[1].speed = -5, car[1].angle = 45;
    else if (car[1].x>2200 && car[1].y<650 && car[1].speed<0) car[1].speed = 0, car[1].angle = 225;
    if (car[1].y>3450 && car[1].x<1450 && car[1].speed>0) car[1].speed = 0, car[1].angle = 135; 
    else if (car[1].y>3450 && car[1].x<1450 && car[1].speed<0) car[1].speed = 5, car[1].angle = 315;

    //long thicc square
    //up and right
    if (car[1].x>480 && car[1].x<830 && car[1].y>620 && car[1].y<2390 && car[1].speed>0) car[1].speed = 0, car[1].angle = 135;
    else if (car[1].x>480 && car[1].x<830 && car[1].y>620 && car[1].y<2390 && car[1].speed<0) car[1].speed = 5, car[1].angle = 315;
    //down and left
    if (car[1].x>460 && car[1].x<810 && car[1].y>640 && car[1].y<2410 && car[1].speed>0) car[1].speed = -5, car[1].angle = 45;
    else if (car[1].x>460 && car[1].x<810 && car[1].y>640 && car[1].y<2410 && car[1].speed<0) car[1].speed = 0, car[1].angle = 225;

    //thicc horizontal square
    //up and right
    if (car[1].x>800 && car[1].x<2100 && car[1].y>1450 && car[1].y<2000 && car[1].speed>0) car[1].speed = 0, car[1].angle = 135;
    else if (car[1].x>800 && car[1].x<2100 && car[1].y>1450 && car[1].y<2000 && car[1].speed<0) car[1].speed = 5, car[1].angle = 315;
    //down and left
    if (car[1].x>800 && car[1].x<2080 && car[1].y>1470 && car[1].y<2050 && car[1].speed>0) car[1].speed = -5, car[1].angle = 45;
    else if (car[1].x>800 && car[1].x<2080 && car[1].y>1470 && car[1].y<2050 && car[1].speed<0) car[1].speed = 0, car[1].angle = 225;

    //long slim square
    //up and right
    if (car[1].x>2220 && car[1].x<2500 && car[1].y>1630 && car[1].y<3200 && car[1].speed>0) car[1].speed = 0, car[1].angle = 135;
    else if (car[1].x>2220 && car[1].x<2500 && car[1].y>1630 && car[1].y<3200 && car[1].speed<0) car[1].speed = 5, car[1].angle = 315;
    //down and left
    if (car[1].x>2200 && car[1].x<2480 && car[1].y>1650 && car[1].y<3250 && car[1].speed>0) car[1].speed = -5, car[1].angle = 45;
    else if (car[1].x>2200 && car[1].x<2480 && car[1].y>1650 && car[1].y<3250 && car[1].speed<0) car[1].speed = 0, car[1].angle = 225;

    //up and right
    if (car[1].x>2020 && car[1].x<2200 && car[1].y>1630 && car[1].y<2000 && car[1].speed>0) car[1].speed = 0, car[1].angle = 135;
    else if (car[1].x>2020 && car[1].x<2200 && car[1].y>1630 && car[1].y<2000 && car[1].speed<0) car[1].speed = 5, car[1].angle = 315;
    //down and left
    if (car[1].x>2000 && car[1].x<2180 && car[1].y>1650 && car[1].y<2050 && car[1].speed>0) car[1].speed = -5, car[1].angle = 45;
    else if (car[1].x>2000 && car[1].x<2180 && car[1].y>1650 && car[1].y<2050 && car[1].speed<0) car[1].speed = 0, car[1].angle = 225;
    
    //small square
    //up and right
    if (car[1].x>380 && car[1].x<530 && car[1].y>2190 && car[1].y<2640 && car[1].speed>0) car[1].speed = 0, car[1].angle = 135;
    else if (car[1].x>380 && car[1].x<530 && car[1].y>2190 && car[1].y<2640 && car[1].speed<0) car[1].speed = 5, car[1].angle = 315;
    //down and left
    if (car[1].x>360 && car[1].x<510 && car[1].y>2160 && car[1].y<2660 && car[1].speed>0) car[1].speed = -5, car[1].angle = 45;
    else if (car[1].x>360 && car[1].x<510 && car[1].y>2160 && car[1].y<2660 && car[1].speed<0) car[1].speed = 0, car[1].angle = 225;
    }
    for (int i = 0; i < X; i++)
    {
      if (coin[i].x <= car[1].x && car[1].x <= coin[i].x + 30 && coin[i].y <= car[1].y && car[1].y <= coin[i].y + 30) 
      {
        maxSpeed2 += 0.2;
        // Move all the elements after the coin one position to the left
        for (int n = i; n < X; n++)
        {
          coin[n] = coin[n+1];
        }
        X -= 1;
      };
    };

    ///checkpoints car 2///
    if (car[1].y <= 2230 && counter2 == 0) // test
    {
        counter2 += 1; 
    }// test
    else if (car[1].x <= 2230 && counter2 == 1) // test
    {
        counter2 += 1; 
    }// test
    else if (car[1].y >= 2230 && counter2 == 2) // test
    {
        counter2 += 1; 
    }// test
    else if (car[1].x >= 2230 && counter2 == 3) // test
    {
        counter2 += 1; 
    }// test
    else if (car[1].y <= 2230 && counter2 == 4 && lapCounter2 != 3) // test
    {
        counter2 = 0;
        lapCounter2 += 1;
        //cout << "counter: " << counter2 << "\n";
    }// test
     ///checkpoints car 2///

    //track 2 bounds car 2
    if (currentTrack == 2) 
    {
    
    //up and right
    if (car[1].x>1150 && car[1].x<2000 && car[1].y>1100 && car[1].y<3230 && car[1].speed>0) car[1].speed = 0, car[1].angle = 135;
    else if (car[1].x>1150 && car[1].x<2000 && car[1].y>1100 && car[1].y<3230 && car[1].speed<0) car[1].speed = 5, car[1].angle = 315;
    //down and left
    if (car[1].x>1130 && car[1].x<1980 && car[1].y>1080 && car[1].y<3250 && car[1].speed>0) car[1].speed = -5, car[1].angle = 45;
    else if (car[1].x>1130 && car[1].x<1980 && car[1].y>1080 && car[1].y<3250 && car[1].speed<0) car[1].speed = 0, car[1].angle = 225;
    
    //up and right
    if (car[1].x>950 && car[1].x<2200 && car[1].y>950 && car[1].y<1700 && car[1].speed>0) car[1].speed = 0, car[1].angle = 135;
    else if (car[1].x>950 && car[1].x<2200 && car[1].y>950 && car[1].y<1700 && car[1].speed<0) car[1].speed = 5, car[1].angle = 315;
    //down and left
    if (car[1].x>900 && car[1].x<2180 && car[1].y>1000 && car[1].y<1750 && car[1].speed>0) car[1].speed = -5, car[1].angle = 45;
    else if (car[1].x>900 && car[1].x<2180 && car[1].y>1000 && car[1].y<1750 && car[1].speed<0) car[1].speed = 0, car[1].angle = 225;
    }

    

    for(int i=0;i<N;i++)
    {
        car[i].move();
        //cout << car[0].x << "x" << car[0].y << "y" << "\n";
    } 
	
    ////drawing the background and cars///////
    app.clear(Color::Green);
    
    //view #1
    app.setView(view1); //split

    app.draw(sGrass);

    sBackground.setPosition(-offsetX,-offsetY);
    app.draw(sBackground);

    for(int i=0;i<X;i++) //split
    { //split
        sCoin.setPosition(coin[i].x-offsetX, coin[i].y-offsetY); //split
        app.draw(sCoin); //split
    } //split

    sCar.setPosition(car[0].x-offsetX, car[0].y-offsetY);
    sCar.setRotation(car[0].angle*180/3.141592);
    app.draw(sCar);

    sCar2.setPosition(car[1].x-offsetX, car[1].y-offsetY);
    sCar2.setRotation(car[1].angle*180/3.141592);
    app.draw(sCar2);

    //////clock///////
    if (!stop1)
    {
    ss.str("");
    t=clock.getElapsedTime();
    s=t.asSeconds();
    g=s/3600;
    m=(s-(g*3600))/60;
    s=s-(g*3600+m*60);
    
    if(g<10)
    {
        ss<<"0"<<g;
    }
    else
    {
        ss<<g;
    }
    if(m<10)
    {
        ss<<":"<<"0"<<m;
    }
    else
    {
        ss<<":"<<m;
    }
    if(s<10)
    {
        ss<<":"<<"0"<<s;
    }
    else
    {
        ss<<":"<<s;
    }
 
        //ss<<g<<":"<<m<<":"<<s;
 
    text.setString(ss.str());
    stringText1 = ss.str();
 
    app.draw(text);
    }
    //////clock///////


    ///lap counter/////
    ss1.str("");
    ss1<<lapCounter + 1<<"/3";
    laps.setString(ss1.str());
    app.draw(laps);
    ///lap counter/////

    ///win/////
    ssW.str("");
    if (lapCounter == totalLaps) {
    //ssW<<"win"<< "\n" << m << ":" <<s;
    const string lastString = stringText1;
    ssW<<"win"<< "\n" << lastString;
    win.setString(ssW.str());
    app.draw(win);
    if (currentTrack == 1) {
        firstTrackCompletion1 = lastString;
      } else if (currentTrack == 2) {
        secondTrackCompletion1 = lastString;
      }
    stop1 = true;
    }
    ///win/////

    //view #2
    if (mode == 2) {
        app.setView(view2); //split
    
    app.draw(sGrass);
    
    sBackground.setPosition(-offsetX2,-offsetY2); //split
    app.draw(sBackground); //split

    for(int i=0;i<X;i++) //split
    { //split
        sCoin.setPosition(coin[i].x-offsetX2, coin[i].y-offsetY2); //split
        app.draw(sCoin); //split
    }
    

    sCar.setPosition(car[0].x-offsetX2, car[0].y-offsetY2);
    sCar.setRotation(car[0].angle*180/3.141592);
    app.draw(sCar);

    sCar2.setPosition(car[1].x-offsetX2, car[1].y-offsetY2);
    sCar2.setRotation(car[1].angle*180/3.141592);
    app.draw(sCar2);

    //coins car 2
    if (sCar2.getGlobalBounds().intersects(sCoin.getGlobalBounds()))
    {
        car[1].speed = 0;
    };

    //////clock///////
    
    if (!stop2)
    {
    ss.str("");
    t=clock.getElapsedTime();
    s=t.asSeconds();
    g=s/3600;
    m=(s-(g*3600))/60;
    s=s-(g*3600+m*60);
    
    if(g<10)
    {
        ss<<"0"<<g;
    }
    else
    {
        ss<<g;
    }
    if(m<10)
    {
        ss<<":"<<"0"<<m;
    }
    else
    {
        ss<<":"<<m;
    }
    if(s<10)
    {
        ss<<":"<<"0"<<s;
    }
    else
    {
        ss<<":"<<s;
    }
 
        //ss<<g<<":"<<m<<":"<<s;
 
    text.setString(ss.str());
    stringText2 = ss.str();
 
    app.draw(text);
    }
    //////clock///////

    ///lap counter/////
    ss2.str("");
    ss2<<lapCounter2 + 1<<"/3";
    laps.setString(ss2.str());
    app.draw(laps);
    ///lap counter/////

    ///win/////
    ssW.str("");
    if (lapCounter2 == totalLaps) {
      const string lastString2 = stringText2;
      ssW<<"win"<< "\n" << lastString2;
      //ssW<<"win"<< "\n" << m << ":" <<s;
    
      win.setString(ssW.str());
      app.draw(win);
      if (currentTrack == 1) {
        firstTrackCompletion2 = lastString2;
      } else if (currentTrack == 2) {
        secondTrackCompletion2 = lastString2;
      }

      stop2 = true;
    }

    }
    
    ///win/////
    //change track
    if ((stop1 && (mode == 1)) || (stop1 && stop2)) {
        if (currentTrack == 1) {
            stop1 = false;
            stop2 = false;
            t1.loadFromFile("../track2.png");
            counter=0;
            counter2=0;
            maxSpeed = 12.0;
            maxSpeed2 = 12.0;

            for(int i=0;i<N;i++)
            {       
                car[i].x=2250 + i*100;
                car[i].y=2500;
                car[i].speed=0;
                //car[i].angle=0;
            };

            X = 14;

            coin_x = { 2850,2750,1700,1700,410,310,780,780,680,680,1350,1450,1550,1650 };
            coin_y = { 1350,1350,260,360,1000,1000,2200,2300,2200,2300,3820,3820,3820,3820 };

            for(int i=0;i<X;i++)
            {
                coin[i].x=coin_x[i];
                coin[i].y=coin_y[i];
                coin[i].used = 0;
            };

            lapCounter=0;
            lapCounter2=0;
            clock.restart();
            s=0;
            g=0;
            m=0;
            currentTrack = 2;


        } else {
            if (currentTrack == 2) {
                app.setView(app.getDefaultView());
                app.clear(Color::Black);
                app.draw(sStart);

                Text winText1("Player 1 times: " + nextLine +  firstTrackCompletion1 + nextLine + secondTrackCompletion1, mario_font);
                winText1.setPosition(75,100);
                winText1.setCharacterSize(50);
                winText1.setColor(Color::Yellow);

                app.draw(winText1);
                if (mode == 2) {
                    Text winText2("Player 2 times:" + nextLine + firstTrackCompletion2 + nextLine + secondTrackCompletion2, mario_font);
                    winText2.setPosition(75,325);
                    winText2.setCharacterSize(50);
                    winText2.setColor(Color::Yellow);

                    app.draw(winText2);
                }
                
                
            }
        }
    }

    app.display();
    }
    

    return 0;
}

