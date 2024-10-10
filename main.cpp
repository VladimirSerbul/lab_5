#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
typedef HINSTANCE LIB_HANDLE;
#define LOAD_LIBRARY(name) LoadLibraryW(name)
#define GET_FUNCTION(lib, name) GetProcAddress(lib, name)
#define CLOSE_LIBRARY(lib) FreeLibrary(lib)
#define EXPANSION 1
#else
#include <dlfcn.h>
typedef void* LIB_HANDLE;
#define LOAD_LIBRARY(name) dlopen(name, RTLD_LAZY)
#define GET_FUNCTION(lib, name) dlsym(lib, name)
#define CLOSE_LIBRARY(lib) dlclose(lib)
#define EXPANSION 0
#endif
#define ARRAY_SIZE 20
#define MATRIX_ROWS 5
#define MATRIX_COLS 6
int main()
{
    std::cout << "Choose array(20) or matrix(5;6), if array then click 1, if matrix then click all except 1" << std::endl;
    char menu;
    std::cin >> menu;
    void* lib;
    
    LPCWSTR name;
    if (menu == '1')
    {
        void (*fun_fill)(int*, int);
        void (*fun_process)(int*, int);
        int array[ARRAY_SIZE];
        if (EXPANSION == 1)
        {
            name = (LPCWSTR)L"libarray.dll";
        }
        else
        {
            name = (LPCWSTR)L"libarray.so";
        }
        
        lib = LOAD_LIBRARY(name); //загрузка библиотеки в память;
        if (!lib)
        {
            printf("cannot open library '%s'\n", name);
            system("Pause");
            return -1;
        }
        fun_fill = (void (*)(int*, int))GET_FUNCTION((LIB_HANDLE)lib, "fillarray");
        if (fun_fill == NULL)
        {
            printf("cannot load function fillarray\n");
	    std::cerr << "Cannot load function fillarray: " << GetLastError() << std::endl;
            system("Pause");
            return -2;
        }
        else
        {
            fun_fill(array, ARRAY_SIZE);
        }
        fun_process = (void (*)(int*, int))GET_FUNCTION((LIB_HANDLE)lib, "processarray");
        if (fun_process == NULL)
        {
            printf("cannot load function processarray\n");
            system("Pause");
            return -2;
        }
        else
        {
            fun_process(array, ARRAY_SIZE);
        }
        //получение указателя на функции из библиотеки;
     
        CLOSE_LIBRARY((LIB_HANDLE)lib);//выгрузка библиотеки;
        
        std::cout << "Processed Array:" << std::endl;
        for (int i = 0; i < ARRAY_SIZE; ++i)
        {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        void (*fun_fill)(int[5][6]);
        void (*fun_process)(int[5][6]);
        int matrix[MATRIX_ROWS][MATRIX_COLS];
        if (EXPANSION == 1)
        {
            name = (LPCWSTR)L"libmatrix.dll";
        }
        else
        {
            name = (LPCWSTR)L"libmatrix.so";
        }

        lib = LOAD_LIBRARY(name); //загрузка библиотеки в память;
        if (!lib)
        {
            printf("cannot open library '%s'\n", name);
            system("Pause");
            return -1;
        }
        fun_fill = (void (*)(int[5][6]))GET_FUNCTION((LIB_HANDLE)lib, "fillmatrix");
        if (fun_fill == NULL)
        {
            printf("cannot load function fillmatrix\n");
            std::cerr << "Cannot load function fillmatrix: " << GetLastError() << std::endl;
            system("Pause");
            return -2;
        }
        else
        {
            fun_fill(matrix);
        }
        fun_process = (void (*)(int[5][6]))GET_FUNCTION((LIB_HANDLE)lib, "processmatrix");
        if (fun_process == NULL)
        {
            printf("cannot load function processmatrix\n");
            system("Pause");
            return -2;
        }
        else
        {
            fun_process(matrix);
        }

        CLOSE_LIBRARY((LIB_HANDLE)lib);//выгрузка библиотеки;

        std::cout << "Processed Matrix:" << std::endl;
        for (int i = 0; i < MATRIX_ROWS; ++i) {
            for (int j = 0; j < MATRIX_COLS; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    system("Pause");
<<<<<<< HEAD
=======


>>>>>>> no-windows
    return 0;
}
