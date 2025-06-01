set(BOX2D_DIR ${CMAKE_SOURCE_DIR}/Zefir/thirdparty/box2d-3.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(BOX2D_SOURCES
	${BOX2D_DIR}/src/aabb.c
	${BOX2D_DIR}/src/arena_allocator.c
	${BOX2D_DIR}/src/array.c
	${BOX2D_DIR}/src/bitset.c
	${BOX2D_DIR}/src/body.c
	${BOX2D_DIR}/src/broad_phase.c
	${BOX2D_DIR}/src/constraint_graph.c
	${BOX2D_DIR}/src/contact.c
	${BOX2D_DIR}/src/contact_solver.c
	${BOX2D_DIR}/src/core.c
	${BOX2D_DIR}/src/distance.c
	${BOX2D_DIR}/src/distance_joint.c
	${BOX2D_DIR}/src/dynamic_tree.c
	${BOX2D_DIR}/src/geometry.c
	${BOX2D_DIR}/src/hull.c
	${BOX2D_DIR}/src/id_pool.c
	${BOX2D_DIR}/src/island.c
	${BOX2D_DIR}/src/joint.c
	${BOX2D_DIR}/src/manifold.c
	${BOX2D_DIR}/src/math_functions.c
	${BOX2D_DIR}/src/motor_joint.c
	${BOX2D_DIR}/src/mouse_joint.c
	${BOX2D_DIR}/src/mover.c
	${BOX2D_DIR}/src/prismatic_joint.c
	${BOX2D_DIR}/src/revolute_joint.c
	${BOX2D_DIR}/src/sensor.c
	${BOX2D_DIR}/src/shape.c
	${BOX2D_DIR}/src/solver.c
	${BOX2D_DIR}/src/solver_set.c
	${BOX2D_DIR}/src/table.c
	${BOX2D_DIR}/src/timer.c
	${BOX2D_DIR}/src/types.c
	${BOX2D_DIR}/src/weld_joint.c
	${BOX2D_DIR}/src/wheel_joint.c
	${BOX2D_DIR}/src/world.c
)

set_source_files_properties(
    ${BOX2D_SOURCES}
    PROPERTIES LANGUAGE C
)

add_library(Box2D STATIC ${BOX2D_SOURCES})

target_include_directories(Box2D PUBLIC
    ${BOX2D_DIR}/include
    ${BOX2D_DIR}/src/
)
