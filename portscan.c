/*
 * portscan.c: tcp portscanner for plan 9
 * sean caron (scaron@umich.edu)
*/

#include <u.h>
#include <libc.h>

int main(int argc, char **argv);

int main(int argc, char **argv) {
    int port = 1;
    int limit = 1;
    int result = 0;
    char connport[128], devdir[128], *dialaddr;

    if (argc != 3) {
        print("usage: %s host maxport\n", argv[0]);
        exits(0);
    }

    limit = atoi(argv[2]);

    while (port <= limit) {
        sprint(connport, "%d", port);

        dialaddr = netmkaddr(argv[1], "tcp", connport);

        result = dial(dialaddr, 0, devdir, 0);

        if (result >= 0) {
            print("%s:%d open\n", argv[1], port);
            hangup(result);
        }

        port = port + 1;
    }
}

