#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
    int check;
} user_data;

void banner() {
    puts(" _   _ _          _____");
    puts("| \\ | (_) ___ ___|  ___|__  _ __ _   _ _ __ ___  ___");
    puts("|  \\| | |/ __/ _ \\ |_ / _ \\| '__| | | | '_ ` _ \\/ __|");
    puts("| |\\  | | (_|  __/  _| (_) | |  | |_| | | | | | \\__ \\");
    puts("|_| \\_|_|\\___\\___|_|  \\___/|_|   \\__,_|_| |_| |_|___/");
    puts("\n\n\n");
}

void vip_queue() {
    puts("[+] Your user is in the VIP list. Thanks for subscribing :D");
    puts("===================================");
    puts("===================================");
    puts("====      CONGRATULATIONS      ====");
    puts("===================================");
    puts("====        YOU MANAGED        ====");
    puts("====   TO EXPLOIT THE BINARY   ====");
    puts("===================================");
    puts("===================================");
    puts("==  STACK BASED BUFFER OVERFLOW  ==");
    puts("===================================");
    puts("===================================");
}

void get_user_info() {
    user_data data;
    data.check = 0;

    puts("[+] Welcome to NiceForums!");
    puts("[+] Please, submit your name or alias to continue with the subscription.");

    puts("Name or Alias:");
    gets(data.name);

    if (data.check != 0) {
        puts("[!] ALERT! Stop trying strange stuff >:(");
        exit(1);
    }
    return;
}

int main() {
    banner();
    get_user_info();
    puts("[!] There are no places available for non VIP users and you don't figure as one.");
}
