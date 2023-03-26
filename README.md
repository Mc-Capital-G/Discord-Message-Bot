
This is an open source program designed to drive a Discord Bot.

The executable requires its runtime to be in the root folder of the project (Where CMakeLists, .gitignore, and this README file are)

If you intend to use this code to power your own bot, you will have to provide your own token in a file labeled "token.txt" in the data/ folder

This program is built using D++, an open source C++ library for working with Discord's API. 

You will have to run install.sh to finish setting up the project

install.sh:
    git clones the D++ library into the project for building
    creates additional files that the program needs to function
    attempts to run cmake and make to build the project

I do not currently have a working windows build, but D++ is available for windows and they provide pre-compiled binaries, which should be simple enough to set up.
