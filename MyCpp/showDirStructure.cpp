#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

using namespace std;

/***************************
 * 函数功能: 遍历文件夹
 * return: void
 * @para folderPath: 文件夹路径
***************************/
void showDirStructure(char *folderPath)
{
    /********** BEGIN **********/
    DIR* dir;
    struct dirent* ptr;
    char base[500];
    static int times = 0;
    //Open error...
    if ((dir=opendir(folderPath)) == NULL)
    {
        cout << "Open dir error..." << endl;
        exit(1);
    }
    //Open success...
    if ( times == 0 )
    {
        //print root dir
        char* p = folderPath;
        while ( *p != '\0' )
        {
            p++;
        }
        while ( *p != '/' )
        {
            p--;
        }
        p++;
        cout << "+--" << p << endl;
    }
    times++;
    while ((ptr=readdir(dir)) != NULL)
    {
        //disappear current dir . OR parrent dir ..
        if (strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0)
        {
            continue;
        }
        //files
        else if (ptr->d_type == 8)
        {
            for (int i=0; i<times; i++)
            {
                cout << "  ";
            }
            cout << "--" << ptr->d_name  << endl;
        }
        //Link file
        else if (ptr->d_type == 10)
        {
            for (int i=0; i<times; i++)
            {
                cout << "  ";
            }
            cout << "--" << ptr->d_name  << endl;
        }
        //dir
        else if (ptr->d_type == 4)
        {
            memset(base,'\0',sizeof(base));
            strcpy(base,folderPath);
            strcat(base,"/");
            strcat(base,ptr->d_name);
            for (int i=0; i<times; i++)
            {
                cout << "  ";
            }
            cout << "+--" << ptr->d_name  << endl;
            showDirStructure(base); //DiGuiDiaoYong
        }

    }
    closedir(dir);
    times--;
    /********** END **********/
}


int main(void)
{
    char filepath[30] = {"/home/eisenhao/Documents"};
    showDirStructure(filepath);
    return 0;
}

