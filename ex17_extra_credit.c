#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    unsigned int max_data;
    unsigned int max_rows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};


void Database_close(struct Connection *conn, unsigned int max_rows)
{
    if (conn) {
        if (conn->file) fclose(conn->file);
        if (conn->db->rows) {
            int i;
            for (i = 0; i < max_rows; ++i) {
                free(conn->db->rows[i].name);
                free(conn->db->rows[i].email);
            }
            free(conn->db->rows);
        }
        if (conn->db) free(conn->db);
        free(conn);
    }
}


/* extra credit 1) */
void die(const char *message, struct Connection *conn)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    if (conn)
        Database_close(conn, conn->db->max_rows);

    exit(1);
}


void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}


void Database_load(struct Connection *conn)
{
    /* get max data */
    int rc = fread(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file);
    if (rc != 1) die("Failed to read max_data.", conn);

    /* get max rows */
    rc = fread(&conn->db->max_rows, sizeof(conn->db->max_rows), 1, conn->file);
    if (rc != 1) die("Failed to read max_rows", conn);

    /* load the database, row by row */
    conn->db->rows = calloc(1, sizeof(struct Address) * conn->db->max_rows);
    int i;
    for (i = 0; i < conn->db->max_rows; ++i) {
        rc = fread(&conn->db->rows[i].id, sizeof(unsigned int), 1, conn->file);
        if (rc != 1) die("1) Failed to load database.", conn);
        rc = fread(&conn->db->rows[i].set, sizeof(unsigned int), 1, conn->file);
        if (rc != 1) die("2) Failed to load database.", conn);

        char *name = calloc(1, conn->db->max_data);
        char *email = calloc(1, conn->db->max_data);
        rc = fread(name, conn->db->max_data, 1, conn->file);
        if (rc != 1) die("3) Failed to load database.", conn);
        rc = fread(email, conn->db->max_data, 1, conn->file);
        if (rc != 1) die("4) Failed to load database.", conn);

        conn->db->rows[i].name = name;
        conn->db->rows[i].email = email;
    }
}


struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memory error", conn);

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die("Memory error", conn);

    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) die("Failed to open the file", conn);

    return conn;
}


void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = 0;
    // write max_data
    rc = fwrite(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file);
    if (rc != 1)
        die("Failed to write max_data.", conn);

    // write max_rows
    rc = fwrite(&conn->db->max_rows, sizeof(conn->db->max_rows), 1, conn->file);
    if (rc != 1)
        die("Failed to write max_rows.", conn);

    // write database
    /**
     * Q: Can we write entire contents of a struct (with nested pointer to structs)
     *    in single fwrite ?
     */
    int i;
    for (i = 0; i < conn->db->max_rows; ++i) {
        rc = fwrite(&conn->db->rows[i].id, sizeof(unsigned int), 1, conn->file);
        if (rc != 1) die("Failed to write database.", conn);
        rc = fwrite(&conn->db->rows[i].set, sizeof(unsigned int), 1, conn->file);
        if (rc != 1) die("Failed to write database." , conn);
        rc = fwrite(conn->db->rows[i].name, conn->db->max_data, 1, conn->file);
        if (rc != 1) die("Failed to write database.", conn);
        rc = fwrite(conn->db->rows[i].email, conn->db->max_data, 1, conn->file);
        if (rc != 1) die("Failed to write database.", conn);
    }

    rc = fflush(conn->file);
    if (rc == -1)
        die("Cannot flush database.", conn);
}


void Database_create(struct Connection *conn, unsigned int max_rows, unsigned int max_data)
{
    conn->db->max_rows = max_rows;
    conn->db->max_data = max_data;
    struct Address *rows = calloc(1, sizeof(struct Address) * max_rows);

    int i = 0;
    for (i = 0; i < max_rows; ++i) {
        rows[i].id = i;
        rows[i].set = 0;
        rows[i].name = calloc(1, max_data);
        rows[i].email = calloc(1, max_data);
    }

    conn->db->rows = rows;
}


void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first", conn);

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->db->max_data);
    // demonstrate the strncpy bug
    if (!res) die("Name copy failed", conn);

    res = strncpy(addr->email, email, conn->db->max_data);
    if (!res) die("Email copy failed", conn);
}


void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}


void Database_delete(struct Connection *conn, int id)
{
    memset(conn->db->rows[id].name, 0, conn->db->max_data);
    memset(conn->db->rows[id].email, 0, conn->db->max_data);
    conn->db->rows[id].set = 0;
}


void Database_list(struct Connection *conn)
{
    struct Address *cur = conn->db->rows;

    int i = 0;
    for (i = 0; i < conn->db->max_rows; ++i) {
        if (cur->set) {
            Address_print(cur);
        } ++cur;
    }
}


void Database_find(struct Connection *conn, const char *name)
{
    //struct Address *cur = conn->db->rows;
    int i;
    for (i = 0; i < conn->db->max_rows; ++i) {
        if (!strcmp(name, conn->db->rows[i].name))
            Address_print(&conn->db->rows[i]);
    }
}


int main(int argc, char **argv)
{
    int max_rows = 1024;
    int max_data = 512;

    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if (action != 'c' && argc > 3) id = atoi(argv[3]);
    if (action != 'c' && id >= conn->db->max_rows) die("There's not that many records.", conn);

    switch (action) {
        case 'c':
            Database_create(conn, max_rows, max_data);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4) die("Need an id to get", conn);

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) die("Need id, name, email to set", conn);

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4) die("Need id to delete", conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        case 'f':
            Database_find(conn, argv[3]);
            break;

        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn, max_rows);

    return EXIT_SUCCESS;
}
