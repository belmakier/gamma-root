ez_unit_init()

# Abstraction

# Implementation
ez_this_unit_add_source(ban2root.cc)

# Make executable application
add_executable(${EZ_THIS_UNIT_NAME} ${EZ_THIS_UNIT_SOURCES})

# note standardised target names
target_link_libraries(${EZ_THIS_UNIT_NAME} ${ROOT_LIBRARIES} gamr_ornl)

# Install executable
ez_install_unit(${EZ_THIS_UNIT_NAME} "bin")
