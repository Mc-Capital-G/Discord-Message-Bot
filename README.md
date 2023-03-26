
This is an open source program designed to drive a Discord Bot.

The executable requires its runtime to be in the root folder of this file (Where CMakeLists, .gitignore, and this README file are)

If you intend to use this code to power your own bot, you will have to provide your own token in a file labeled "token.txt" in the data/ folder

This program is built using D++, an open source C++ library for working with Discord's API. 
Please note that D++ is not included in the git project, and you will have to install it for yourself to build.
For UNIX operating systems, simply git cloning https://github.com/brainboxdotcc/dpp.git into the libs/ folder should work.

I do not currently have a working windows build, but D++ is available for windows and they provide pre-compiled binaries, which should be simple enough to set up.
