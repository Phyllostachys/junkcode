To have ```rustc``` print out target specifications:

    rustc -Z unstable-options --print target-spec-json --target thumbv7m-none-eabi

To get a list of targets:

    rustc --print target-list
