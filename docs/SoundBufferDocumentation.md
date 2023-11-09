# RectangleShape
Exports `sf::SoundBuffer` API to Lua. A SoundBuffer represents a storage for audio samples defining a sound.  

### Methods
`SoundBuffer.new()`: Creates an empty sound buffer object.  
`SoundBuffer.new(sbuffer: SoundBuffer)`: Creates a copy of given sound buffer.  
`sbuffer:loadFromFile(filename: string)`: Loads the sound buffer from file.  
`sbuffer:saveToFile(filename: string)`: Saves the sound buffer to an audio file.  
`sbuffer:getSamples()`: Returns the audio samples stored in the buffer as a table.  
`sbuffer:getSampleCount()`: Returns the number of samples stored in the buffer.  
`sbuffer:getSampleRate()`: Returns the sample rate of the sound.  
`sbuffer:getChannelCount()`: Returns the number of channels used by the sound.  
`sbuffer:getDuration()`: Returns the total duration of the sound in seconds.  