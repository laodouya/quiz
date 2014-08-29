#include <unistd.h>
#include <dirent.h>
#include <sys/types.h> // for opendir(), readdir(), closedir()
#include <sys/stat.h> // for stat()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define PROC_DIRECTORY "/proc/"
#define CASE_SENSITIVE    1
#define CASE_INSENSITIVE  0
#define EXACT_MATCH       1
#define INEXACT_MATCH     0
#define COMPARE_FULL_PATH 1
#define COMPARE_NAME      0

//是不是数字
int IsNumeric(const char* ccharptr_CharacterList)
{
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}

//intCaseSensitive=0大小写不敏感
int strcmp_Wrapper(const char *s1, const char *s2, int intCaseSensitive)
{
    if (intCaseSensitive)
        return !strcmp(s1, s2);
    else
        return !strcasecmp(s1, s2);
}

//intCaseSensitive=0大小写不敏感
int strstr_Wrapper(const char* haystack, const char* needle, int intCaseSensitive)
{
    if (intCaseSensitive)
        return (int) strstr(haystack, needle);
    else
        return (int) strcasestr(haystack, needle);
}

pid_t GetFirstPIDbyName_implements(const char* cchrptr_ProcessName, int intCaseSensitiveness, int intExactMatch, int isCompareFullPath)
{
    char CommandLinePath[1000]  ;
    char pathAndNameOfProcess[3000]  ;
    char* stringToCompare = NULL ;
    pid_t pid_ProcessIdentifier = (pid_t) -1 ;
    struct dirent* de_DirEntity = NULL ;
    DIR* dir_proc = NULL ;

    int (*CompareFunction) (const char*, const char*, int) ;

    if (intExactMatch)
        CompareFunction = &strcmp_Wrapper;
    else
        CompareFunction = &strstr_Wrapper;


    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == NULL)
    {
        perror("Couldn't open the " PROC_DIRECTORY " directory") ;
        return (pid_t) -2 ;
    }

    // Loop while not NULL
    while ( (de_DirEntity = readdir(dir_proc)) )
    {
        if (de_DirEntity->d_type == DT_DIR)
        {
            if (IsNumeric(de_DirEntity->d_name))
            {
                strcpy(CommandLinePath, PROC_DIRECTORY) ;
                strcat(CommandLinePath, de_DirEntity->d_name) ;
                strcat(CommandLinePath, "/cmdline") ;
                FILE* fd_CmdLineFile = fopen (CommandLinePath, "rt") ;  //open the file for reading text
                if (fd_CmdLineFile)
                {
                    fscanf(fd_CmdLineFile, "%s", pathAndNameOfProcess) ; //read from /proc/<NR>/cmdline
                    fclose(fd_CmdLineFile);  //close the file prior to exiting the routine
                    if (isCompareFullPath)
                        stringToCompare = pathAndNameOfProcess;
                    else if (strrchr(pathAndNameOfProcess, '/'))
                        stringToCompare = strrchr(pathAndNameOfProcess, '/') +1 ;
                    else
                        stringToCompare = pathAndNameOfProcess ;

                    if ( CompareFunction(stringToCompare, cchrptr_ProcessName, intCaseSensitiveness) )
                    {
                        pid_ProcessIdentifier = (pid_t) atoi(de_DirEntity->d_name) ;
                        closedir(dir_proc) ;
                        return pid_ProcessIdentifier ;
                    }
                }
            }
        }
    }
    closedir(dir_proc) ;
    return pid_ProcessIdentifier ;
}

//简单实现
pid_t GetFirstPIDbyName_Wrapper(const char* cchrptr_ProcessName)
{
        return GetFirstPIDbyName_implements(cchrptr_ProcessName, CASE_INSENSITIVE, INEXACT_MATCH, COMPARE_NAME);
}
/*
int main()
{
    pid_t pid = GetFirstPIDbyName_Wrapper("bash") ; // If -1 = not found, if -2 = proc fs access error
    printf("PID %d\n", pid);
    return EXIT_SUCCESS ;
}
*/
