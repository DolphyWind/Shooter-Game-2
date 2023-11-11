function start()
    Entity.new("bad_apple_mod", "block", Vector2.new(700, 300))
end

function update(dt)
    if Mouse.getButtonDown(Mouse.left) and main_window:hasFocus() then
        player = Entity.findEntitiesWithName("Player")[1]
        if player ~= nil then
            bullet = Entity.new("coremod", "bullet", player:getPosition())
            bullet:setGlobal("playerId", player:getPlayerId())
        end
    end
end

function render()
end

function onDestroy()
end

function onCollisionEnter(other)
end

function onCollisionStay(other)
end

function onCollisionExit(other)
end


