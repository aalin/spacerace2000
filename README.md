# Spacerace 2000

A game set in some kind of space world.

## TODO

### Graphics

* Some kind of sky.
* Framebuffers.
* Depth of field.

### Random

* The camera should never "go through" the track.
* Game menu.

### Track

* `TrackModel` and `TrackInfo` have a lot in common. Extract that stuff to another class.
* The track model duplicates lots of vertices. Make use of an element buffer.
* Tracks should load from files.

### Player

* The player should crash when it goes off the track.
* It should not be possible to jump to other parts of the track.
* Gravity.
* AI players.
* Gamepad/joystick support.

## Contributing

Fork the project, make the changes you want and send a pull request. Make sure the game runs as it already does or better after each commit. Try to follow any naming or coding conventions existing around the code you're working with.
