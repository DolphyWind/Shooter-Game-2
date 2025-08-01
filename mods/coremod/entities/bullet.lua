bulletSpeed = 500
bulletDamage = 10
bulletRadius = 10
playerId = -2
parentPlayer = nil

counter = 0
direction = Vector2.new(1, 0)
bulletCircle = CircleShape.new(bulletRadius)

function start()
    bulletCircle:setOrigin(Vector2.new(bulletRadius, bulletRadius))
    bulletCircle:attachTo(this)
    bulletCollider = Collider.new()
    
    local colliderPoints = {}
    local POINT_COUNT_DIVIDER = 3
    for i = 1, bulletCircle:getPointCount() // POINT_COUNT_DIVIDER, 1 do
        colliderPoints[i] = bulletCircle:getPoint(POINT_COUNT_DIVIDER * (i - 1) ) - bulletCircle:getOrigin()
    end
    bulletCollider:setPoints(colliderPoints)
    this:setCollider(bulletCollider)

    players = Entity.findEntitiesWithName("Player")
    for i=1, #players do
        if players[i]:getPlayerId() == playerId then
            mousePos = Mouse.getPosition(main_window)
            playerPos = players[i]:getPosition()

            angle = math.atan(mousePos.y - playerPos.y, mousePos.x - playerPos.x)
            direction.x = math.cos(angle)
            direction.y = math.sin(angle)

            playerCollider = players[i]:getCollider()
            playerRadius = (playerCollider:getPoints()[1] - playerCollider:getColliderCenter()):magnitude()
            this:move(direction * playerRadius)
            break
        end
    end
end

function update(dt)
    this:move(bulletSpeed * direction * dt)
    counter = counter + dt

    if counter > 5 then
        this:destroy()
    end
end

function render()
    main_window:draw(bulletCircle)
end

function onCollisionEnter(other)
    -- if other:getFullName() == "coremod/bullet" and other:getGlobal("playerId") ~= playerId then
        --this:destroy()
        --return
    --end

    if other:getPlayerId() ~= playerId then
        if other:isPlayer() then
            other:changeHealth(-bulletDamage)
        end
        
        this:destroy()
    end
end

function onCollisionExit(other)
end
