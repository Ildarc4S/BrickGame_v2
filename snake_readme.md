# School 21 - BrickGame - Tetris

Tetris is one of the most addictive games in the BrickGame series. Here is a classic interpretation of the game written in C, with ncurses-based console graphics to spice up the gameplay.

The game logic is based on finite state machines, a diagram of which you can see below.

![FSM](image/fsm.png)

### Game control
- **Start Game**: Press `s`
- **End the Game**: Press `q`
- **Pause the Game**: Press `p`
- **Move Left**: Press the `Left Arrow`
- **Move Right**: Press the `Right Arrow`
- **Accelerate (Move Down double)**: Press double the `Down Arrow`
- **Rotate the Tetramino**: Press `Space`

### Scoring
- Clearing `1` row: `100` points
- Clearing `2` rows: `300` points
- Clearing `3` rows: `700` points
- Clearing `4` rows: `1500` points

### Levels
- The game starts at level `1`.
- Every time you score `600` points, the level increases by `1`, and the speed of falling tetrominoes increases.
- The maximum level is `10`.

### End of the Game
The game ends when a new tetromino cannot be placed at the top of the playing field, meaning the blocks have piled up too high. Your final score will be displayed, and if it’s higher than your previous best, it will be saved as the new high score

Good luck, and enjoy the game!

### Installation
To install the game, make sure you have the ncurses library.

```bash
make install
```

### Documentation generation

Install packages:
* graphviz
* doxygen
```bash
make dvi 
```
