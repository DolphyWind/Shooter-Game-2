FRAME_COUNT = 6572
bad_apple_textures = {}
bad_apple_music = Music.new()

function start()
    bad_apple_music:openFromFile("bad_apple_audio.wav")
    for i = 1, FRAME_COUNT do
        bad_apple_textures[i] = Texture.new()
        bad_apple_textures[i]:loadFromFile(string.format("frames/frame_%04d.png", i))
    end
end

function get_texture(i)
    return bad_apple_textures[i]
end

function play_music()
    bad_apple_music:play()
end
