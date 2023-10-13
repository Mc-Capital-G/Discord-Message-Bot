touch data/token.txt
touch data/cache.txt

mkdir libs
cd libs

git clone https://github.com/brainboxdotcc/dpp.git

cd ..

cmake -S . -B build/
make -C build/

echo "Add discord bot token to the token.txt file in the data folder"
