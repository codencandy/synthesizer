FRAMEWORKS='-framework AppKit -framework CoreVideo -framework Metal -framework MetalKit -framework GameController'
FLAGS='-std=c++20 --debug -Ilibs/imgui -Ilibs/imgui/backends'
TIMEFORMAT=%R
IGNORE='-Wno-nullability-completeness -Wno-unused-command-line-argument'
BUILD_TYPE=$1

all()
{
    rm -rf CNC_ImGui.o
    clang++ ${FRAMEWORKS} -c CNC_ImGui.mm ${FLAGS} ${IGNORE}
    platform
}

platform()
{
    clang++ ${FRAMEWORKS} CNC_Main.mm -o synthesizer CNC_ImGui.o ${FLAGS} ${IGNORE}
}

main()
{
    if [ "$BUILD_TYPE" = "ALL" ]
    then
        echo "complete build with imgui"
        time all
    else
        echo "only platform build"
        time platform
    fi
}

main