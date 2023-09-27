donutTexture = Texture.new()
donutLoaded = false
donutSprite = Sprite.new()
playerVelocity = 250
playerSpeed = Vector2.new(0, 0)
donutSize = Vector2.new(0, 0)
local outerCircleRadius = 0

function start()
    if donutTexture:loadFromFile("donut.png") then
        donutLoaded = true
        donutSprite:setTexture(donutTexture)
        donutSprite:attachTo(this)
        donutSprite:setScale(3, 3)
        donutSize = donutTexture:getSize():cwiseMul(donutSprite:getScale())
        donutSprite:setOrigin(donutTexture:getSize() / 2)

        donutCollider = Collider.new()
        donutCollider:setPoints({
            -donutSize / 2,
            Vector2.new(-donutSize.x / 2, donutSize.y / 2),
            donutSize / 2,
            Vector2.new(donutSize.x / 2, -donutSize.y / 2),
        })
        donutCollider:setImmovable(true)
        donutCollider:setStatic(true)
        this:setCollider(donutCollider)

        outerCircleRadius = donutSize:magnitude() / 2
    end
end

function update(dt)
    InterpretLUdataAs("Entity")

    playerSpeed.x = 0
    playerSpeed.y = 0

    if donutLoaded then
        if Keyboard.getKey(Keyboard.Left) then
            playerSpeed.x = playerSpeed.x - playerVelocity
        end
        if Keyboard.getKey(Keyboard.Right) then
            playerSpeed.x = playerSpeed.x + playerVelocity
        end
        if Keyboard.getKey(Keyboard.Down) then
            playerSpeed.y = playerSpeed.y + playerVelocity
        end
        if Keyboard.getKey(Keyboard.Up) then
            playerSpeed.y = playerSpeed.y - playerVelocity
        end

        this:move(playerSpeed * dt)
    end
end

function render()
    main_window:draw(donutSprite)
end

function onDestroy()
end

function onCollisionEnter(other)
end

function onCollisionStay(other)
end

function onCollisionExit(other)
end
