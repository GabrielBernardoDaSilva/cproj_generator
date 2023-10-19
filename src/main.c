#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *cmake_content = " "
                            "cmake_minimum_required(VERSION 3.0.0)\n"
                            "\n"
                            "project(&&project_name&&)\n"
                            "\n"
                            "## set c compiler\n"
                            "set(CMAKE_C_COMPILER \"gcc\")\n"
                            "\n"
                            "## set c version\n"
                            "set(CMAKE_C_STANDARD 17)\n"
                            "\n"
                            "## set c flags\n"
                            "set(CMAKE_C_FLAGS \"-Wall -Wextra -Werror -Wpedantic -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-but-set-parameter -Wno-unused-value -Wno-unused-result -Wno-unused-label -Wno-unused-local-typedefs -Wno-unused-macros -Wno-unused-const-variable -Wno-unused-const-variable -Wno-unused-const-parameter -Wno-unused-const-variable -Wno-unused-cons \")\n"
                            "\n"
                            "file (GLOB SOURCES \"src/*.c\")\n"
                            "\n"
                            "include_directories(./includes)\n"
                            "add_executable(${PROJECT_NAME} ${SOURCES})\n"
                            "\n"
                            "message(STATUS \"CMAKE_C_FLAGS: \" ${CMAKE_C_FLAGS})\n"
                            "message(STATUS \"CMAKE_C_COMPILER: \" ${CMAKE_C_COMPILER})\n"
                            "message(STATUS \"CMAKE_C_STANDARD: \" ${CMAKE_C_STANDARD})\n"
                            "message(STATUS \"Final Project Name: \" ${PROJECT_NAME})\n";

const char *main_c_content = "#include <stdio.h>\n"
                             "\n"
                             "\n"
                             "int main(int argc, char const *argv[])\n"
                             "{\n"
                             "\tprintf(\"Hello World\\n\");\n"
                             "\treturn 0;\n"
                             "}\n";

int main(int argc, char const *argv[])
{

#if __WIN32 || __WIN64
    printf("Not supported in Windows\n");
    return 1;
#endif

    if (argc < 2)
    {
        printf("\033[1;31mTo few arguments send file name example project_name=\"test_proj\" or -p=\"test_prog\"\033[0m\n");
        return 1;
    }
    const char *project_name = argv[1];
    // find char in string
    const char *find = strchr(project_name, '=');
    if (find == NULL)
    {
        printf("\033[1;31mTo few arguments send file name example project_name=\"test_proj\" or -p=\"test_prog\"\033[0m\n");
        return 1;
    }

    // get file name
    char *project = (char *)malloc(strlen(find));
    strcpy(project, find + 1);
    printf("\033[1;34mYour project name is %s\033[0m\n", project);

    // create project
    // starting with folder that will contain project
    int ckeck = mkdir(project, 0777);
    if (ckeck == -1)
    {
        // check if folder already exist
        printf("\033[1;31mFolder already exist\033[0m\n");
        return 1;
    }

    // create src folder
    char *src = (char *)malloc(strlen(project) + 4);
    strcpy(src, project);
    strcat(src, "/src");
    ckeck = mkdir(src, 0777);
    if (ckeck == -1)
    {
        // check if folder already exist
        printf("\033[1;31mFolder already exist\033[0m\n");
        return 1;
    }

    // create include folder
    char *include = (char *)malloc(strlen(project) + 8);
    strcpy(include, project);
    strcat(include, "/include");
    ckeck = mkdir(include, 0777);
    if (ckeck == -1)
    {
        // check if folder already exist
        printf("\033[1;31mFolder already exist\033[0m\n");
        return 1;
    }

    // create main.c file
    char *main = (char *)malloc(strlen(project) + 9);
    strcpy(main, project);
    strcat(main, "/src/main.c");
    FILE *main_file = fopen(main, "w");
    if (main_file == NULL)
    {
        printf("\033[1;31mError creating main.c file\033[0m\n");
        return 1;
    }
    fwrite(main_c_content, 1, strlen(main_c_content), main_file);
    fclose(main_file);

    // create CMakeLists.txt file
    char *cmake = (char *)malloc(strlen(project) + 15);
    strcpy(cmake, project);
    strcat(cmake, "/CMakeLists.txt");
    FILE *cmake_file = fopen(cmake, "w");
    if (cmake_file == NULL)
    {
        printf("\033[1;31mError creating CMakeLists.txt file\033[0m\n");
        return 1;
    }
    char *cmake_content_proj = (char *)malloc(strlen(cmake_content) + strlen(project));
    strcpy(cmake_content_proj, cmake_content);

    // replace &&project_name&& with project name
    char *find_project_name = strstr(cmake_content_proj, "&&project_name&&");
    if (find_project_name == NULL)
    {
        printf("\033[1;31mError creating CMakeLists.txt file\033[0m\n");
        return 1;
    }

    size_t project_name_len = strlen(project);
    size_t placeholder_len = strlen("&&project_name&&");
    size_t cmake_content_len = strlen(cmake_content_proj);
    size_t new_cmake_content_len = cmake_content_len - placeholder_len + project_name_len;
    char *new_cmake_content = (char *)malloc(new_cmake_content_len);
    memset(new_cmake_content, 0, new_cmake_content_len);
    memcpy(new_cmake_content, cmake_content_proj, find_project_name - cmake_content_proj);
    memcpy(new_cmake_content + (find_project_name - cmake_content_proj), project, project_name_len);
    memcpy(new_cmake_content + (find_project_name - cmake_content_proj) + project_name_len, find_project_name + placeholder_len, cmake_content_len - (find_project_name - cmake_content_proj) - placeholder_len);
    new_cmake_content[new_cmake_content_len - 1] = '\0';
    free(cmake_content_proj);
    cmake_content_proj = new_cmake_content;

    fwrite(cmake_content_proj, 1, strlen(cmake_content_proj), cmake_file);
    fclose(cmake_file);


    // finish create project
    printf("\033[1;32mProject %s created\033[0m\n", project);

    //clean up
    free(project);
    free(src);
    free(include);
    free(main);
    free(cmake);
    free(new_cmake_content);

    return 0;
}
