current_dir=$1
build_dir=$2

echo CUR DIR = $current_dir
echo BUILD DIR = $build_dir

python3.8 ${current_dir}/generators/generate.py --build-dir=${build_dir} --current_dir=${current_dir}
find ${build_dir}/codegen  -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;

