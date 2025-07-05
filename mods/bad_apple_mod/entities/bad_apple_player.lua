FPS = 30
bad_apple_music = nil
bad_apple_sprite = nil
texture_index = 1
STEP_TIME = 1.0 / FPS
step_timer = 0
is_activated = false
FRAME_COUNT = 6572
texture_loader_entity = nil

function start()
end

function update(dt)
    if is_activated ~= true then
        return
    end
    
    if step_timer > STEP_TIME then
        step_timer = 0--step_timer - STEP_TIME
        texture = get_texture()
        if texture ~= nil then
            bad_apple_sprite:setTexture(texture)
        end
        STEP_TIME = 1.0 / FPS - dt
    end
    step_timer = step_timer + dt
end

function render()
    if is_activated then
        main_window:draw(bad_apple_sprite)
    end
end

function activate()
    bad_apple_sprite = Sprite.new()
    
    is_activated = true
    texture_loader_entity = Entity.findEntitiesWithName("texture_loader")[1]
    
    texture_loader_entity:callFunction("play_music", 0)
    
    texture = get_texture()
    if texture ~= nil then
        bad_apple_sprite:setTexture(texture)
    end
    bad_apple_sprite:setOrigin(Vector2.new(120, 90))
    bad_apple_sprite:attachTo(this)
    step_timer = 0
    texture_index = 1
end

function get_texture()
    if texture_loader_entity == nil then
        return nil
    end

    if texture_index > FRAME_COUNT then
        this:destroy()
    end
    texture = texture_loader_entity:callFunction("get_texture", 1, texture_index)
    texture_index = texture_index + 1
    return texture
end
