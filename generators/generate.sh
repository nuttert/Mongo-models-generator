python3.8 ./generators/generate.py --build-dir=build
find ./build/codegen  -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;

