blockTexture = Texture.new()
blockSprite = Sprite.new()
textureLoaded = false

function start()
    if blockTexture:loadFromFile("block.png") then
        blockSprite:setTexture(blockTexture)
        textureLoaded = true
        
        blockSize = blockTexture:getSize():cwiseMul(blockSprite:getScale())
        blockSprite:setOrigin(blockSize / 2)
        blockCollider = Collider.new()
        blockCollider:setPoints({
            Vector2.new(0, 0) - blockSprite:getOrigin(),
            Vector2.new(0, blockSize.y) - blockSprite:getOrigin(),
            Vector2.new(blockSize.x, blockSize.y) - blockSprite:getOrigin(),
            Vector2.new(blockSize.x, 0) - blockSprite:getOrigin()
        })
        this:setCollider(blockCollider)
        blockSprite:attachTo(this)
    end
end

function update(dt)
end

function render()
    if textureLoaded then
        main_window:draw(blockSprite)
    end
end

function onDestroy()
end

function onCollisionEnter(other)
    if other:getFullName() == "coremod/bullet" then
        other:destroy()
        this:destroy()
        bad_apple_player = Entity.new("bad_apple_mod", "bad_apple_player", this:getPosition())
        bad_apple_player:callFunction("activate", 0)
    end
end

function onCollisionStay(other)
end

function onCollisionExit(other)
end


