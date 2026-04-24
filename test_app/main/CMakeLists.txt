idf_component_register(
    SRCS
        "test_app_main.c"
        "test_counter.c"
    INCLUDE_DIRS "."
    REQUIRES unity counter
    # WHOLE_ARCHIVE keeps the TEST_CASE() registration constructors generated
    # by Unity from being dropped by the linker, so unity_run_all_tests() can
    # discover and execute every case in this component.
    WHOLE_ARCHIVE
)
