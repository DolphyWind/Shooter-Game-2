# Stopwatch
Exports sfex::Stopwatch API to Lua. A Stopwatch is basically a stoppable clock.

### Methods
`Stopwatch.new()`: Creates a new stopwatch object.  
`stopwatch:getElapsedTime()`: Get elapsed time since the last restart or the creation of `stopwatch` object in seconds.  
`stopwatch:pause()`: Pauses the `stopwatch` object. Does nothing if `stopwatch` is already paused.  
`stopwatch:resume()`: Resumes the `stopwatch` object. Does nothing if `stopwatch` is not paused.  
`stopwatch:restart()`: Restarts the `stopwatch`.  
`stopwatch:isPaused()`: Returns true if `stopwatch` is paused. Returns false otherwise.  
