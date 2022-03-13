export PROJECT_NAME = generator_tests
.PHONY: $(PROJECT_NAME)
build:
	cd ./build && cmake .. && make -j$(nproc)
run:
	cd ./build && cmake .. && make -j$(nproc)
	./build/test/$(PROJECT_NAME)
