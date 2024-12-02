include(FetchContent)

FetchContent_Declare(
        scn
        GIT_REPOSITORY  https://github.com/eliaskosunen/scnlib
        GIT_TAG         v4.0.1
        GIT_SHALLOW     TRUE
)
FetchContent_MakeAvailable(scn)
