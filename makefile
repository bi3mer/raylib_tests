wasm:
	emcc \
		src/*.cpp \
		-I ./src/ \
		-I ../dependencies/raylib-5.0_webassembly/include \
		-L ../dependencies/raylib-5.0_webassembly/lib \
		-lraylib \
		-lm \
		-s USE_GLFW=3 \
		-s GL_ENABLE_GET_PROC_ADDRESS \
		-s WASM=1 \
		-s MODULARIZE=1 \
		-s EXPORT_ES6=1 \
		-o index.js \
		-O3
		# --embed-file ./assets \

run:
	g++ src/*.cpp -I./src/*.hpp  -lraylib -std=c++17
	./a.out	