import core.thread, core.time;
import std.stdio, std.string, std.array, std.conv, std.exception, std.math, std.random;
import derelict.sdl2.sdl;//, derelict.sdl2.image;

int main()
{
    enum windowWidth = 800, windowHeight = 600;
    bool running = true;
    SDL_Event event;

    DerelictSDL2.load();
    //DerelictSDL2Image.load();

    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    scope(exit) SDL_Quit();

    SDL_Window* Main_Window = SDL_CreateWindow("DPong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    //enforce(Main_Window);
    scope(exit) SDL_DestroyWindow(Main_Window);

    SDL_Renderer* Main_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);
    //enforce(Main_Renderer);
    scope(exit) SDL_DestroyRenderer(Main_Renderer);

    //SDL_Surface* Loading_Surf;
    //scope(exit) SDL_DestorySurface(Loading_Surf);

    int winWidth, winHeight;
    SDL_GetWindowSize(Main_Window, &winWidth, &winHeight);

    auto player1Paddle = new Paddle(windowWidth / 10, winHeight / 2 - Paddle.paddleHeight / 2, windowWidth, windowHeight);
    auto player2Paddle = new Paddle(windowWidth - (windowWidth / 10 + Paddle.paddleWidth), winHeight / 2 - Paddle.paddleHeight / 2, windowWidth, windowHeight);
    auto ball = new Ball(400, 300, windowWidth, windowHeight);

    while (running) {
        uint t = SDL_GetTicks(); // get time since SDL_Init

        // collect keyboard events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            player1Paddle.move(-15, SDL_GetTicks() - t);
                            break;

                        case SDLK_DOWN:
                            player1Paddle.move(15, SDL_GetTicks() - t);
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        player1Paddle.moveMouse(mouseY);
        player2Paddle.moveMouse(mouseY);

        SDL_SetRenderDrawColor(Main_Renderer, 0, 0, 0, 0);
        SDL_RenderClear(Main_Renderer);

        //render paddle positions
        player1Paddle.update(Main_Renderer);
        player2Paddle.update(Main_Renderer);
        ball.update(Main_Renderer);

        SDL_Delay(16);

        // display renderer on screen
        SDL_RenderPresent(Main_Renderer);

        writeln(SDL_GetTicks() - t, " ms"); // write time since last call to SDL_GetTicks()
        //Thread.sleep( dur!("msecs")( 500 ) );
    }

    return 0;
}

class Paddle
{
    public:

        enum paddleWidth = 10;//50;
        enum paddleHeight = 150;

        this(int x, int y, int winWidth, int winHeight)
        {
            currBoundingBox.x = x;
            currBoundingBox.y = y;
            currBoundingBox.w = paddleWidth;
            currBoundingBox.h = paddleHeight;
            color = [255, 255, 255];
            windowWidth = winWidth;
            windowHeight = winHeight;
        }

        ~this()
        {
            //
        }

        void move(int dy, uint timeStep)
        {
            prevBoundingBox = currBoundingBox;
            currBoundingBox.y += dy;
            if (currBoundingBox.y < 0) {
                currBoundingBox.y = 0;
            } else if (currBoundingBox.y > windowHeight - paddleHeight) {
                currBoundingBox.y = windowHeight - paddleHeight;
            }
        }

        void moveMouse(int mY)
        {
            //writeln("Mouse Y: ", mY, " Paddle Y: ", currBoundingBox.y);
            currBoundingBox.y = mY - (paddleHeight / 2);

            // prevent paddle from going out of bounds
            if (currBoundingBox.y < 0) {
                currBoundingBox.y = 0;
            } else if (currBoundingBox.y > windowHeight - paddleHeight) {
                currBoundingBox.y = windowHeight - paddleHeight;
            }
        }

        void update(SDL_Renderer* renderer)
        {
            SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &currBoundingBox);
        }

        void setColor(ubyte r, ubyte g, ubyte b)
        {
            color = [r, g, b];
        }

    private:
        SDL_Rect prevBoundingBox, currBoundingBox;
        ubyte[] color;
        int windowWidth, windowHeight;
}

class Ball
{
    public:
        enum ballWidth = 5;
        enum ballHeight = 5;

        this(int x, int y, int winWidth, int winHeight)
        {
            bbox.x = x;
            bbox.y = y;
            bbox.w = ballWidth;
            bbox.h = ballHeight;

            color = [255, 255, 255];

            windowWidth = winWidth;
            windowHeight = winHeight;

            velocity[0] = cast(byte)uniform(-5, 5);
            while (velocity[0] == 0) {
                velocity[0] = cast(byte)uniform(-5, 5);
            }

            velocity[1] = cast(byte)uniform(-5, 5);
            while (velocity[1] == 0) {
                velocity[1] = cast(byte)uniform(-5, 5);
            }
        }

        ~this()
        {
            //
        }

        void move()
        {
            bbox.x += velocity[0];
            bbox.y += velocity[1];

            // hits off of either wall then this is points missed
            if (bbox.x < 0 || bbox.x + ballWidth > windowWidth) {
                bbox.x = windowWidth / 2 - ballWidth / 2;
                bbox.y = windowHeight / 2 - ballHeight / 2;

                // reset velocities
                velocity[0] = cast(byte)uniform(-5, 5);
                while (velocity[0] == 0) {
                    velocity[0] = cast(byte)uniform(-5, 5);
                }

                velocity[1] = cast(byte)uniform(-5, 5);
                while (velocity[1] == 0) {
                    velocity[1] = cast(byte)uniform(-5, 5);
                }
            }

            // hits off of floor or ceiling
            if (bbox.y < 0) {
                bbox.y = 0;
                velocity[1] *= -1;
            } else if (bbox.y + ballHeight > windowHeight) {
                bbox.y = windowHeight - ballHeight;
                velocity[1] *= -1;
            }

            //writeln("Ball x,y: ", bbox.x, " ", bbox.y);
            //writeln("Ball Velocity: ", velocity[0], " ", velocity[1]);
        }

        void update(SDL_Renderer* renderer)
        {
            move();
            SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &bbox);
        }

        void setColor(ubyte r, ubyte g, ubyte b)
        {
            color = [r, g, b];
        }

    private:
        SDL_Rect bbox;
        byte[2] velocity;
        ubyte[] color;
        int windowWidth, windowHeight;
}
