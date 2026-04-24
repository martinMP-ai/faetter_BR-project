idf_component_register(
    SRCS "test_app_main.c"
    INCLUDE_DIRS "."
    # "test" here is the special component name the unity_test_runner uses to
    # auto-discover and execute TEST_CASE() definitions registered by test
    # sub-components.
    REQUIRES unity counter
    WHOLE_ARCHIVE
)
