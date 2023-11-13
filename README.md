# Stefan-s-Slideaway-Pencil-Chisel-Code-3
Game project for Pencil, Chisel, Code! #3 - itch.io's GameJam

Short description:\
Another story of my rabbit Stefan, this time he has a problem and it's sliding continuously. Help him, to survive as long as possible, sometimes you get pulls to use, if you have some luck, you'll win another chance! Also remember, that green boxes can be jumped, blue ones can be slided through them, but beware red obstacles which are needed to be avoided.

Controls:\
[WSAD/arrow keys] - controls
[Space] - jump
[Left control] - "pull" the roulette slot

Dev notes:\
- For Polish people: Unfortunately, I also didn't have enough time to prepare a Polish translation, but in assets you can find a special logo with Polish title. I know adding an option to choose language at the beginning (after running the game) and replacing text strings with translated one it's quite easy. However, I decided that text aligning will be too time-consuming (yeah, game jams don't like wasting time). Now, I know that changing the origin of Text objects to center was also possible.
- For everyone: The roulette system is a lot more "cut" than I planned it initially, at least I'm happy that I added a possibility to regain health/lifes, but even this solution has a two bugs:
  - last roulette slot doesn't have an animation like two previous, I wasn't able to eliminate that bug, so my workaround is to increase a margin of sprite's Y-coordinate to increase chance to get an extra life
  - in one game after submitting, there was another problem with pernament blocked slots (3rd or 4th full "roster")
- Full roulette system was planned to grab "pull" coins or even power-up fragments on the stage and use them to get a pull, of course there were planned also power-ups (like: temporal invincible, temporal slow down, showing "safe path")
- Sometimes, you can think that a rabbit is landing onto the green box, but it doesn't interact at all, it's an intentional behavior (I don't call it feature), I had a problem with height, so I decided to do "one-time" check for this boxes, so when the character is in 2D space colliding with box, but a rabbit has a non-zero height, then the obstacle is jumped over.
- If you want to compile this project on your own, please note some things:
  - Visual Studio IDE (2022) was used
  - you need to download SFML (version 2.6.1, link is at the end of readme file), extract it and set in project's settings your path to library (tutorial from SFML's page is very helpful here)
  - copy openal.dll file to compiled Debug/Release (choose x86 build) folder, otherwise you won't be able to run program
- I don't plan to work on this project so now, but I also don't exclude to go back to that idea and doing it in another way
- Thank you, for if you were interested on my code, game or at least reading my notes 

Useful links:
- https://www.sfml-dev.org/download/sfml/2.6.1/ (I recommend downloading Visual C++ 17 (2022) - 32-bit one)
- https://ciachociech.itch.io/stefans-slideaway (game's page on itch.io)
- https://itch.io/jam/pencil-chisel-code-3/rate/2364311 (game jam's page on itch.io)
