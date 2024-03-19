FRAMEWORKS='-framework AppKit -framework CoreVideo -framework Metal -framework MetalKit'
FLAGS='-std=c++20 --debug'
TIMEFORMAT=%R

platform()
{
    clang++ ${FRAMEWORKS} CNC_Main.mm -o synthesizer ${FLAGS}
}

main()
{
    time platform
}

main