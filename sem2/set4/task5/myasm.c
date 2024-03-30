#include <stdio.h>
#include <stdlib.h>

void execf(char *plugin, char *func, int argc, char **args) {

}

int main(int argc, char *argv[])
{
    char command[1001];
    char *core = "core";

    while (gets(command)) {
        char *plugin;
        char *func;

        int curr_i = 0;

        while (command[curr_i] != ':' || command[curr_i] != ' ' || command[curr_i] == '\0') {
            curr_i++;
        }

        if (command[curr_i] == ':') {
            plugin = command;
            func = &command[curr_i + 1];
        } else if (command[curr_i] == ' '){
            plugin = core;
            func = command;
        } else {
            execf(core, plugin, 0, NULL);
            continue;
        }
        command[curr_i] = '\0';

        curr_i++;
        while (command[curr_i] != ' ' || command[curr_i] != '\0') {
            curr_i++;
        }
        command[curr_i] = '\0';

        while (command[curr_i] != '\0') {

        }


    }

    return EXIT_SUCCESS;
}
