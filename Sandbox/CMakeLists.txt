add_executable(Sandbox "src/SandboxApp.cpp"  "src/SandBox2D.h" "src/SandBox2D.cpp")

target_precompile_headers(Sandbox PRIVATE 
								<iostream> 
								<functional>
								<vector> 
								<array> 
								<sstream>
								<memory>
								<algorithm>)

target_link_libraries(Sandbox PUBLIC Hawk)


