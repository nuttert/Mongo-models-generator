export PROJECT_NAME = test
.PHONY: $(PROJECT_NAME)
build:
	cd ./build && cmake .. && make -j$(nproc)
run:
	cd ./build && cmake .. && make -j$(nproc)
	./build/$(PROJECT_NAME)
run-test:
	mkdir -p build
	cd ./build && cmake .. -D TEST_MODE=TRUE -D PROJECT_NAME=$(PROJECT_NAME) && make && ./$(PROJECT_NAME)
