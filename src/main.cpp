#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
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
    //setting up the window and the framerate
    RenderWindow app(VideoMode(640, 480), "Virtual Machines");
    app.setFramerateLimit(60);

    //the textures being called 
    Texture t1, t2, t3, t4;
    t1.loadFromFile("../track.png");
    t2.loadFromFile("../carkong.png");
    t3.loadFromFile("../coin.png");
    t4.loadFromFile("../carkong.png");
    t1.setSmooth(true);
    t2.setSmooth(true);
    t3.setSmooth(true);
    t4.setSmooth(true);

    //naming the background image and the car
    Sprite sBackground(t1), sCar(t2), sCoin(t3), sCar2(t4);
    sBackground.scale(3,4);
    sCar.setOrigin(22, 22);
    sCar2.setOrigin(22, 22);

    //setting up the split screen and their names
    View view1, view2; //split
    view1.setViewport(FloatRect(0, 0, 0.5f, 1.0f)); //split
    //view1.setSize(1000/2, 480); //split
    view2.setViewport(FloatRect(0.5f, 0, 0.5f, 1.0f)); //split
    //view2.setSize(1000/2, 480); //split

    //////clock///////
    srand(time(NULL));
    Clock clock;
    Time t;
    stringstream ss;
    int s=0;
    int g=0;
    int m=0;
 
    Font mario_font;
    mario_font.loadFromFile("../SuperMario256.ttf");
 
    Text text("", mario_font);
    text.setPosition(7,0);
    text.setCharacterSize(50);
    text.setColor(Color::Yellow);
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
    const int N=2;  
    Car car[N];
    
    //the cars speed and x,y coordinates
    for(int i=0;i<N;i++)
    {
        car[i].x=2760 + i*96;
        car[i].y=2336 + i*96;
        car[i].speed = 7 + i;
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

    int lapCounter=1;
    int lapCounter2=1;

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

    //coins car 1
    //if(find(coin_x))
    for (int i = 0; i < X; i++)
    {
      if (coin[i].x - 15 <= car[0].x && car[0].x <= coin[i].x + 15 && coin[i].y - 15 <= car[0].y && car[0].y <= coin[i].y + 15) 
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
        counter = 1;
        lapCounter += 1;
    }// test
     ///checkpoints car 1///

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

    for (int i = 0; i < X; i++)
    {
      if (coin[i].x - 15 <= car[1].x && car[1].x <= coin[i].x + 15 && coin[i].y - 15 <= car[1].y && car[1].y <= coin[i].y + 15) 
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
        counter2 = 1;
        lapCounter2 += 1;
        //cout << "counter: " << counter2 << "\n";
    }// test
     ///checkpoints car 2///

    for(int i=0;i<N;i++)
    {
        car[i].move();
    } 
	
    ////drawing the background and cars///////
    app.clear(Color::Green);
    
    //view #1
    app.setView(view1); //split

    sBackground.setPosition(-offsetX,-offsetY);
    app.draw(sBackground);

    for(int i=0;i<X;i++) //split
    { //split
        sCoin.setPosition(coin[i].x-offsetX, coin[i].y-offsetY); //split
        app.draw(sCoin); //split
    } //split

    Color colors[10] = {Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White};

    for(int i=0;i<N;i++) //split
    { //split
        sCar.setPosition(car[i].x-offsetX, car[i].y-offsetY); //split
        sCar.setRotation(car[i].angle*180/3.141592); //split
        sCar.setColor(colors[i]); //split
        app.draw(sCar); //split
    } //split

    ///////cout << "x" << car[0].x << "y" << car[0].y << "\n";

    //////clock///////
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
 
    app.draw(text);
    //////clock///////


    ///lap counter/////
    ss1.str("");
    ss1<<lapCounter<<"/3";
    laps.setString(ss1.str());
    app.draw(laps);
    ///lap counter/////

    ///win/////
    ssW.str("");
    if (lapCounter == 3) ssW<<"win"<< "\n" << m << ":" <<s;
    win.setString(ssW.str());
    app.draw(win);
    ///win/////

    //view #2
    app.setView(view2); //split
    sBackground.setPosition(-offsetX2,-offsetY2); //split
    app.draw(sBackground); //split

    for(int i=0;i<X;i++) //split
    { //split
        sCoin.setPosition(coin[i].x-offsetX2, coin[i].y-offsetY2); //split
        app.draw(sCoin); //split
    }

    for(int i=0;i<N;i++)
    {
        sCar2.setPosition(car[i].x-offsetX2, car[i].y-offsetY2);
        sCar2.setRotation(car[i].angle*180/3.141592);
        sCar2.setColor(colors[i]);
        app.draw(sCar2);
    }

    //coins car 2
    if (sCar2.getGlobalBounds().intersects(sCoin.getGlobalBounds())) 
    {
      car[1].speed = 0;
    };

    //////clock///////
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
 
    app.draw(text);
    //////clock///////

    ///lap counter/////
    ss2.str("");
    ss2<<lapCounter2<<"/3";
    laps.setString(ss2.str());
    app.draw(laps);
    ///lap counter/////

    ///win/////
    ssW.str("");
    if (lapCounter2 == 3) ssW<<"win"<< "\n" << m << ":" <<s;
    win.setString(ssW.str());
    app.draw(win);
    ///win/////

    app.display();
    }

    return 0;
}
