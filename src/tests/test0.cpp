#include <model/project/Project.hpp>

#include <utils/Log.hpp>

int main(int argc, char *argv[])
{
    Log::set_level(LogLevel::INFO);

    Project p("My amazing project", "./test");

    Log::info(p.get_str());

    return 0;
}
