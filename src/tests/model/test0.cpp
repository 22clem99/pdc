#include <filesystem>

#include <model/project/Project.hpp>
#include <utils/Log.hpp>

int main(int argc, char *argv[])
{
    Log::set_level(LogLevel::DEBUG);

    Project p("My amazing project", std::filesystem::path("./test0/prj"), std::filesystem::path("./images/Tux.svg"));

    return 0;
}
