donutTexture = Texture.new()
donutLoaded = false
donutSprite = Sprite.new()
donutSize = Vector2.new(0, 0)

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
    end
end

function update(dt)
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
    if other:getName() == "bullet" then
        -- other:destroy()
    end
end
