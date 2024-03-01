dev:
	emcmake cmake . -B./build -DCMAKE_BUILD_TYPE=Debug
	cmake --build ./build

prod:
	emcmake cmake . -B./build -DCMAKE_BUILD_TYPE=Release
	cmake --build ./build
