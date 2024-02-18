#ifndef RL_LOCK
#define RL_LOCK

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdatomic.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>
#include <assert.h>

typedef struct
{
    pid_t proc; /* pid du processus */
    int des; /* descripteur de fichier */
} owner;

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t rcond;
    pthread_cond_t wcond;
    bool libre;
} memory;  

#define NB_OWNERS 256
typedef struct
{
    int next_lock;//indice de l’élément suivant
    // -1 pour le dernier élément de la liste
    //-2 si la case n’est pas utilisée(initialement)
    off_t starting_offset; //décalage du début du segment par rapport au début du fichier
    off_t len; //  longueur du segment ; si len == 0, jusqu'à la fin
    short type; /* F_RDLCK F_WRLCK */
    size_t nb_owners; //le nombre de propriétaires effectifs du verrou
    owner lock_owners [NB_OWNERS];
    memory *m; 
} rl_lock;

#define NB_LOCKS 10
typedef struct {
    int first;//indice du premier élément
    rl_lock* lock_table; // (rl_lock *) malloc (NB_LOCKS * sizeof(rl_lock));
    //Initialement toutes les cases de lock_table sont libres 
    //donc first == -2 et next_lock == -2 pour chaque verrou
} rl_open_file;

typedef struct {
    int d; // descripteur de fichier habituel
    rl_open_file* f;//(rl_open_file *) malloc (sizeof(rl_open_file));
    //un pointeur vers la mémoire partagée contenant la structure rl_open_file
} rl_descriptor;

#define NB_FILES 256
static struct {
    int nb_files;
    rl_open_file *tab_open_files[NB_FILES];
} rl_all_files; 

char* generateSharedMemoryObjectName (dev_t st1,ino_t st2);
int initialiser_mutex(pthread_mutex_t *pmutex);
int initialiser_cond(pthread_cond_t *pcond);
void thread_error(const char *file, int line, int code, char *txt);
rl_descriptor rl_open(const char *path, int oflag, ...);
int rl_close(rl_descriptor lfd);
owner init_owner_lfd (rl_descriptor lfd);
bool owner_equal_lfd_owner (owner lfd_owner,owner ow);
int lfd_owner_in_lock_owners (owner lfd_owner,rl_lock lock);
int * lfd_owner_belongs_to_lock_tab (owner lfd_owner,rl_open_file lfd_file, off_t start, off_t len);
int already_locked (int pos,off_t start, off_t length, rl_lock * fl, pid_t pid);
owner * delete_lock_owner (owner *current_owners ,int i);
rl_lock * delete_lock (rl_lock * current_locks ,int i);
bool lock_table_full (rl_lock * current_locks);
rl_lock * pose_lock (rl_lock * current_locks , rl_lock newlock);
rl_lock * enleve_lock_ou_owner (int a,int b,rl_descriptor lfd);
int rl_fcntl (rl_descriptor lfd, int cmd, struct flock *lck);
rl_descriptor rl_dup(rl_descriptor lfd);
rl_descriptor rl_dup2(rl_descriptor lfd, int newd);
pid_t rl_fork();
int rl_init_library();
void print_all ();
#endif

