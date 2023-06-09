all: remote

OUTPUT_NAME=parselib.out
COMPILER=g++ -std=c++11
CONFIG=
BUILD=$(COMPILER) $^ $(CONFIG) -o $(OUTPUT_NAME)

local: src/main/*.cpp test/*.cpp
		make clean
		$(BUILD)

remote: src/main/*.cpp test/*.cpp
		make clean
		git pull
		$(BUILD)

clean:
	rm -f $(OUTPUT_NAME)
