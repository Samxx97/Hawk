add_executable(Sandbox "src/SandboxApp.cpp" )

target_precompile_headers(Sandbox PRIVATE 
								<iostream> 
								<functional>
								<vector> 
								<array> 
								<sstream>
								<memory>
								<algorithm>)

target_link_libraries(Sandbox PUBLIC Hawk)


