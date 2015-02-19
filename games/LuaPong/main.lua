function love.load()
    -- setup paddle size based on window
    paddleWidth = love.graphics.getWidth() / 20
    paddleHeight = love.graphics.getHeight() / 5
    ballRadius = love.graphics.getWidth() / 100

    paddle1Pos = {love.graphics.getWidth() / 15, love.graphics.getHeight() / 3}
    paddle2Pos = { love.graphics.getWidth() - love.graphics.getWidth() / 15 - paddleWidth,
    love.graphics.getHeight() / 3}
    ballPos = {love.graphics.getWidth() / 2 - (2 * ballRadius), love.graphics.getHeight() / 2 - (2 * ballRadius)}
    ballVel = {math.random(500), math.random(250)}
end

function love.draw()
    love.graphics.clear()
    love.graphics.polygon(  'fill',
    paddle1Pos[1], paddle1Pos[2],
    paddle1Pos[1] + paddleWidth, paddle1Pos[2],
    paddle1Pos[1] + paddleWidth, paddle1Pos[2] + paddleHeight,
    paddle1Pos[1], paddle1Pos[2] + paddleHeight)

    love.graphics.polygon(  'fill',
    paddle2Pos[1], paddle2Pos[2],
    paddle2Pos[1] + paddleWidth, paddle2Pos[2],
    paddle2Pos[1] + paddleWidth, paddle2Pos[2] + paddleHeight,
    paddle2Pos[1], paddle2Pos[2] + paddleHeight)

    love.graphics.circle('fill', ballPos[1], ballPos[2], ballRadius, 12)

    local windowStr = "Width: ".. love.graphics.getWidth() .. ", Height: " .. love.graphics.getHeight()
    local paddle1Str = "X: " .. paddle1Pos[1] .. ", Y:" .. paddle1Pos[2]
    local paddle2Str = "X: " .. paddle2Pos[1] .. ", Y:" .. paddle2Pos[2]
    local ballStr = "X: " .. ballPos[1] .. ", Y:" .. ballPos[2]
    love.graphics.print(windowStr, 0, 0)
    love.graphics.print(paddle1Str, 0, 11)
    love.graphics.print(paddle2Str, 0, 22)
    love.graphics.print(ballStr, 0, 33)
end

rate = 200   -- change to change the rate at which the var is changed
function love.update(dt)
    -- update paddle 1
    if love.keyboard.isDown("a") then   -- reduce the value
        paddle1Pos[2] = paddle1Pos[2] - (dt * rate)
    end

    if love.keyboard.isDown("s") then   -- increase the value
        paddle1Pos[2] = paddle1Pos[2] + (dt * rate)
    end

    if paddle1Pos[2] < 0 then paddle1Pos[2] = 0 end
    if paddle1Pos[2] + paddleHeight > love.graphics.getHeight() then
        paddle1Pos[2] = love.graphics.getHeight() - paddleHeight
    end

    -- update paddle 2
    if love.keyboard.isDown("k") then   -- reduce the value
        paddle2Pos[2] = paddle2Pos[2] - (dt * rate)
    end

    if love.keyboard.isDown("l") then   -- increase the value
        paddle2Pos[2] = paddle2Pos[2] + (dt * rate)
    end

    if paddle2Pos[2] < 0 then paddle2Pos[2] = 0 end
    if paddle2Pos[2] + paddleHeight > love.graphics.getHeight() then
        paddle2Pos[2] = love.graphics.getHeight() - paddleHeight
    end

    ballPos = {ballPos[1] + (ballVel[1] * dt), ballPos[2] + (ballVel[2] * dt)}
    if ballPos[1] > love.graphics.getWidth() or ballPos[1] < 0 then
        ballVel[1] = ballVel[1] * -1
    end
    if ballPos[2] > love.graphics.getHeight() or ballPos[2] < 0 then
        ballVel[2] = ballVel[2] * -1
    end
end