cmake_minimum_required(VERSION 3.25)
project(c_codes)

set(CMAKE_CXX_STANDARD 17)
# 添加一个可执行程序 如果只有一个可执行入口 一般采用${PROJECT_NAME}作为名字

# 查找当前目录下的所有源文件，并将名称保存到 DIR_SRCS 变量
aux_source_directory(./selfClass/ DIR_SRCS)
#add_executable(Main main.cpp selfClass/TestImport.cpp selfClass/Conversation.cpp)
add_executable(Main main.cpp ${DIR_SRCS})


add_executable(Hello HelloWorld.cpp)
add_executable(MemoryManage MemoryManage.cpp)
add_executable(BinarySearch arg/BinarySearch.cpp)
add_executable(FunctionUse FunctionUse.cpp)
add_executable(PointerAndRef PointerAndRef.cpp)
add_executable(ArrayPointer ArrayPointer.cpp)
add_executable(ConstPointer ConstPointer.cpp)
add_executable(MemoryManageDeep MemoryManageDeep.cpp)
add_executable(DestructorAndDeepCopy DestructorAndDeepCopy.cpp)

# 添加 selfClass 子目录
add_subdirectory(./selfClass/)
# 对名称为FunctionUse的可执行程序 要链接的库文件的名字 相当于gcc中的-l(小写的l)参数
target_link_libraries(FunctionUse selfClassLib)

# 去哪里找头文件 相当于gcc/clang 中的-I(i的大写字母)参数
#include_directories("./selfClass/")

add_executable(StaticUse StaticUse.cpp)
add_executable(OverRideUse OverRideUse.cpp)
add_executable(InheritanceUse InheritanceUse.cpp)
add_executable(TemplateUse TemplateUse.cpp)