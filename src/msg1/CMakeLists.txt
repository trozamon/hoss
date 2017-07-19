include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(MSG_1_SRCS MSG_1_HDRS
        Cpu.proto
        Heartbeat.proto
        Memory.proto
        ResourceAmount.proto
        )

add_library(hoss-msg1 SHARED ${MSG_1_SRCS})
target_link_libraries(hoss-msg1 ${PROTOBUF_LIBRARIES})
