#include <model/project/Project.hpp>

int main(int argc, char *argv[])
{
    Project p;

    p.set_name_and_file("My amazing project", "./test");

    return 0;
}
