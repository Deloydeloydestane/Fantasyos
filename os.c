#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

void clear_screen() {
    printf("\033[H\033[J");
}

void list_dir() {
    struct dirent *de;
    DIR *dr = opendir(".");
    if (dr == NULL) {
        printf("Error: Could not open directory.\n");
        return;
    }
    while ((de = readdir(dr)) != NULL) {
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            printf("%s  ", de->d_name);
        }
    }
    printf("\n");
    closedir(dr);
}

void install_package(char *pkg_name) {
    if (strlen(pkg_name) == 0) {
        printf("Error: Missing package name. Usage: apt install <package>\n");
        return;
    }
    printf("[apt] Installing %s...\n", pkg_name);
    
    char sys_cmd[256];
    #ifdef __ANDROID__
        snprintf(sys_cmd, sizeof(sys_cmd), "pkg install %s -y", pkg_name);
    #else
        snprintf(sys_cmd, sizeof(sys_cmd), "sudo apt-get install %s -y", pkg_name);
    #endif

    if (system(sys_cmd) == 0) {
        printf("[apt] %s installed successfully.\n", pkg_name);
    } else {
        printf("[apt] Failed to install %s.\n", pkg_name);
    }
}

int main() {
    char input[512];
    char cmd[256];
    char param[256];
    char cwd[256];

    clear_screen();
    printf("==========================================\n");
    printf("        FANTASY OS INITIALIZED            \n");
    printf("==========================================\n");
    printf("Type 'help' for available commands.\n\n");

    while(1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("user@fantasyos#root:%s$ ", cwd);
        } else {
            printf("user@fantasyos#root:$ ");
        }

        if (fgets(input, sizeof(input), stdin) == NULL) break;
        input[strcspn(input, "\n")] = 0;

        cmd[0] = '\0';
        param[0] = '\0';
        sscanf(input, "%s %[^\n]", cmd, param);

        if (strlen(cmd) == 0) continue;

        if (strcmp(cmd, "cd") == 0) {
            if (strlen(param) == 0) {
                char *home = getenv("HOME");
                if (home != NULL) chdir(home);
            } else if (chdir(param) != 0) {
                printf("cd: No such file or directory: %s\n", param);
            }
        }
        else if (strcmp(cmd, "ls") == 0) {
            list_dir();
        }
        else if (strcmp(cmd, "apt") == 0) {
            char action[128] = "";
            char target[128] = "";
            sscanf(param, "%s %s", action, target);
            
            if (strcmp(action, "install") == 0) {
                install_package(target);
            } else {
                printf("Usage: apt install <package>\n");
            }
        }
        else if (strcmp(cmd, "clear") == 0) {
            clear_screen();
        }
        else if (strcmp(cmd, "help") == 0) {
            printf("Commands:\n");
            printf("  ls                  List directory contents\n");
            printf("  cd <dir>            Change directory\n");
            printf("  apt install <pkg>   Install package via package manager\n");
            printf("  clear               Clear the terminal screen\n");
            printf("  exit                Terminate the session\n");
        }
        else if (strcmp(cmd, "exit") == 0) {
            break;
        }
        else {
            system(input);
        }
    }
    return 0;
}
