cd datastructures
while getopts f: flag
do
    case "${flag}" in
        f) filter=${OPTARG};;
    esac
done
if [ -n "$filter" ];then
	export GTEST_FILTER=$filter
fi
cmake -S . -B build
cmake --build build
cd build && ctest -V
cd ../..
