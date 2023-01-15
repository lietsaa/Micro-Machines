#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "car.cpp"
#include "coin.cpp"
#include "tile.cpp"
#include "map.cpp"
using namespace sf;
using namespace std;

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

    Text menuText3("", mario_font);
    menuText3.setPosition(175,400);
    menuText3.setCharacterSize(50);
    menuText3.setColor(Color::White);
    // Main loop
    bool playerCountSelected = false;
    bool start = false;
    int mode = 1;
    int menuIndex = 0;
    int maxMenuIndex = 1;
    bool spacePressed = false;
    string filePath;
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
                if (menuIndex > 0) {
                    menuIndex--;
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (menuIndex < maxMenuIndex) {
                    menuIndex++;
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Space) && !spacePressed)
            {
                spacePressed = true;
                if (playerCountSelected) {
                switch(menuIndex) {
                    case 0:
                        filePath = "../input.txt";
                        break;
                    case 1:
                        filePath = "../input2.txt";
                        break;
                    case 2:
                        filePath = "../input3.txt";
                    default:
                        break;
                }
                    start = true;
                } else {
                    menuText1.setString("Track 1");
                    menuText2.setString("Track 2");
                    menuText3.setString("Track 3");
                    playerCountSelected = true;
                    mode = menuIndex + 1;
                    maxMenuIndex = 2;
                    menuIndex = 0;
                }
            } else {
                spacePressed = false;
            }
            menuText1.setColor(Color::White);
            menuText2.setColor(Color::White);
            menuText3.setColor(Color::White);
            switch(menuIndex) {
                case 0:
                    menuText1.setColor(Color::Yellow);
                    break;
                case 1:
                    menuText2.setColor(Color::Yellow);
                    break;
                case 2:
                    menuText3.setColor(Color::Yellow);
                default:
                    break;
            }

            app.draw(sStart);
            app.draw(menuText1);
            app.draw(menuText2);
            app.draw(menuText3);
            app.display();
        }
    }
            //END MENU!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //setting up the window and the framerate
    //RenderWindow app(VideoMode(640, 480), "Virtual Machines");
    //app.setFramerateLimit(60);
    Map map;
    //map.MapFunction(fileText);
    //the textures being called 
    Texture t1, t2, t3, t4, t5;
    //t1.loadFromFile("../track.png");
    t1.loadFromImage(map.MapFunction(filePath));
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
    sBackground.scale(3,3);
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

    /// checkpoints ///
    Text checkpoints("", mario_font);
    checkpoints.setPosition(50,850);
    checkpoints.setCharacterSize(100);
    checkpoints.setColor(Color::Yellow);

    Text checkpoints2("", mario_font);
    checkpoints2.setPosition(50,850);
    checkpoints2.setCharacterSize(100);
    checkpoints2.setColor(Color::Yellow);
    ///checkpoints///

    /// you win ///
    stringstream ssW;
    Text win("", mario_font);
    win.setPosition(100,100);
    win.setCharacterSize(200);
    win.setColor(Color::Yellow);
    /// you win ///

    Tiles tiles;
    tiles.tiles(filePath);

    //number of cars
    const int N=mode;  
    Car car[N];

    vector<int> spawn_x = tiles.seven;
    vector<int> spawn_y = tiles.seven_y;
    
    //the cars speed and x,y coordinates
    for(int i=0;i<N;i++)
    {
        car[i].x= spawn_x[i] + 62.5;
        car[i].y= spawn_y[i] + 62.5;
        car[i].speed=7 + i;
    }

    //number of coins
    int X= tiles.five.size();
    Coin coin[X];

    //the coins x,y coordinates
    vector<int> coin_x = tiles.five;
    vector<int> coin_y = tiles.five_y;

    for(int i=0;i<X;i++)
    {
        coin[i].x=coin_x[i] + 62.5;
        coin[i].y=coin_y[i] + 62.5;
        coin[i].used = 0;
    }

    //checkpoints
    vector<int> checkpoints_x = tiles.six;
    vector<int> checkpoints_y = tiles.six_y;
    int cpSize = checkpoints_x.size();
    vector<bool> cpCleared1(cpSize, false);
    vector<bool> cpCleared2(cpSize, false);

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
    
    //checkpoints car 1
    for (int i = 0; i<cpSize; i++)
    {
      if (checkpoints_x[i] <= car[0].x && car[0].x <= checkpoints_x[i] + 125 && checkpoints_y[i] <= car[0].y && car[0].y <= checkpoints_y[i] + 125)
      {
        if (!cpCleared1[i]) {
            counter++;
            cpCleared1[i] = true;
        }
      }
      
    };

    for (int i = 0; i<2; i++)
    {
      if (spawn_x[i] <= car[0].x && car[0].x <= spawn_x[i] + 125 && spawn_y[i] <= car[0].y && car[0].y <= spawn_y[i] + 125)
      {
        if (counter == 4 && lapCounter != 3) {
            counter = 0;
            lapCounter++;
            for (int i = 0; i<cpSize; i++)
            {
                cpCleared1[i] = false;
            }
        }
      }
    };
    /*
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
    */


    //the gravel x y coordinates
    vector<int> gravel_x = tiles.zero;
    vector<int> gravel_y = tiles.zero_y;

    int Z = gravel_x.size();

    for (int i = 0; i<Z; i++)
    {
      if (gravel_x[i] <= car[0].x && car[0].x <= gravel_x[i] + 125 && gravel_y[i] <= car[0].y && car[0].y <= gravel_y[i] + 125) 
      {
        car[0].speed = car[0].speed*0.5;
        
      }
    };

    //the mud x y coordinates
    vector<int> mud_x = tiles.two;
    vector<int> mud_y = tiles.two_y;
    
    int R = mud_x.size();

    for (int i = 0; i<R; i++)
    {
      if (mud_x[i] <= car[0].x && car[0].x <= mud_x[i] + 125 && mud_y[i] <= car[0].y && car[0].y <= mud_y[i] + 125) 
      {
        car[0].speed = car[0].speed*0.2;
        
      }
    };

    //the walls x y coordinates
    vector<int> walls_x = tiles.x;
    vector<int> walls_y = tiles.x_y;
    
    int L = walls_x.size();
    int wall = 0;

    for (int i = 0; i<L; i++)
    {
      if (walls_x[i] <= car[0].x + sin(car[0].angle) * car[0].speed && car[0].x + sin(car[0].angle) * car[0].speed <= walls_x[i] + 125 && walls_y[i] <= car[0].y - cos(car[0].angle) * car[0].speed && car[0].y - cos(car[0].angle) * car[0].speed <= walls_y[i] + 125)
      {
        wall = 1;
      }
      
    };


    //the speed x y coordinates
    vector<int> speed_x = tiles.three;
    vector<int> speed_y = tiles.three_y;
    
    int S = speed_x.size();

    for (int i = 0; i<S; i++)
    {
      if (speed_x[i] <= car[0].x && car[0].x <= speed_x[i] + 125 && speed_y[i] <= car[0].y && car[0].y <= speed_y[i] + 125) 
      {
        car[0].speed = car[0].speed*2;
        
      }
    };

    if (wall == 0) car[0].move();

    
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

    //checkpoints car 2
    for (int i = 0; i<cpSize; i++)
    {
      if (checkpoints_x[i] <= car[1].x && car[1].x <= checkpoints_x[i] + 125 && checkpoints_y[i] <= car[1].y && car[1].y <= checkpoints_y[i] + 125)
      {
        if (!cpCleared2[i]) {
            counter2++;
            cpCleared2[i] = true;
        }
      }
      
    };

    for (int i = 0; i<2; i++)
    {
      if (spawn_x[i] <= car[1].x && car[1].x <= spawn_x[i] + 125 && spawn_y[i] <= car[1].y && car[1].y <= spawn_y[i] + 125)
      {
        if (counter2 == 4 && lapCounter2 != 3) {
            counter2 = 0;
            lapCounter2++;
            for (int i = 0; i<cpSize; i++)
            {
                cpCleared2[i] = false;
            }
        }
      }
    };

    //the gravel x y coordinates

    for (int i = 0; i<Z; i++)
    {
      if (gravel_x[i] <= car[1].x && car[1].x <= gravel_x[i] + 125 && gravel_y[i] <= car[1].y && car[1].y <= gravel_y[i] + 125) 
      {
        car[1].speed = car[1].speed*0.5;
        
      }
    };

    //the mud x y coordinates


    for (int i = 0; i<R; i++)
    {
      if (mud_x[i] <= car[1].x && car[1].x <= mud_x[i] + 125 && mud_y[i] <= car[1].y && car[1].y <= mud_y[i] + 125) 
      {
        car[1].speed = car[1].speed*0.2;
      }
    };

    //the walls x y coordinates

    int wall1 = 0;

    for (int i = 0; i<L; i++)
    {
      if (walls_x[i] <= car[1].x + sin(car[1].angle) * car[1].speed && car[1].x + sin(car[1].angle) * car[1].speed <= walls_x[i] + 125 && walls_y[i] <= car[1].y - cos(car[1].angle) * car[1].speed && car[1].y - cos(car[1].angle) * car[1].speed <= walls_y[i] + 125)
      {
        wall1 = 1;
      }
      
    };


    //the speed x y coordinates


    for (int i = 0; i<S; i++)
    {
      if (speed_x[i] <= car[1].x && car[1].x <= speed_x[i] + 125 && speed_y[i] <= car[1].y && car[1].y <= speed_y[i] + 125) 
      {
        car[1].speed = car[1].speed*2;
        
      }
    };

    if (wall1 == 0) car[1].move();
    
    /*
    for(int i=0;i<N;i++)
    {
        car[i].move();
        //cout << car[0].x << "x" << car[0].y << "y" << "\n";
    } 
    */
	
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

    //checkpoint counter//
    ss1.str("");
    ss1<<counter <<"/" << cpSize;
    checkpoints.setString(ss1.str());
    app.draw(checkpoints);
    //checkpoint counter//

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

    //checkpoint counter//
    ss2.str("");
    ss2<<counter2 <<"/" << cpSize;
    checkpoints2.setString(ss2.str());
    app.draw(checkpoints2);
    //checkpoint counter//

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
    //end track
    if ((stop1 && (mode == 1)) || (stop1 && stop2)) {
        app.setView(app.getDefaultView());
        app.clear(Color::Black);
        app.draw(sStart);

        Text winText1("Player 1 time: " + nextLine +  firstTrackCompletion1 + nextLine + secondTrackCompletion1, mario_font);
        winText1.setPosition(75,100);
        winText1.setCharacterSize(50);
        winText1.setColor(Color::Yellow);

        app.draw(winText1);
        if (mode == 2) {
            Text winText2("Player 2 time:" + nextLine + firstTrackCompletion2 + nextLine + secondTrackCompletion2, mario_font);
            winText2.setPosition(75,325);
            winText2.setCharacterSize(50);
            winText2.setColor(Color::Yellow);

            app.draw(winText2);
        }
    }

    app.display();
    }
    

    return 0;
}
